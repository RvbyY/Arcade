#pragma once

#include "../../../lib/libarcade/Arcade/display.hpp"
#include <SFML/Graphics.hpp>
#include <optional>
#include <string_view>
#include <utility>

class SfmlGraphic : public Arcade::IDisplay {
public:
    SfmlGraphic()  = default;
    ~SfmlGraphic() override = default;

    // ── Lifecycle ──────────────────────────────────────────────────────────
    void open()          override;
    void close() noexcept override;
    bool isOpen()  const noexcept override;

    // ── Frame ──────────────────────────────────────────────────────────────
    void clear()   override;
    void display() override;

    // ── Draw overloads ─────────────────────────────────────────────────────
    void draw(const Arcade::Shapes::Point&     point) override;
    void draw(const Arcade::Shapes::Rectangle& rect)  override;
    void draw(const Arcade::Text&              text)  override;

    // ── Events ─────────────────────────────────────────────────────────────
    std::optional<Arcade::Event> pollEvent() override;

    // ── Queries ────────────────────────────────────────────────────────────
    std::pair<Arcade::Coordinate, Arcade::Coordinate> mousePosition() const override;
    std::pair<Arcade::Coordinate, Arcade::Coordinate> size()  const noexcept override;
    std::string_view libraryName() const noexcept override;

    std::optional<Arcade::Event> KeySwitch(int);

private:
    void setIsWinOpen(bool newState);
    bool getIsWinOpen() const;

    sf::RenderWindow _window;
    sf::Font         _font;
    bool             _isWinOpen = false;
};
