#include "../../include/menu/userInputMenu.hpp"
#include "../../include/core/core.hpp"

Arcade::UserInputMenu::UserInputMenu(Core& core)
    : _core(core)
{
}


void Arcade::UserInputMenu::init()
{
    restart();
}

void Arcade::UserInputMenu::destroy()
{
    _pendingEvent.reset();
}

void Arcade::UserInputMenu::handleEvent(Events::Event evt, IDisplay& display)
{
    (void)display;
    _pendingEvent = evt;
}

void Arcade::UserInputMenu::update(std::chrono::nanoseconds dt, Player& player)
{
    (void)dt;
    (void)player;

    if (!_pendingEvent.has_value()) {
        return;
    }
    switch (*_pendingEvent) {
        case Arcade::Event::ARC_KEY_RETURN:
            if (_input.empty())
                return;
            _core.setPlayer(_input);
            _core.switchToSelectMenu();
            return;
        case Arcade::Event::ARC_KEY_BACKSPACE:
            if (!_input.empty())
                _input.pop_back();
            break;
        default: {
            const char character = EventToChar(*_pendingEvent);
            if (character != 0 && _input.size() < 16) {
                _input += character;
            }
            break;
        }
    }
    _pendingEvent.reset();
}

void Arcade::UserInputMenu::render(IDisplay& display)
{
    const Arcade::Color white(255, 255, 255);
    const Arcade::Color yellow(255, 255, 0);

    display.draw(Arcade::Text{"Enter your username:", 10, 5, white});
    display.draw(Arcade::Text{"> " + _input + "_", 10, 7, yellow});
    display.draw(Arcade::Text{"Press ENTER to confirm", 10, 10, white});
}

void Arcade::UserInputMenu::restart()
{
    _pendingEvent.reset();
}
