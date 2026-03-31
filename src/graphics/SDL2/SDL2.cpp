#include "../../../include/graphics/SDL2/SDL2.hpp"
#include "../../../lib/libarcade/Arcade/utils/types.hpp"
#include <SDL2/SDL.h>

extern "C" {
    Arcade::IDisplay* get_display() {
        return new SDL2Graphic();
    }

}

void SDL2Graphic::open()
{
    SDL_Init(SDL_INIT_VIDEO);
    _window = SDL_CreateWindow(
        "Arcade",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_SHOWN
    );
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    setIsWinOpen(true);
}

void SDL2Graphic::close() noexcept
{
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
    setIsWinOpen(false);
}

bool SDL2Graphic::isOpen() const noexcept
{
    return getIsWinOpen();
}

void SDL2Graphic::clear()
{
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);
}

void SDL2Graphic::display()
{
    SDL_RenderPresent(_renderer);
}

void SDL2Graphic::draw(const Arcade::Shapes::Point& point)
{
    SDL_SetRenderDrawColor(_renderer,
        point.color.red, point.color.green, point.color.blue, point.color.alpha);
    SDL_RenderDrawPoint(_renderer, point.x, point.y);
}

void SDL2Graphic::draw(const Arcade::Shapes::Rectangle& rect)
{
    SDL_Rect sdlRect = {
        static_cast<int>(rect.x),
        static_cast<int>(rect.y),
        static_cast<int>(rect.width),
        static_cast<int>(rect.height)
    };
    SDL_SetRenderDrawColor(_renderer,
        rect.color.red, rect.color.green, rect.color.blue, rect.color.alpha);
    SDL_RenderDrawRect(_renderer, &sdlRect);
}

void SDL2Graphic::draw(const Arcade::Text& text)
{
    if (!_font) return;
    SDL_Color color = { text.color.red, text.color.green, text.color.blue, text.color.alpha };
    SDL_Surface* surface = TTF_RenderText_Solid(_font, text.content.c_str(), color);
    if (!surface) return;
    SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, surface);
    SDL_Rect dst = { static_cast<int>(text.x), static_cast<int>(text.y), surface->w, surface->h };
    SDL_FreeSurface(surface);
    SDL_RenderCopy(_renderer, texture, nullptr, &dst);
    SDL_DestroyTexture(texture);
}

std::optional<Arcade::Event> SDL2Graphic::pollEvent()
{
    SDL_Event event;

    if (SDL_PollEvent(&event) == 0)
        return {};

    if (event.type == SDL_QUIT)
        return Arcade::Event::ARC_CLOSE;

    if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
        return Arcade::Event::ARC_RESIZE;

    if (event.type == SDL_KEYDOWN)
        return KeySwitch(event.key.keysym.sym);

    return {};
}

std::pair<Arcade::Coordinate, Arcade::Coordinate> SDL2Graphic::mousePosition() const
{
    int x = 0, y = 0;
    SDL_GetMouseState(&x, &y);
    return { x, y };
}

std::pair<Arcade::Coordinate, Arcade::Coordinate> SDL2Graphic::size() const noexcept
{
    int w = 0, h = 0;
    SDL_GetWindowSize(_window, &w, &h);
    return { w, h };
}

std::string_view SDL2Graphic::libraryName() const noexcept
{
    return "ADR SDL2";
}

void SDL2Graphic::setIsWinOpen(bool newState)
{
    _isWinOpen = newState;
}

bool SDL2Graphic::getIsWinOpen() const
{
    return _isWinOpen;
}
