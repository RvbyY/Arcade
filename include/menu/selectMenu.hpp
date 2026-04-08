#pragma once

#include <cstddef>
#include <optional>
#include "Arcade/game.hpp"
#include "Arcade/display.hpp"
#include "Arcade/utils.hpp"

void MenuLoop(std::size_t selectedButton, Arcade::IDisplay* graphic, void *handle);
int ProgrammEntrypoint(int, char**);

class Core;
namespace Arcade {
    class IDisplay;
    struct Player;

    class SelectMenu : public IGame {
        public:
            enum class SelectType {
                Graphics,
                Games
            };

            SelectMenu(Core& core);
            ~SelectMenu() noexcept override = default;

            void init() override;
            void destroy() override;
            void handleEvent(Events::Event evt, IDisplay& display) override;
            void update(std::chrono::nanoseconds dt, Player& player) override;
            void render(IDisplay& display) override;
            void restart();

            std::string_view gameTitle() const noexcept override { return "Select Menu - BAM"; }

        private:
            Core& _core;
            SelectType _selected = SelectType::Graphics;
            std::optional<Events::Event> _pendingEvent;
    };
}
