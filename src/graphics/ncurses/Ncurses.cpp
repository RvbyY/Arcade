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
    short toNcursesColor(const Arcade::Color& col)
    {
        const auto simple = col.simple();

        switch (simple)
        {
            case Arcade::Colors::RED   : return COLOR_RED;
            case Arcade::Colors::GREEN : return COLOR_GREEN;
            case Arcade::Colors::YELLOW: return COLOR_YELLOW;
            case Arcade::Colors::BLUE  : return COLOR_BLUE;
            case Arcade::Colors::PURPLE: return COLOR_MAGENTA;
            case Arcade::Colors::CYAN  : return COLOR_CYAN;
            case Arcade::Colors::WHITE : return COLOR_WHITE;
            default: return COLOR_BLACK;
        }
    }

    int toColorIndex(const Arcade::Color& col)
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
            default: return 0;
        }
    }

    int toPair(const Arcade::Color& fg, const Arcade::Color& bg)
    {
        constexpr int paletteSize = 8;

        return toColorIndex(fg) * paletteSize + toColorIndex(bg) + 1;
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
        static constexpr Arcade::Color palette[] = {
            Arcade::Colors::BLACK,
            Arcade::Colors::WHITE,
            Arcade::Colors::RED,
            Arcade::Colors::GREEN,
            Arcade::Colors::YELLOW,
            Arcade::Colors::BLUE,
            Arcade::Colors::PURPLE,
            Arcade::Colors::CYAN,
        };

        start_color();
        int pairId = 1;

        for (const auto& fg : palette) {
            for (const auto& bg : palette) {
                init_pair(pairId, toNcursesColor(fg), toNcursesColor(bg));
                pairId++;
            }
        }
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

void NcursesGraphic::draw(const Arcade::Shapes::Point& point)
{
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);
    if (point.x >= maxX || point.y >= maxY || point.x < 0 || point.y < 0)
        return;
    attron(COLOR_PAIR(toPair(Arcade::Colors::BLACK, point.color)));
    mvaddch(point.y, point.x, ' ');
    attroff(COLOR_PAIR(toPair(Arcade::Colors::BLACK, point.color)));
}

void NcursesGraphic::draw(const Arcade::Shapes::Rectangle& rect)
{
    attron(COLOR_PAIR(toPair(Arcade::Colors::BLACK, rect.color)));

    for (int y = rect.y; y < rect.y + rect.height + (rect.height == 0); y++) {
        for (int x = rect.x; x < rect.x + rect.width + (rect.width == 0); x++) {
            mvaddch(y, x, ' ');
        }
    }

    attroff(COLOR_PAIR(toPair(Arcade::Colors::BLACK, rect.color)));
}

void NcursesGraphic::draw(const Arcade::Text& text)
{
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);
    if (text.x >= maxX || text.y >= maxY || text.x < 0 || text.y < 0)
        return;
    const auto maxWidth = maxX - text.x;

    attron(COLOR_PAIR(toPair(text.color, Arcade::Colors::BLACK)));
    mvaddnstr(text.y, text.x, text.content.c_str(), maxWidth);
    attroff(COLOR_PAIR(toPair(text.color, Arcade::Colors::BLACK)));
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
