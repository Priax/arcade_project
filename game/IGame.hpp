/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-arcade-vincent.montero-fontaine
** File description:
** IGame
*/

#ifndef IGAME_HPP_
#define IGAME_HPP_

#include "../core_/GameState.hpp"

namespace arcade
{
    class IGame;
}

class arcade::IGame
{
public:
    virtual ~IGame() = default;
    virtual void updateGameState(GameState &gs) = 0;

protected:
private:
};

#endif /* !IGAME_HPP_ */
