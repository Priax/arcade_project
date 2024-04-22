/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-arcade-vincent.montero-fontaine
** File description:
** Ncurses
*/

#ifndef NCURSES_HPP_
#define NCURSES_HPP_

#include "IGraph.hpp"
#include <ncurses.h>
#include <iostream>

namespace arcade
{
    class Ncurses;
}

class arcade::Ncurses : public IGraph
{
public:
    Ncurses();
    ~Ncurses();
    void initColors();
    void displayWindow(GameState &gs);
    void displayArcadeMenu(GameState &gs);
    void arcadeMenuEvents(GameState &gs);
    void changeSelection(int i);
    void nextStep(GameState &gs);
    void usernameMenuEvent(GameState &gs);
    int safeIncrement(int current, int max);
    void displayUsernameMenu(std::string title, int x, int y, int h, int w);
    void displayLibMenu(std::string title, std::vector<std::string> lib, int select, int x, int y, int h, int w);
    void displayScoresMenu(std::string title, std::map<std::string, int> scores, int x, int y, int h, int w);
    void displayUpperLine(std::string title, int color, int x, int y, int w);
    void displayLowerLine(int color, int x, int y, int w);
    void displayGameStart(GameState &gs);
    void arcadeGameStartEvents(GameState &gs);
    void displayKeysInfos(int y, int x);
    void displayGame(GameState &gs);
    void gameEvents(GameState &gs);
    void convertKey(GameState &gs, int key);
    void displayGameEnd(GameState &gs);
    void gameEndEvents(GameState &gs);
    void setCellColor(char c);
    void displayArcadeBorder();

protected:
private:
    enum arcade::arcadeStepMenu _step = arcade::arcadeStepMenu::GRAPH;
    int _graphSelect = 0;
    int _maxGraph = 0;
    int _gameSelect = 0;
    int _maxGame = 0;
    char _username[1016] = "";
    std::clock_t _clock = std::clock();
    float _tickRate = 1.0;
    float _idleRate = 1.0;
    bool tmp = true;
};

#endif /* !NCURSES_HPP_ */
