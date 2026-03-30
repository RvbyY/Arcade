#include "../../../include/graphics/Ncurses/Ncurses.hpp"
#include "../../../lib/libarcade/Arcade/utils/types.hpp"
#include <ncurses.h>
#include <utility>

void NcursesGraphic::open()
{
    setIsWinOpen(true);
    _window = initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_WHITE,   COLOR_BLACK);
        init_pair(2, COLOR_RED,     COLOR_BLACK);
        init_pair(3, COLOR_GREEN,   COLOR_BLACK);
        init_pair(4, COLOR_YELLOW,  COLOR_BLACK);
        init_pair(5, COLOR_BLUE,    COLOR_BLACK);
        init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(7, COLOR_CYAN,    COLOR_BLACK);
    }
}

void NcursesGraphic::close() noexcept
{
    setIsWinOpen(false);
    endwin();
}

bool NcursesGraphic::isOpen() const noexcept
{
    return NcursesGraphic::getIsWinOpen();
}
void NcursesGraphic::clear()
{
    clear();
}

void NcursesGraphic::display()
{
    refresh();
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
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);
    if (text.x >= maxX || text.y >= maxY || text.x < 0 || text.y < 0)
        return;
    attron(COLOR_PAIR(text.color));
    mvprintw(text.y, text.x, "%s", text.content.c_str());
    attroff(COLOR_PAIR(text.color));
}

std::optional<Arcade::Event> NcursesGraphic::pollEvent()
{
    int ch = wgetch(_window);

    return NcursesGraphic::switchCaseKey(ch);
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

    return {y, x};
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