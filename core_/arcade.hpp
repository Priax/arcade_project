/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-arcade-vincent.montero-fontaine
** File description:
** arcade
*/

#ifndef ARCADE_HPP_
#define ARCADE_HPP_

//* INCLUDES
#include <iostream>
#include <string>
#include <map>

//? CORE
#include "DLLoader.hpp"
#include "Core.hpp"
#include "ErrorHandling.hpp"
#include "Parsing.hpp"
#include "GameState.hpp"

//? GAME
#include "../game/IGame.hpp"

//? GRAPH
#include "../graph/IGraph.hpp"
#include "../graph/AGraph.hpp"

//* DEFINES

//* STRUCTURES

//* CLASSES

//* NAMESPACES
namespace arcade
{
    //? CORE
    class Core;
    template <typename T>
    class DLLoader;
    class ErrorHandling;
    class Parsing;
    class GameState;

    //? GAME
    class IGame;
    class AGame;

    class Snake;
    class Nibbler;

    //? GRAPH
    class IGraph;
    class AGraph;

    class Ncurses;
    class SDL;
    class SFML;
}

//* FUNCTIONS
//? arcade.cpp
int main(int ac, char **av);

#endif /* !ARCADE_HPP_ */
