/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-arcade-vincent.montero-fontaine
** File description:
** AGraph
*/

#ifndef AGRAPH_HPP_
#define AGRAPH_HPP_

#include "IGraph.hpp"
#include "../core_/GameState.hpp"

namespace arcade
{
    class AGraph;
}

class arcade::AGraph : public arcade::IGraph
{
public:
    AGraph();
    ~AGraph();
    virtual void displayWindow(GameState &gs) = 0;
    virtual void displayArcadeMenu(GameState &gs) = 0;
    arcade::libType getLibType();

protected:
private:
};

#endif /* !AGRAPH_HPP_ */
