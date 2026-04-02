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

void NcursesGraphic::open()
{
    setIsWinOpen(true);
    _window = ::initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    ::start_color();
    ::use_default_colors();

    init_pair(COLOR_BLACK,   COLOR_BLACK,   COLOR_BLACK);
    init_pair(COLOR_RED,     COLOR_RED,     COLOR_BLACK);
    init_pair(COLOR_GREEN,   COLOR_GREEN,   COLOR_BLACK);
    init_pair(COLOR_BLUE,    COLOR_BLUE,    COLOR_BLACK);
    init_pair(COLOR_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(COLOR_YELLOW,  COLOR_YELLOW,  COLOR_BLACK);
    init_pair(COLOR_CYAN,    COLOR_CYAN,    COLOR_BLACK);
    init_pair(COLOR_WHITE,   COLOR_WHITE,   COLOR_BLACK);

    ::bkgd(COLOR_PAIR(COLOR_BLACK));
    ::cbreak();
    ::noecho();
    ::keypad(stdscr, TRUE);
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
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    ::clear();
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
    attron(COLOR_PAIR(point.color));
    mvaddch(point.y, point.x, '#');   // or whatever char represents a point
    attroff(COLOR_PAIR(point.color));
}

void NcursesGraphic::draw(const Arcade::Shapes::Rectangle& rect)
{
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);
    if (rect.x >= maxX || rect.y >= maxY || rect.x < 0 || rect.y < 0)
        return;
    attron(COLOR_PAIR(rect.color));

    for (int y = rect.y; y < rect.y + rect.height; y++) {
        for (int x = rect.x; x < rect.x + rect.width; x++) {
            bool isBorder = (y == rect.y || y == rect.y + rect.height - 1 ||
                             x == rect.x || x == rect.x + rect.width - 1);
            mvaddch(y, x, isBorder ? '#' : ' ');
        }
    }

    attroff(COLOR_PAIR(rect.color));
}

void NcursesGraphic::draw(const Arcade::Text& text)
{
    short ncursesColor = ColorToNcurses(text.color);
    ::attron(COLOR_PAIR(ncursesColor));
    ::mvprintw(text.y, text.x, "%s", text.content.c_str());
    ::attroff(COLOR_PAIR(ncursesColor));
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
    return "ADR Ncurses";
}

void NcursesGraphic::setIsWinOpen(bool newState)
{
    _isWinOpen = newState;
}

bool NcursesGraphic::getIsWinOpen() const
{
    return _isWinOpen;
}
