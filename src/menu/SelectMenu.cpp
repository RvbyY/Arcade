#include "../../include/menu/selectMenu.hpp"
#include "../../include/menu/userInputMenu.hpp"
#include "../../include/core/core.hpp"
#include <string>

namespace {
std::size_t wrapIndex(std::size_t current, int delta, std::size_t count)
{
    if (count == 0) {
        return 0;
    }

    const auto countAsLong = static_cast<long>(count);
    const auto next = (static_cast<long>(current) + delta + countAsLong) % countAsLong;
    return static_cast<std::size_t>(next);
}
}

Arcade::SelectMenu::SelectMenu(Core& core)
    : _core(core)
{
}

void Arcade::SelectMenu::init()
{
    restart();
}

void Arcade::SelectMenu::destroy()
{
    _pendingEvent.reset();
}

void Arcade::SelectMenu::handleEvent(Events::Event evt, IDisplay& display)
{
    (void)display;
    _pendingEvent = evt;
}

void Arcade::SelectMenu::updateCoreSelect(int delta)
{
    switch (_selected) {
        case SelectType::Graphics:
            if (_core.displayCount() > 0) {
                _core.selectDisplay(wrapIndex(_core.getSelectedDisplayIndex(), delta, _core.displayCount()));
            }
            break;
        case SelectType::Games:
            if (_core.gameCount() > 0) {
                _core.selectGame(wrapIndex(_core.getSelectedGameIndex(), delta, _core.gameCount()));
            }
            break;
    }
}

void Arcade::SelectMenu::update(std::chrono::nanoseconds dt, Player& player)
{
    (void)dt;
    (void)player;
    if (!_pendingEvent.has_value()) {
        return;
    }
    switch (*_pendingEvent) {
        case Arcade::Event::ARC_ARROW_UP:
            updateCoreSelect(-1);
            break;
        case Arcade::Event::ARC_ARROW_DOWN:
            updateCoreSelect(1);
            break;
        case Arcade::Event::ARC_ARROW_LEFT:
            _selected = SelectType::Graphics;
            break;
        case Arcade::Event::ARC_ARROW_RIGHT:
            _selected = SelectType::Games;
            break;
        case Arcade::Event::ARC_KEY_RETURN:
        case Arcade::Event::ARC_KEY_SPACE:
            if (_core.gameCount() > 0) {
                _core.switchToLoadedGame();
            }
            break;
        default:
            break;
    }
    _pendingEvent.reset();
}

void Arcade::SelectMenu::render(IDisplay& display)
{
    const Arcade::Color selectedColor(255, 165, 0);
    const Arcade::Color normalColor(255, 255, 255);
    const Arcade::Color accentColor(120, 120, 120);
    const Coordinate graphicsX = 5;
    const Coordinate gamesX = 55;
    const Coordinate listStartY = 5;

    display.draw(Arcade::Text{"Graphics libraries", graphicsX, 2, normalColor});
    display.draw(Arcade::Text{"Games", gamesX, 2, normalColor});

    for (std::size_t i = 0; i < _core.displayCount(); ++i) {
        const bool isSelected = i == _core.getSelectedDisplayIndex();
        const bool isSelectTypeed = _selected == SelectType::Graphics && isSelected;
        std::string label;

        if (i < 9) {
            label = "F" + std::to_string(i + 1) + " ";
        } else {
            label = "   ";
        }
        label += std::string(_core.displayName(i));

        display.draw(Arcade::Text{label, graphicsX, listStartY + static_cast<Coordinate>(i), isSelected ? selectedColor : normalColor});
        if (isSelectTypeed) {
            display.draw(Arcade::Text{">", graphicsX - 2, listStartY + static_cast<Coordinate>(i), selectedColor});
        }
    }

    for (std::size_t i = 0; i < _core.gameCount(); ++i) {
        const bool isSelected = i == _core.getSelectedGameIndex();
        const bool isSelectTypeed = _selected == SelectType::Games && isSelected;
        const std::string label = std::string(_core.gameTitle(i));

        display.draw(Arcade::Text{label, gamesX, listStartY + static_cast<Coordinate>(i), isSelected ? selectedColor : normalColor});
        if (isSelectTypeed) {
            display.draw(Arcade::Text{">", gamesX - 2, listStartY + static_cast<Coordinate>(i), selectedColor});
        }
    }

    display.draw(Arcade::Text{"LEFT/RIGHT: SelectType column", 5, 20, accentColor});
    display.draw(Arcade::Text{"UP/DOWN: select item", 5, 21, accentColor});
    display.draw(Arcade::Text{"ENTER/SPACE: launch selected game", 5, 22, accentColor});
    display.draw(Arcade::Text{"F1..F12: switch graphics library", 5, 23, accentColor});
    display.draw(Arcade::Text{"In game: G next game, M menu", 5, 24, accentColor});
}

void Arcade::SelectMenu::restart()
{
    _selected = SelectType::Games;
    _pendingEvent.reset();
}
