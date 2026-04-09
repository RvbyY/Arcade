#include <chrono>
#include <deque>
#include <optional>
#include <random>
#include <unordered_map>
#include "game.hpp"
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
            static constexpr int MAP_WIDTH = 60;
            static constexpr int MAP_HEIGHT = 30;
            static constexpr int GHOST_ZONE_WIDTH = 5;
            static constexpr int GHOST_ZONE_HEIGHT = 4;
            static constexpr int TARGET_GUN = 2;
            static constexpr int GUN_MAX_ATTEMPs = 50;
            static constexpr std::chrono::milliseconds MOVE_DELAY = std::chrono::milliseconds(100);

            // helpers
            bool spawnPacGun();
            void eatPacGun();
            std::optional<Tools::Vec2> getRandomEmptyCoord();
            Arcade::Color getCellColor(Tools::CellType type);

            // state
            size_t _nbPacGun;
            Tools::Grid<Tools::CellType> _grid;
            std::mt19937 _rng;
            Tools::Vec2 _pacman;
            std::deque<Tools::Vec2> _ghosts;
            std::optional<Tools::Vec2> _dir;
            std::chrono::nanoseconds _accumulator;
            bool _gameOver;
    };
}
