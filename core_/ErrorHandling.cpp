/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-arcade-vincent.montero-fontaine
** File description:
** ErrorHandling
*/

#include "ErrorHandling.hpp"

void arcade::ErrorHandling::displayHelp()
{
    std::cout << "./arcade ./path/to/lib.so" << std::endl;
}

int arcade::ErrorHandling::checkArgs(int ac, char** av)
{
    if (ac != 2) {
        throw std::string(
            "One unique argument needed.\n" \
            "\t./arcade -help for help.");
    }
    if (std::string(av[1]) == "-help") {
        displayHelp();
        return 1;
    }
    return 0;
}
