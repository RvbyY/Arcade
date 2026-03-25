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

bool parsing(std::string lib)
{
    struct stat buffer;

    return (stat (lib.c_str(), &buffer) == 0);
}

int main(void)
{
    assert(parsing("test.so") == false);
    assert(parsing("") == false);
    assert(parsing("lib/arcade_ncurses.so") == true);
    assert(parsing("./lib/arcade_ncurses.so") == true);
    assert(parsing("/lib/arcade_ncurses.so") == false);

    return 0;
}