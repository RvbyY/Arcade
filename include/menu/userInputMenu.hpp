#pragma once

#include <optional>
#include <string>
#include "Arcade/game.hpp"
#include "Arcade/display.hpp"
#include "Arcade/utils.hpp"

char EventToChar(Arcade::Event event);
std::string UsernameScreen(Arcade::IDisplay* graphic);

class Core;
namespace Arcade {
    class IDisplay;
    struct Player;

    class UserInputMenu : public IGame {
        public:
            UserInputMenu(Core& core);
            ~UserInputMenu() noexcept override = default;

            void init() override;
            void destroy() override;
            void handleEvent(Events::Event evt, IDisplay& display) override;
            void update(std::chrono::nanoseconds dt, Player& player) override;
            void render(IDisplay& display) override;
            void restart();

            std::string_view gameTitle() const noexcept override { return "User Input Menu - BAM"; }

        private:
            Core& _core;
            std::optional<Events::Event> _pendingEvent;
            std::string _input;
    };
}
