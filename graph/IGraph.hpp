/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-arcade-vincent.montero-fontaine
** File description:
** IGraph
*/

#ifndef IGRAPH_HPP_
#define IGRAPH_HPP_

#include <vector>
#include <string>
#include <map>
#include "../core_/GameState.hpp"

namespace arcade
{
    class IGraph;
    enum arcadeStepMenu {
        GRAPH = 0,
        GAMES,
        USERNAME
    };
}

class arcade::IGraph
{
public:
    virtual ~IGraph() = default;
    virtual void displayWindow(GameState &gs) = 0;

protected:
private:
};

#endif /* !IGRAPH_HPP_ */
