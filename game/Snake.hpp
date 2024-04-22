/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-arcade-vincent.montero-fontaine
** File description:
** Snake
*/

#ifndef SNAKE_HPP_
#define SNAKE_HPP_

#include "IGame.hpp"
#include "../core_/GameState.hpp"
#include <iostream>
#include <vector>
#include <ctime>

namespace arcade {
    class Snake;
}

enum Direction {
        UP,
    LEFT,   RIGHT,
        DOWN
};

class SnakeBody {
    public:
        SnakeBody(size_t h, size_t w);
        ~SnakeBody();
        size_t getX();
        size_t getY();
        Direction getDirection();
        void setX(size_t x);
        void setY(size_t y);
        void setDirection(Direction direction);
        void setVisible(bool v);
        bool isVisible();

    protected:
    private:
        size_t x = 0;
        size_t y = 0;
        enum Direction _direction = RIGHT;
        bool _visible = true;
};

class Apple {
    public:
        Apple();
        ~Apple();
        size_t getX();
        size_t getY();
        void setX(size_t x);
        void setY(size_t y);
        void setRandomXY(int maxX, int maxY);
        bool isEaten();
        void setStatus(bool status);
    protected:
    private:
        size_t _x = 0;
        size_t _y = 0;
        bool _eaten = true;
};

class arcade::Snake : public IGame {
    public:
        Snake();
        ~Snake();
        void initArena();
        void displayMap(std::vector<std::string> map);
        void initSnake(size_t length);
        void displaySnake();
        void updateSnakeMap();
        void updateSnakePosition();
        void updateGameState(GameState &gs);
        void updateGame(GameState &gs);
        void updateSnakeDirection(keyPressed key);
        bool isOuroboros();
        bool isParpaing();
        void extendSnake();
        void keyEvents(keyPressed key);
        bool isEatingApple();
        bool isGigantic();
        void updateGameStart(GameState &gs);
        void setAscii();
        void updateTick();
        void updateSnake();
        void updateArena();
        void updateApple();
        void updateBanana();
        // void setupSpeed();

    protected:
    private:
        std::size_t _height = 15;
        std::size_t _width = 15;
        std::vector<std::string> _arena = {};
        std::vector<std::string> _snakeMap = {};
        std::vector<SnakeBody*> _snake;
        std::vector<std::string> _ascii = {};
        Apple _apple = Apple();
        Apple _banana = Apple();
        keyPressed _key = NOTHING;
        std::clock_t _clock = std::clock();
        float _tickRate = 0.40;
        float _tickSub = 0.02;
        float _maxTick = 0.25;
        // float _tmpTick = this->_tickRate;
        int score = -100;
        std::clock_t _bananaClock = std::clock();
        float _bananaTick = 5.0;
        size_t _counter = 0;
        bool _fst = true;
};

#endif /* !SNAKE_HPP_ */
