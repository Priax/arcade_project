/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-arcade-vincent.montero-fontaine
** File description:
** arcade
*/

#include "arcade.hpp"
#include "../graph/SDL.hpp"

int main(int ac, char** av)
{
    arcade::Core core;

    try
    {
        if (arcade::ErrorHandling::checkArgs(ac, av) == 1)
            return 0;
        core.setGraphLib(av[1]);
        core.arcade();
    } catch (const arcade::SDL::Error& error) {
        std::cerr << "SDL error occurred: " << error.what() << ": " << error.where() << std::endl;
        return 84;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 84;
    }
    catch(std::string& e)
    {
        std::cerr << "Error: " << e << '\n';
        return 84;
    }
    catch (...) {
        std::cerr << "Unknown error occured." << std::endl;
        return 84;
    }
    return 0;
}
