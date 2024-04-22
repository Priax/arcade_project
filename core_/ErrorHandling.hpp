/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-arcade-vincent.montero-fontaine
** File description:
** ErrorHandling
*/

#ifndef ERRORHANDLING_HPP_
#define ERRORHANDLING_HPP_

#include <iostream>

namespace arcade
{
    class ErrorHandling;
}

class arcade::ErrorHandling {
    public:
        static int checkArgs(int ac, char** av);
        static void displayHelp();

    protected:
    private:
};

#endif /* !ERRORHANDLING_HPP_ */
