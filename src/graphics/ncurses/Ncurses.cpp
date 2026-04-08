#include "../../../include/graphics/Ncurses/Ncurses.hpp"
#include "../../../lib/libarcade/Arcade/utils/colors.hpp"
#include "../../../lib/libarcade/Arcade/utils/types.hpp"
#include <ncurses.h>
#include <utility>

extern "C" {
    Arcade::IDisplay* get_display() {
        return new NcursesGraphic();
    }

}

namespace {
    int toPairFG(const Arcade::Color& col)
    {
        const auto simple = col.simple();

        switch (simple)
        {
            case Arcade::Colors::WHITE : return 1;
            case Arcade::Colors::RED   : return 2;
            case Arcade::Colors::GREEN : return 3;
            case Arcade::Colors::YELLOW: return 4;
            case Arcade::Colors::BLUE  : return 5;
            case Arcade::Colors::PURPLE: return 6;
            case Arcade::Colors::CYAN  : return 7;
            default: return 0; // default (black)
        }
    }

    int toPairBG(const Arcade::Color& col)
    {
        const auto simple = col.simple();

        switch (simple)
        {
            case Arcade::Colors::WHITE : return 8;
            case Arcade::Colors::RED   : return 9;
            case Arcade::Colors::GREEN : return 10;
            case Arcade::Colors::YELLOW: return 11;
            case Arcade::Colors::BLUE  : return 12;
            case Arcade::Colors::PURPLE: return 13;
            case Arcade::Colors::CYAN  : return 14;
            default: return 0; // default (black)
        }
    }
}

void NcursesGraphic::open()
{
    setIsWinOpen(true);
    _window = ::initscr();
    cbreak();
    noecho();
    keypad(_window, TRUE);
    nodelay(_window, TRUE); // non-blocking input
    curs_set(0);
    set_escdelay(5);

    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_WHITE,   COLOR_BLACK);
        init_pair(2, COLOR_RED,     COLOR_BLACK);
        init_pair(3, COLOR_GREEN,   COLOR_BLACK);
        init_pair(4, COLOR_YELLOW,  COLOR_BLACK);
        init_pair(5, COLOR_BLUE,    COLOR_BLACK);
        init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(7, COLOR_CYAN,    COLOR_BLACK);
        init_pair(8, COLOR_BLACK,   COLOR_WHITE);
        init_pair(9, COLOR_BLACK,     COLOR_RED);
        init_pair(10, COLOR_BLACK,   COLOR_GREEN);
        init_pair(11, COLOR_BLACK,  COLOR_YELLOW);
        init_pair(12, COLOR_BLACK,    COLOR_BLUE);
        init_pair(13, COLOR_BLACK, COLOR_MAGENTA);
        init_pair(14, COLOR_BLACK,    COLOR_CYAN);
    }
}

void NcursesGraphic::close() noexcept
{
    setIsWinOpen(false);
    curs_set(1);
    endwin();
}

bool NcursesGraphic::isOpen() const noexcept
{
    return NcursesGraphic::getIsWinOpen();
}
void NcursesGraphic::clear()
{
    if (_window)
        ::wclear(_window);
}

void NcursesGraphic::display()
{
    ::refresh();
}

static short ColorToNcurses(const Arcade::Color& color)
{
    Arcade::Color simple = color.simple();

    switch (simple) {
        case Arcade::BLACK:  return COLOR_BLACK;
        case Arcade::RED:    return COLOR_RED;
        case Arcade::GREEN:  return COLOR_GREEN;
        case Arcade::BLUE:   return COLOR_BLUE;
        case Arcade::PURPLE: return COLOR_MAGENTA;
        case Arcade::YELLOW: return COLOR_YELLOW;
        case Arcade::CYAN:   return COLOR_CYAN;
        case Arcade::WHITE:  return COLOR_WHITE;
        default:             return COLOR_WHITE;
    }
}

void NcursesGraphic::draw(const Arcade::Shapes::Point& point)
{
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);
    if (point.x >= maxX || point.y >= maxY || point.x < 0 || point.y < 0)
        return;
    // Map your color to an ncurses color pair (assumes you've set up color pairs)
    attron(COLOR_PAIR(toPairBG(point.color)));
    mvaddch(point.y, point.x, ' ');   // or whatever char represents a point
    attroff(COLOR_PAIR(toPairBG(point.color)));
}

void NcursesGraphic::draw(const Arcade::Shapes::Rectangle& rect)
{
    attron(COLOR_PAIR(toPairBG(rect.color)));

    for (int y = rect.y; y < rect.y + rect.height + (rect.height == 0); y++) {
        for (int x = rect.x; x < rect.x + rect.width + (rect.width == 0); x++) {
            mvaddch(y, x, ' ');
        }
    }

    attroff(COLOR_PAIR(toPairBG(rect.color)));
}

void NcursesGraphic::draw(const Arcade::Text& text)
{
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);
    if (text.x >= maxX || text.y >= maxY || text.x < 0 || text.y < 0)
        return;
    attron(COLOR_PAIR(toPairFG(text.color)));
    mvprintw(text.y, text.x, "%s", text.content.c_str());
    attroff(COLOR_PAIR(toPairFG(text.color)));
}

std::optional<Arcade::Event> NcursesGraphic::pollEvent()
{
    int ch = wgetch(_window);

    return NcursesGraphic::KeySwitch(ch);
}

std::pair<Arcade::Coordinate, Arcade::Coordinate> NcursesGraphic::mousePosition() const
{
    return {0, 0};
}

std::pair<Arcade::Coordinate, Arcade::Coordinate> NcursesGraphic::size() const noexcept
{
    int y = 0;
    int x = 0;

    getmaxyx(_window, y, x);

    return {x, y};
}

std::string_view NcursesGraphic::libraryName() const noexcept
{
    return "BAM Ncurses";
}

void NcursesGraphic::setIsWinOpen(bool newState)
{
    _isWinOpen = newState;
}

bool NcursesGraphic::getIsWinOpen() const
{
    return _isWinOpen;
}
