/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** playerContainer
*/

#include "../../include/core/core.hpp"
#include "../../include/core/playerContainer/playerContainer.hpp"

#include <fstream>
#include <iostream>
#include <stdexcept>

void PlayerContainer::save(const std::filesystem::path& path)
{
    std::ofstream file(path, std::ios::trunc);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open scores file for writing: " + path.string());
    }

    for (const auto& pair : _players) {
        const CorePlayer& player = pair.second;
        if (!player.name.empty()) {
            file << player.name << "=" << player.maxScore << std::endl;
        }
    }
}

void PlayerContainer::load(const std::filesystem::path& path)
{
    std::ifstream file(path);
    // If the file doesn't exist or can't be opened, it's likely the first run.
    // We just proceed with an empty score list.
    if (!file) {
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue; // Skip empty lines
        }

        size_t delimiterPos = line.find('=');
        if (delimiterPos == std::string::npos) {
            std::cerr << "Warning: Malformed score line in " << path.string() << ": '" << line << "'" << std::endl;
            continue;
        }

        std::string playerName = line.substr(0, delimiterPos);
        std::string scoreStr = line.substr(delimiterPos + 1);

        try {
            std::uint64_t score = std::stoull(scoreStr);
            CorePlayer& player = _players[playerName];
            player.name = playerName;
            player.maxScore = score;
        } catch (const std::exception& e) {
            std::cerr << "Warning: Invalid score format in " << path.string() << " for player '" << playerName << "': '" << scoreStr << "' (" << e.what() << ")" << std::endl;
        }
    }
}
