/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** debugOverlay
*/

#include "../../include/core/overlays/debugOverlay.hpp"
#include "../../include/core/core.hpp"

Arcade::DebugOverlay::DebugOverlay(Core& core)
    : _core(&core)
{
}

void Arcade::DebugOverlay::init()
{
}

void Arcade::DebugOverlay::destroy()
{
}

void Arcade::DebugOverlay::handleEvent(Events::Event evt, IDisplay& display)
{
    (void)display;
}

void Arcade::DebugOverlay::update(std::chrono::nanoseconds dt, Player& player)
{
    (void)dt;
    (void)player;

}

void Arcade::DebugOverlay::render(IDisplay& display)
{
    auto [width, height] = display.size();

    Arcade::Text displayText("Graphical library: ", 0, 5, Arcade::GREEN);
    displayText.content += _core->displayName();
    displayText.x = width - displayText.content.length() - 5;

    Arcade::Text gameText("Game library: ", 0, 8, Arcade::GREEN);
    gameText.content += _core->gameTitle();
    gameText.x = width - gameText.content.length() - 5;

    Arcade::Text playerText("Player: ", 0, 10, Arcade::GREEN);
    playerText.content += _core->getCurrentPlayer().name;
    playerText.x = width - playerText.content.length() - 5;

    Arcade::Text playerScoreText("P-Score: ", 0, 12, Arcade::GREEN);
    playerScoreText.content += std::to_string(_core->getCurrentPlayer().score);
    playerScoreText.x = width - playerScoreText.content.length() - 5;

    display.draw(displayText);
    display.draw(gameText);
    display.draw(playerText);
    display.draw(playerScoreText);
}
