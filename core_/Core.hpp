/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-arcade-vincent.montero-fontaine
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include <string>
#include "DLLoader.hpp"
#include "../game/IGame.hpp"
#include "../graph/IGraph.hpp"
#include "GameState.hpp"

namespace arcade
{
    class Core;
}

class arcade::Core
{
public:
    Core();
    ~Core();
    void setGraphLib(std::string path);
    void setGameLib(std::string path);
    DLLoader<arcade::IGraph>& getGraphLoader();
    DLLoader<arcade::IGame>& getGameLoader();
    GameState getGameState();
    void arcade();
    IGraph* updateGraph();
    IGame* initGame();
    void updateScores();

protected:
private:
    DLLoader<arcade::IGraph> _graph;
    std::string _graphName = "";
    DLLoader<arcade::IGame> _game;
    std::string _gameName = "";
    GameState _gameState;
};

#endif /* !CORE_HPP_ */
