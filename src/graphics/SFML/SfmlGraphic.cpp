#include "../../../include/graphics/SFML/SfmlGraphic.hpp"
#include "../../../lib/libarcade/Arcade/utils/colors.hpp"
#include "../../../lib/libarcade/Arcade/utils/types.hpp"
#include <SFML/Graphics.hpp>
#include <utility>

// ─── Cell dimensions (SFML has no "character grid" — we fake one) ────────────
static constexpr float CELL_W = 12.f;
static constexpr float CELL_H = 18.f;

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
        sf::VideoMode(1280, 720),
        "Arcade",
        sf::Style::Close | sf::Style::Titlebar
    );
    _window.setFramerateLimit(60);

    // Load a monospace font for text drawing
    // Adjust path to wherever your font lives in the project
    if (!_font.loadFromFile("assets/fonts/DejaVuSansMono.ttf")) {
        // Fallback: try a common system path
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

// ─── Draw overloads ──────────────────────────────────────────────────────────

void SfmlGraphic::draw(const Arcade::Shapes::Point& point)
{
    sf::RectangleShape cell(sf::Vector2f(CELL_W, CELL_H));
    cell.setPosition(point.x * CELL_W, point.y * CELL_H);
    cell.setFillColor(ColorToSfml(point.color));
    _window.draw(cell);
}

void SfmlGraphic::draw(const Arcade::Shapes::Rectangle& rect)
{
    sf::Color color = ColorToSfml(rect.color);

    for (int row = rect.y; row < rect.y + rect.height; ++row) {
        for (int col = rect.x; col < rect.x + rect.width; ++col) {
            bool isBorder = (row == rect.y || row == rect.y + rect.height - 1 ||
                             col == rect.x || col == rect.x + rect.width - 1);

            sf::RectangleShape cell(sf::Vector2f(CELL_W, CELL_H));
            cell.setPosition(col * CELL_W, row * CELL_H);

            if (isBorder) {
                cell.setFillColor(color);
            } else {
                // Interior: transparent / black fill, matching ncurses ' '
                cell.setFillColor(sf::Color::Black);
            }
            _window.draw(cell);
        }
    }
}

void SfmlGraphic::draw(const Arcade::Text& text)
{
    sf::Text sfText;
    sfText.setFont(_font);
    sfText.setString(text.content);
    sfText.setCharacterSize(static_cast<unsigned int>(CELL_H));
    sfText.setFillColor(ColorToSfml(text.color));
    sfText.setPosition(text.x * CELL_W, text.y * CELL_H);
    _window.draw(sfText);
}

// ─── Events ──────────────────────────────────────────────────────────────────

std::optional<Arcade::Event> SfmlGraphic::pollEvent()
{
    sf::Event event;
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed) {
            auto mapped = SfmlGraphic::pollEvent();
            if (mapped.has_value())
                return mapped;
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
    return "ADR SFML";
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
