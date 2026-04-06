#include <exception>
#include <iostream>
#include "core/core.hpp"

int main(int argc, char* argv[])
{
    try {
        return core(argc, argv);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown error." << std::endl;
    }
    return 1;
}
