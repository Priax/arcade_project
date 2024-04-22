/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-arcade-vincent.montero-fontaine
** File description:
** Core
*/

#include "Core.hpp"
#include <regex>

arcade::Core::Core()
{
}

arcade::Core::~Core()
{
}

void arcade::Core::setGraphLib(std::string path)
{
    this->_graph.loadInstance(path);
    this->_graphName = path;
    this->_gameState.setGraphLib(path);
}

void arcade::Core::setGameLib(std::string path)
{
    this->_game.loadInstance(path);
    this->_gameName = path;
    this->_gameState.setGameLib(path);
}

arcade::DLLoader<arcade::IGraph>& arcade::Core::getGraphLoader()
{
    return this->_graph;
}

arcade::DLLoader<arcade::IGame>& arcade::Core::getGameLoader()
{
    return this->_game;
}

arcade::GameState arcade::Core::getGameState()
{
    return this->_gameState;
}

arcade::IGraph* arcade::Core::updateGraph()
{
    this->setGraphLib(this->_gameState.getGraphLib());
    return this->_graph.getInstance("instance");
}

arcade::IGame* arcade::Core::initGame()
{
    this->setGameLib(this->_gameState.getGameLib());
    return this->_game.getInstance("instance");
}

void arcade::Core::updateScores()
{
    std::map<std::string, int> tmp = this->_gameState.getGameScores(_gameState.getGameLib());
    tmp[this->_gameState.getUsername()] = this->_gameState.getScore();
    std::smatch matches;
    std::string gameLib = this->_gameState.getGameLib();
    std::regex_search(gameLib, matches, std::regex(".*arcade_(\\w+).so"));
    if (matches.size() == 2)
        matches[1];
    arcade::Parsing::writeScores("./ressources/" + std::string(matches[1]) + ".scores", tmp);
}

void arcade::Core::arcade()
{
    IGraph* graph = this->_graph.getInstance("instance");
    IGame* game = NULL;
    screenState state, oldstate = STOP;

    while ((state = this->_gameState.getState()) != STOP) {
        if (state == GAME_START && oldstate != GAME_START) {
            if (graph)
                delete graph;
            graph = this->updateGraph();
            if (game)
                delete game;
            game = this->initGame();
        }
        if (state == GAME_END && oldstate != GAME_END) {
            this->updateScores();
        }
        if (game)
            game->updateGameState(this->_gameState);
        graph->displayWindow(this->_gameState);
        oldstate = state;
    }

    if (graph)
        delete graph;
    if (game)
        delete game;
}
