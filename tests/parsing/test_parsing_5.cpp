/* ------------------------------------------------------------------------------------ *
 *                                                                                      *
 * EPITECH PROJECT - Thu, Mar, 2026                                                     *
 * Title           - G-OOP-400-STG-4-1-arcade-5                                         *
 * Description     -                                                                    *
 *     test_parsing                                                                     *
 *                                                                                      *
 * ------------------------------------------------------------------------------------ *
 *                                                                                      *
 *             ███████╗██████╗ ██╗████████╗███████╗ ██████╗██╗  ██╗                     *
 *             ██╔════╝██╔══██╗██║╚══██╔══╝██╔════╝██╔════╝██║  ██║                     *
 *             █████╗  ██████╔╝██║   ██║   █████╗  ██║     ███████║                     *
 *             ██╔══╝  ██╔═══╝ ██║   ██║   ██╔══╝  ██║     ██╔══██║                     *
 *             ███████╗██║     ██║   ██║   ███████╗╚██████╗██║  ██║                     *
 *             ╚══════╝╚═╝     ╚═╝   ╚═╝   ╚══════╝ ╚═════╝╚═╝  ╚═╝                     *
 *                                                                                      *
 * ------------------------------------------------------------------------------------ */

#include <iostream>
#include <cassert>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fstream>

bool isExist(std::string lib)
{

    struct stat buffer;

    return (stat (lib.c_str(), &buffer) == 0);
}

bool parsing(std::string lib)
{
    if (isExist(lib) == false)
        return false;
    if (lib.substr(lib.find_last_of(".") + 1) != "so")
        return false;
    return true;
}

int main(void)
{
    assert(parsing("/lib/arcade_ncurses.so") == false);

    return 0;
}