#include "include/graphics/ncurses/Ncurses.hpp"
#include <iostream>

void NcursesGraphic::open()
{
    std::cout << "Ncurses init\n";
}

void NcursesGraphic::close() noexcept
{
    std::cout << "Ncurses stop\n";
}

bool NcursesGraphic::isOpen() const noexcept
{
    std::cout << "Ncurses isOpen\n";
    return 1;
}
void NcursesGraphic::clear()
{
    std::cout << "Ncurses clear\n";
}

void NcursesGraphic::display()
{
    std::cout << "Ncurses display\n";
}

void NcursesGraphic::draw(const Arcade::Shapes::Point& point)
{
    std::cout << "Ncurses drawpoint\n";
}

void NcursesGraphic::draw(const Arcade::Shapes::Rectangle& rect)
{
    std::cout << "Ncurses drawrectangle\n";
}

void NcursesGraphic::draw(const Arcade::Text& text)
{
    std::cout << "Ncurses drawtext\n";
}

std::optional<Arcade::Event> NcursesGraphic::pollEvent()
{

}

std::pair<Arcade::Coordinate, Arcade::Coordinate> NcursesGraphic::mousePosition() const
{

}

std::pair<Arcade::Coordinate, Arcade::Coordinate> NcursesGraphic::size() const noexcept
{

}

std::string_view NcursesGraphic::libraryName() const noexcept
{

}
