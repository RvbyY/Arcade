#include "graphics/IGraphic.hpp"
#include <iostream>

class NcursesGraphic : public IGraphic {
public:
    void init() override {
        std::cout << "Ncurses init\n";
    }

    void draw() override {
        std::cout << "Ncurses draw\n";
    }

    void stop() override {
        std::cout << "Ncurses stop\n";
    }
};

extern "C" IGraphic* create();

extern "C" void destroy(IGraphic* graphic);