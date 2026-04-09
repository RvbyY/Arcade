#include "../../../include/graphics/SDL2/SDL2.hpp"
#include "../../../lib/libarcade/Arcade/utils/types.hpp"
#include <SDL2/SDL.h>

namespace {
    constexpr int CELL_WIDTH = 24;
    constexpr int CELL_HEIGHT = 36;
}

extern "C" {
    Arcade::IDisplay* get_display() {
        return new SDL2Graphic();
    }

}

void SDL2Graphic::open()
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    _window = SDL_CreateWindow(
        "Arcade",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );
    if (!_window) {
        setIsWinOpen(false);
        return;
    }
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!_renderer)
        _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_SOFTWARE);
    _font = TTF_OpenFont("assets/fonts/DejaVuSansMono.ttf", CELL_HEIGHT);
    if (!_font)
        _font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf", CELL_HEIGHT);
    setIsWinOpen(_renderer != nullptr);
}

void SDL2Graphic::close() noexcept
{
    if (_font) {
        TTF_CloseFont(_font);
        _font = nullptr;
    }
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    TTF_Quit();
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

std::pair<int, int> SDL2Graphic::convert_coords(Arcade::Coordinate x, Arcade::Coordinate y) const
{
    return {
        static_cast<int>(x) * CELL_WIDTH,
        static_cast<int>(y) * CELL_HEIGHT
    };
}

void SDL2Graphic::display()
{
    SDL_RenderPresent(_renderer);
}

void SDL2Graphic::draw(const Arcade::Shapes::Point& point)
{
    std::pair<int, int> convertedCoords = convert_coords(point.x, point.y);
    SDL_Rect cellRect = {
        convertedCoords.first,
        convertedCoords.second,
        CELL_WIDTH,
        CELL_HEIGHT
    };
    SDL_SetRenderDrawColor(_renderer,
        point.color.red, point.color.green, point.color.blue, point.color.alpha);
    SDL_RenderFillRect(_renderer, &cellRect);
}

void SDL2Graphic::draw(const Arcade::Shapes::Rectangle& rect)
{
    std::pair<int, int> convertedCoords = convert_coords(rect.x, rect.y);
    SDL_Rect sdlRect = {
        convertedCoords.first,
        convertedCoords.second,
        static_cast<int>(rect.width + (rect.width == 0)) * CELL_WIDTH,
        static_cast<int>(rect.height + (rect.height == 0)) * CELL_HEIGHT
    };
    SDL_SetRenderDrawColor(_renderer,
        rect.color.red, rect.color.green, rect.color.blue, rect.color.alpha);
    SDL_RenderFillRect(_renderer, &sdlRect);
}

void SDL2Graphic::draw(const Arcade::Text& text)
{
    if (!_font) return;
    SDL_Color color = { text.color.red, text.color.green, text.color.blue, text.color.alpha };
    SDL_Surface* surface = TTF_RenderText_Solid(_font, text.content.c_str(), color);
    if (!surface) return;
    SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, surface);
    std::pair<int, int> convertedCoords = convert_coords(text.x, text.y);
    SDL_Rect dst = { convertedCoords.first, convertedCoords.second, surface->w, surface->h };
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
    return {
        static_cast<Arcade::Coordinate>(x / CELL_WIDTH),
        static_cast<Arcade::Coordinate>(y / CELL_HEIGHT)
    };
}

std::pair<Arcade::Coordinate, Arcade::Coordinate> SDL2Graphic::size() const noexcept
{
    int w = 0, h = 0;
    SDL_GetWindowSize(_window, &w, &h);
    return {
        static_cast<Arcade::Coordinate>(w / CELL_WIDTH),
        static_cast<Arcade::Coordinate>(h / CELL_HEIGHT)
    };
}

std::string_view SDL2Graphic::libraryName() const noexcept
{
    return "BAM SDL2";
}

void SDL2Graphic::setIsWinOpen(bool newState)
{
    _isWinOpen = newState;
}

bool SDL2Graphic::getIsWinOpen() const
{
    return _isWinOpen;
}
