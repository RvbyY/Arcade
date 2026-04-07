#include <exception>
#include <iostream>
#include "core/core.hpp"
#include "../../include/menu/menu.hpp"

int main(int argc, char** argv)
{
    Core core(argc, argv);

    int status = 0;
    try {
        status = core.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown error." << std::endl;
        return 1;
    }
    return status;
}
