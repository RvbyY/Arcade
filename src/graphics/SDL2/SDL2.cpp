#include "include/graphics/SDL2/SDL2.hpp"
#include <iostream>
#include <dlfcn.h>

void SDL2Graphic::open()
{
    std::cout << "SDL2 init\n";
}

void SDL2Graphic::close() noexcept
{
    std::cout << "SDL2 stop\n";
}

bool SDL2Graphic::isOpen() const noexcept
{
    std::cout << "SDL2 isOpen\n";
    return 1;
}
void SDL2Graphic::clear()
{
    std::cout << "SDL2 clear\n";
}

void SDL2Graphic::display()
{
    std::cout << "SDL2 display\n";
}

void SDL2Graphic::draw(const Arcade::Shapes::Point& point)
{
    std::cout << "SDL2 drawpoint\n";
}

void SDL2Graphic::draw(const Arcade::Shapes::Rectangle& rect)
{
    std::cout << "SDL2 drawrectangle\n";
}

void SDL2Graphic::draw(const Arcade::Text& text)
{
    std::cout << "SDL2 drawtext\n";
}

std::optional<Arcade::Event> SDL2Graphic::pollEvent()
{

}

std::pair<Arcade::Coordinate, Arcade::Coordinate> SDL2Graphic::mousePosition() const
{

}

std::pair<Arcade::Coordinate, Arcade::Coordinate> SDL2Graphic::size() const noexcept
{

}

std::string_view SDL2Graphic::libraryName() const noexcept
{

}
