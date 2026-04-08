#include "../../../lib/libarcade/Arcade/display.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class SDL2Graphic : public Arcade::IDisplay {

public:
    void open() override;

    void close() noexcept override;

    bool isOpen() const noexcept override;

    void clear() override;

    void display() override;

    void draw(const Arcade::Shapes::Point& point) override;

    template<typename T>
    T convert_coords(int x, int y) const override;

    void draw(const Arcade::Shapes::Rectangle& rect) override;

    void draw(const Arcade::Text& text) override;

    std::optional<Arcade::Event> pollEvent() override;

    std::pair<Arcade::Coordinate, Arcade::Coordinate> mousePosition() const override;

    std::pair<Arcade::Coordinate, Arcade::Coordinate> size() const noexcept override;

    std::string_view libraryName() const noexcept override;

    void setIsWinOpen(bool);

    bool getIsWinOpen() const;

    std::optional<Arcade::Event> KeySwitch(int);

    SDL_Window   *_window   = nullptr;
    SDL_Renderer *_renderer = nullptr;
    TTF_Font* _font;

private:

    bool _isWinOpen = false;
};