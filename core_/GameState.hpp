/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-arcade-vincent.montero-fontaine
** File description:
** GameState
*/

#ifndef GAMESTATE_HPP_
#define GAMESTATE_HPP_

#include <iostream>
#include <map>
#include <vector>
#include "Parsing.hpp"

#define SCORES_FILE "./ressources/"
#define LIB_PATH "./lib"

#define SNAKE_COVER "./ressources/snake_ascii.txt"
#define NIBBLER_COVER "./ressources/nibbler_ascii.txt"

#define EMPTY ' '
#define INVISIBLE '_'
#define WALL '#'
#define APPLE 'O'
#define BANANA '0'
#define HEAD 'D'
#define TAIL 'H'
#define BASE_LENGTH 4
#define APPLE_POINTS 100
#define BANANA_POINTS 300
#define MAX_APPLES_NIBBLER 40

namespace arcade {
    class GameState;

    enum screenState {
        ARCADE_MENU,
        GAME_START,
        IN_GAME,
        GAME_END,
        STOP
    };

    enum keyPressed {
        NOTHING = 0,
        UP_KEY,
        LEFT_KEY,
        RIGHT_KEY,
        DOWN_KEY,
        SPACE_KEY
    };

    enum libType {
        GAME,
        GRAPHICALS
    };
}

class arcade::GameState {
    public:
        GameState();
        ~GameState();
        void printScores();
        //std::map<std::string, int> getScores();
        std::map<std::string, std::map<std::string, int>> getScores();
        std::map<std::string, int> getGameScores(std::string gameName);
        std::vector<std::string> getLibsList();
        std::vector<std::string> getGraphList();
        std::vector<std::string> getGamesList();
        std::string getGraphLib();
        std::string getGameLib();
        std::string getUsername();
        void displayLibs(std::vector<std::string> libs);
        screenState getState();
        void setState(screenState state);
        void setUsername(std::string username);
        void setGraphLib(std::string libName);
        void setGameLib(std::string libName);
        void setGameArray(std::vector<std::string> gameArray);
        std::vector<std::string> getGameArray();
        void setKey(keyPressed key);
        keyPressed getKey();
        std::vector<std::string> getAscii();
        void setAscii(std::vector<std::string> ascii);
        void setScore(int score);
        int getScore();
        bool win = false;

    protected:
    private:
        std::map<std::string, std::map<std::string, int>> _scores = {};
        std::vector<std::string> _libsList = {};
        std::vector<std::string> _graphList = {};
        std::vector<std::string> _gamesList = {};
        std::string _username = "";
        std::string _graphLib = "";
        std::string _gameLib = "";
        int _score = 0;
        std::vector<std::string> _asciiGame = {};
        std::vector<std::string> _gameArray = {};
        screenState _state = screenState::ARCADE_MENU;
        keyPressed _key = NOTHING;
};

#endif /* !GAMESTATE_HPP_ */
