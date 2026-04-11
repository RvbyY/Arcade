#include <chrono>
#include <deque>
#include <optional>
#include <random>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include "Arcade/game.hpp"
#include "tools/grid.hpp"

namespace Arcade {
    class PacMan : public IGame {
        public:
            PacMan();
            ~PacMan() noexcept override = default;

            void init() override;
            void destroy() override;
            void handleEvent(Events::Event evt, IDisplay& display) override;
            void update(std::chrono::nanoseconds dt, Player& player) override;
            void render(IDisplay& display) override;
            void setPacmanPosition();
            void setGhostsPositions();
            void restart();

            std::string_view gameTitle() const noexcept override { return "PacMan - BAM"; }

        private:
            static constexpr Arcade::Color YELLOW = 0xffce1b;
            static constexpr Arcade::Color PURPLE = 0x7f00ff;
            static constexpr Arcade::Color BLUE = 0x111184;
            static constexpr int MAP_WIDTH = 60;
            static constexpr int MAP_HEIGHT = 30;
            static constexpr int GHOST_ZONE_WIDTH = 5;
            static constexpr int GHOST_ZONE_HEIGHT = 4;
            static constexpr int GHOST_ZONE_CENTER_X = MAP_WIDTH / 2;
            static constexpr int GHOST_ZONE_CENTER_Y = MAP_HEIGHT / 2;
            static constexpr int GATE_WIDTH = 2;
            static constexpr int GATE_BOTTOM_X = GHOST_ZONE_CENTER_X;
            static constexpr int GATE_LEFT_Y = GHOST_ZONE_CENTER_Y;
            static constexpr int TARGET_GUN = 4;
            static constexpr int GUN_MAX_ATTEMPs = 50;
            static constexpr std::chrono::milliseconds MOVE_DELAY = std::chrono::milliseconds(100);

            // helpers
            bool spawnPacGun();
            void eatPacGun(Player& player);
            void eatGhosts(Player& player);
            void superPacActions(Player& player);
            void moveGhosts(int);
            void createMap(int, std::uniform_int_distribution<int>);
            std::optional<Tools::Vec2> getRandomEmptyCoord();
            Arcade::Color getCellColor(Tools::CellType type);

            // state
            size_t _nbPacGun;
            Tools::Grid<Tools::CellType> _grid;
            std::mt19937 _rng;
            std::array<int, 4> _ghostPoint;
            Tools::Vec2 _pacman;
            std::deque<Tools::Vec2> _ghosts;
            Tools::Vec2 _dir;
            std::chrono::nanoseconds _accumulator;
            bool _gameOver;
            bool _gameWon;
            bool _superPac;
            std::chrono::nanoseconds _superPacTimer;
            std::array<std::chrono::nanoseconds, 4> _ghostFrozenUntil;
            std::unordered_set<Tools::Vec2, Tools::Vec2Hash> _pacGuns;
    };
}
