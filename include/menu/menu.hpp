#include <cstddef>
#include <dlfcn.h>
#include "Arcade/game.hpp"
#include "Arcade/display.hpp"
#include "Arcade/utils.hpp"

void MenuLoop(std::size_t selectedButton, Arcade::IDisplay* graphic, void *handle);
int ProgrammEntrypoint(int, char**);
std::string UsernameScreen(Arcade::IDisplay* graphic);


#include "../lib/libarcade/Arcade/game.hpp"

namespace Arcade {
    class IDisplay;
    struct Player;

    class Menu : public IGame {
        public:
            Menu();
            ~Menu() noexcept override = default;

            void init() override;
            void destroy() override;
            void handleEvent(Events::Event evt, IDisplay& display) override;
            void update(std::chrono::nanoseconds dt, Player& player) override;
            void render(IDisplay& display) override;
            void restart();

            std::string_view gameTitle() const noexcept override { return "Menu - BAM"; }

        private:
        
    };
}


// faire une game qui prend un paramètre en + qui n'est
// pas un .so externe et qu'on peut utiliser dans le core
// dans le core créer le menu à part avec le core en option du constructeur
