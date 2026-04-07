#include <exception>
#include <iostream>
#include "core/core.hpp"
#include "../../include/menu/menu.hpp"

int main(int argc, char** argv)
{
    Core core(argc, argv);
    try {
        core.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown error." << std::endl;
    }
    return 1;
}
