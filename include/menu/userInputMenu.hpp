#pragma once

#include <cstddef>
#include <dlfcn.h>
#include "Arcade/game.hpp"
#include "Arcade/display.hpp"
#include "Arcade/utils.hpp"

void MenuLoop(std::size_t selectedButton, Arcade::IDisplay* graphic, void *handle);
int ProgrammEntrypoint(int, char**);
std::string UsernameScreen(Arcade::IDisplay* graphic);


#include "Arcade/game.hpp"

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

            std::string_view gameTitle() const noexcept override { return "Menu - BAM"; }

        private:
        Core& _core;
    };
}


// faire une game qui prend un paramètre en + qui n'est
// pas un .so externe et qu'on peut utiliser dans le core
// dans le core créer le menu à part avec le core en option du constructeur
