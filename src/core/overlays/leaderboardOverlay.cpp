/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** leaderboardOverlay
*/

#include <algorithm>
#include <string>
#include <vector>
#include "../../include/core/overlays/leaderboardOverlay.hpp"
#include "../../include/core/core.hpp"

namespace {
std::vector<const CorePlayer *> getTopPlayers(const PlayerContainer& players)
{
    std::vector<const CorePlayer *> sortedPlayers;

    for (const auto& [name, player] : players) {
        (void)name;
        if (!player.name.empty()) {
            sortedPlayers.push_back(&player);
        }
    }
    std::sort(sortedPlayers.begin(), sortedPlayers.end(), [](const CorePlayer *lhs, const CorePlayer *rhs) {
        if (lhs->maxScore != rhs->maxScore) {
            return lhs->maxScore > rhs->maxScore;
        }
        return lhs->name < rhs->name;
    });
    if (sortedPlayers.size() > 5) {
        sortedPlayers.resize(5);
    }
    return sortedPlayers;
}
}

Arcade::LeaderboardOverlay::LeaderboardOverlay(Core& core)
    : _core(&core)
{
}

void Arcade::LeaderboardOverlay::init()
{
}

void Arcade::LeaderboardOverlay::destroy()
{
}

void Arcade::LeaderboardOverlay::handleEvent(Events::Event evt, IDisplay& display)
{
    (void)evt;
    (void)display;
}

void Arcade::LeaderboardOverlay::update(std::chrono::nanoseconds dt, Player& player)
{
    (void)dt;
    (void)player;
}

void Arcade::LeaderboardOverlay::render(IDisplay& display)
{
    const Arcade::Color titleColor(255, 215, 0);
    const Arcade::Color entryColor(255, 255, 255);
    const Arcade::Color accentColor(140, 140, 140);
    const auto players = getTopPlayers(_core->players());
    constexpr Arcade::Coordinate baseX = 5;
    constexpr Arcade::Coordinate baseY = 26;

    display.draw(Arcade::Text{"Leaderboard", baseX, baseY, titleColor});
    if (players.empty()) {
        display.draw(Arcade::Text{"No scores yet", baseX, baseY + 2, accentColor});
        return;
    }
    for (std::size_t i = 0; i < players.size(); ++i) {
        const CorePlayer& player = *players[i];
        const std::string line = std::to_string(i + 1) + ". " + player.name + " - " + std::to_string(player.maxScore);

        display.draw(Arcade::Text{line, baseX, baseY + 2 + static_cast<Arcade::Coordinate>(i), entryColor});
    }
}
