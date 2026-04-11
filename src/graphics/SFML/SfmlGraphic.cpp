#include "../../../include/graphics/SFML/SfmlGraphic.hpp"
#include "../../../lib/libarcade/Arcade/utils/colors.hpp"
#include "../../../lib/libarcade/Arcade/utils/types.hpp"
#include <SFML/Graphics.hpp>
#include <utility>

// ─── Cell dimensions ─────────────────────────────────────────────────────────
static constexpr float CELL_W = 24.f;
static constexpr float CELL_H = 40.f;

extern "C" {
    Arcade::IDisplay* get_display() {
        return new SfmlGraphic();
    }
}

// ─── Helpers ─────────────────────────────────────────────────────────────────

static sf::Color ColorToSfml(const Arcade::Color& color)
{
    Arcade::Color simple = color.simple();
    switch (simple) {
        case Arcade::BLACK:  return sf::Color::Black;
        case Arcade::RED:    return sf::Color::Red;
        case Arcade::GREEN:  return sf::Color::Green;
        case Arcade::BLUE:   return sf::Color::Blue;
        case Arcade::PURPLE: return sf::Color::Magenta;
        case Arcade::YELLOW: return sf::Color::Yellow;
        case Arcade::CYAN:   return sf::Color::Cyan;
        case Arcade::WHITE:  return sf::Color::White;
        default:             return sf::Color::White;
    }
}

// ─── Lifecycle ───────────────────────────────────────────────────────────────

void SfmlGraphic::open()
{
    setIsWinOpen(true);
    _window.create(
        sf::VideoMode::getDesktopMode(),
        "Arcade",
        sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize
    );
    _window.setFramerateLimit(60);

    if (!_font.loadFromFile("assets/fonts/DejaVuSansMono.ttf")) {
        // Fallback: common system path
        _font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf");
    }
}

void SfmlGraphic::close() noexcept
{
    setIsWinOpen(false);
    if (_window.isOpen())
        _window.close();
}

bool SfmlGraphic::isOpen() const noexcept
{
    return getIsWinOpen() && _window.isOpen();
}

// ─── Frame ───────────────────────────────────────────────────────────────────

void SfmlGraphic::clear()
{
    _window.clear(sf::Color::Black);
}

void SfmlGraphic::display()
{
    _window.display();
}

sf::Vector2f SfmlGraphic::convertCoords(Arcade::Coordinate x, Arcade::Coordinate y) const
{
    return {
        static_cast<float>(x) * CELL_W,
        static_cast<float>(y) * CELL_H
    };
}

// ─── Draw overloads ──────────────────────────────────────────────────────────

void SfmlGraphic::draw(const Arcade::Shapes::Point& point)
{
    sf::RectangleShape cell(sf::Vector2f(CELL_W, CELL_H));
    cell.setPosition(convertCoords(point.x, point.y));
    cell.setFillColor(ColorToSfml(point.color));
    _window.draw(cell);
}

void SfmlGraphic::draw(const Arcade::Shapes::Rectangle& rect)
{
    sf::RectangleShape shape(sf::Vector2f(
        static_cast<float>(rect.width + (rect.width == 0)) * CELL_W,
        static_cast<float>(rect.height + (rect.height == 0)) * CELL_H
    ));
    shape.setPosition(convertCoords(rect.x, rect.y));
    shape.setFillColor(ColorToSfml(rect.color));
    _window.draw(shape);
}

void SfmlGraphic::draw(const Arcade::Text& text)
{
    sf::Text sfText;
    sfText.setFont(_font);
    sfText.setString(text.content);
    sfText.setCharacterSize(static_cast<unsigned int>(CELL_H));
    sfText.setFillColor(ColorToSfml(text.color));
    sfText.setPosition(convertCoords(text.x, text.y));
    _window.draw(sfText);
}

// ─── Events ──────────────────────────────────────────────────────────────────

std::optional<Arcade::Event> SfmlGraphic::pollEvent()
{
    sf::Event event;
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Resized) {
            sf::View view = _window.getDefaultView();
            view.setSize({
                static_cast<float>(event.size.width),
                static_cast<float>(event.size.height)
            });
            view.setCenter(event.size.width / 2, event.size.height / 2);
            _window.setView(view);
            return Arcade::Events::ARC_RESIZE;
        }
        if (event.type == sf::Event::MouseMoved) {
            return Arcade::Events::ARC_MOUSE_MOVE;
        }
        if (event.type == sf::Event::Closed) {
            return Arcade::Events::ARC_KEY_ESC;
        }
        if (event.type == sf::Event::KeyPressed) {
            return KeySwitch(event.key.code);
        }
    }
    return std::nullopt;
}

// ─── Queries ─────────────────────────────────────────────────────────────────

std::pair<Arcade::Coordinate, Arcade::Coordinate> SfmlGraphic::mousePosition() const
{
    sf::Vector2i pos = sf::Mouse::getPosition(_window);
    // Return in cell coordinates to stay consistent with the ncurses grid
    return {
        static_cast<Arcade::Coordinate>(pos.x / CELL_W),
        static_cast<Arcade::Coordinate>(pos.y / CELL_H)
    };
}

std::pair<Arcade::Coordinate, Arcade::Coordinate> SfmlGraphic::size() const noexcept
{
    auto sz = _window.getSize();
    // Express size in cell units, same as ncurses getmaxyx()
    return {
        static_cast<Arcade::Coordinate>(sz.x / CELL_W),
        static_cast<Arcade::Coordinate>(sz.y / CELL_H)
    };
}

std::string_view SfmlGraphic::libraryName() const noexcept
{
    return "BAM SFML";
}

// ─── Internal state ──────────────────────────────────────────────────────────

void SfmlGraphic::setIsWinOpen(bool newState)
{
    _isWinOpen = newState;
}

bool SfmlGraphic::getIsWinOpen() const
{
    return _isWinOpen;
}
