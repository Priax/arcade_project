/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-arcade-vincent.montero-fontaine
** File description:
** Snake
*/

#include "Snake.hpp"

arcade::Snake::Snake() : _arena(_height), _snakeMap(_height)
{
    this->initArena();
    this->initSnake(BASE_LENGTH);
    this->updateSnakeMap();
    this->setAscii();
}

arcade::Snake::~Snake()
{
    // size_t i = 0, size = this->_snake.size();

    // while (i < size)
    //     delete this->_snake[i];
}

void arcade::Snake::setAscii()
{
    std::ifstream file(SNAKE_COVER);
    std::string line;
    this->_ascii.clear();

    while (std::getline(file, line)) {
        this->_ascii.push_back(line);
    }
}

void arcade::Snake::initSnake(size_t length)
{
    size_t x = this->_width / 2;
    size_t y = this->_height / 2;

    for (int i = 0; i < length; i ++) {
        this->_snake.push_back(new SnakeBody(x - i, y));
    }
}

void arcade::Snake::displaySnake()
{
    size_t i = 0, len = this->_snake.size();

    while (i < len) {
        std::cout
        << "Index = " << i
        << "(" << this->_snake[i]->getX() << ";"
        << this->_snake[i]->getY() << ")\n";
        i ++;
    }
}

void arcade::Snake::extendSnake()
{
    SnakeBody *tail = new SnakeBody(0, 0);
    tail->setVisible(false);

    this->_snake.push_back(tail);
}

void arcade::Snake::initArena()
{
    char cell;
    for (int i = 0; i < this->_height; i ++) {
        this->_arena[i] = "";
        for (int j = 0; j < this->_width; j ++) {
            if (i == 0 || i == this->_height - 1) {
                cell = WALL;
            }
            else if (j == 0 || j == this->_width - 1) {
                cell = WALL;
            } else {
                cell = EMPTY;
            }
            this->_arena[i] += cell;
        }
    }
}

void arcade::Snake::displayMap(std::vector<std::string> map)
{
    size_t i = 0, size = map.size();

    while (i < size) {
        std::cout << map[i] << std::endl;
        i ++;
    }
}

void arcade::Snake::updateTick()
{
    // this->_tmpTick -= this->_tickSub;
    if (this->_tickRate <= this->_maxTick) {
        this->_tickRate = this->_maxTick;
        return;
    }
    this->_tickRate -= this->_tickSub;
}

void arcade::Snake::updateArena()
{
    char snakePart;
    size_t i = 0, size = this->_arena.size();

    while (i < size) {
        this->_snakeMap[i] = this->_arena[i];
        i ++;
    }

    i = 0, size = this->_snake.size();
    while (i < size) {
        if (this->_snake[i]->isVisible() == false) {
            i ++;
            continue;
        }
        snakePart = (i == 0) ? HEAD : TAIL;
        this->_snakeMap[this->_snake[i]->getY()][this->_snake[i]->getX()] = snakePart;
        i ++;
    }
}

void arcade::Snake::updateApple()
{
        if (this->_apple.isEaten() && !this->isGigantic()) {
        this->updateTick();
        this->score += APPLE_POINTS;
        do {
            this->_apple.setRandomXY(this->_width, this->_height);
        }
        while (this->_snakeMap[this->_apple.getY()][this->_apple.getX()] != EMPTY);
    }
    this->_apple.setStatus(false);
    this->_snakeMap[this->_apple.getY()][this->_apple.getX()] = APPLE;
}

void arcade::Snake::updateBanana()
{
    double duration = (std::clock() - this->_bananaClock) / (double) CLOCKS_PER_SEC;
    if (this->_banana.isEaten() && !this->isGigantic()) {
        do {
            this->_banana.setRandomXY(this->_width, this->_height);
        }
        while (this->_snakeMap[this->_banana.getY()][this->_banana.getX()] != EMPTY);
    }

    if (duration >= this->_bananaTick) {
        if (this->_banana.isEaten()) {
            // this->updateTick(); //? on augmente pas le tick si c'est une banane
            this->_bananaClock = std::clock();
            if (this->_fst) {
                this->_fst = false;
            } else {
                this->score += BANANA_POINTS;
            }
        }
        this->_banana.setStatus(false);
        this->_snakeMap[this->_banana.getY()][this->_banana.getX()] = BANANA;
    }
}

void arcade::Snake::updateSnake()
{
    char snakePart;
    size_t i = 0, size = this->_snake.size();
    while (i < size) {
        if (this->_snake[i]->isVisible() == false) {
            i ++;
            continue;
        }
        snakePart = (i == 0) ? HEAD : TAIL;
        this->_snakeMap[this->_snake[i]->getY()][this->_snake[i]->getX()] = snakePart;
        i ++;
    }
}

void arcade::Snake::updateSnakeMap()
{
    this->updateArena();
    this->updateApple();
    this->updateBanana();
    this->updateSnake();

    this->_snakeMap[0][0] = this->_arena[0][0];
}

void arcade::Snake::updateSnakePosition()
{
    size_t i = this->_snake.size() - 1;

    while (i > 0) {
        this->_snake[i]->setVisible(true);
        this->_snake[i]->setX(this->_snake[i - 1]->getX());
        this->_snake[i]->setY(this->_snake[i - 1]->getY());
        i --;
    }
    switch (this->_snake[0]->getDirection()) {
        case UP:
            this->_snake[0]->setY(this->_snake[0]->getY() - 1);
            break;
        case DOWN:
            this->_snake[0]->setY(this->_snake[0]->getY() + 1);
            break;
        case RIGHT:
            this->_snake[0]->setX(this->_snake[0]->getX() + 1);
            break;
        case LEFT:
            this->_snake[0]->setX(this->_snake[0]->getX() - 1);
            break;
        default:
            break;
    }
}

void arcade::Snake::updateSnakeDirection(keyPressed key)
{
    switch (this->_snake[0]->getDirection()) {
        case LEFT:
        case RIGHT:
            if (key == UP_KEY)
                this->_snake[0]->setDirection(UP);
            if (key == DOWN_KEY)
                this->_snake[0]->setDirection(DOWN);
            break;
        case UP:
        case DOWN:
            if (key == LEFT_KEY)
                this->_snake[0]->setDirection(LEFT);
            if (key == RIGHT_KEY)
                this->_snake[0]->setDirection(RIGHT);
            break;
        default:
            break;
    }
}

// void arcade::Snake::setupSpeed()
// {
//     this->_tmpTick = this->_tickRate;
//     this->_tickRate = this->_maxTick;
// }

void arcade::Snake::keyEvents(keyPressed key)
{
    switch (key) {
        // case SPACE_KEY:
        //     this->setupSpeed();
            // return;
        default:
            break;
    }
    // this->_tickRate = this->_tmpTick;
}

bool arcade::Snake::isOuroboros()
{
    int x = this->_snake[0]->getX();
    int y = this->_snake[0]->getY();
    size_t i = 1, len = this->_snake.size();

    while (i < len) {
        if (this->_snake[i]->getX() == x && this->_snake[i]->getY() == y)
            return true;
        i ++;
    }
    return false;
}

bool arcade::Snake::isParpaing()
{
    int x = this->_snake[0]->getX();
    int y = this->_snake[0]->getY();

    if (this->_arena[y][x] == WALL)
        return true;
    return false;
}

bool arcade::Snake::isGigantic()
{
    int i = 0, j, size = this->_snakeMap.size();

    while (i < size) {
        j = 0;
        while (j < this->_snakeMap[i].size()) {
            if (
                this->_snakeMap[i][j] == EMPTY ||
                this->_snakeMap[i][j] == APPLE ||
                this->_snakeMap[i][j] == BANANA
                ) {
                return false;
            }
            j ++;
        }
        i ++;
    }
    return true;
}

bool arcade::Snake::isEatingApple()
{
    int x = this->_snake[0]->getX();
    int y = this->_snake[0]->getY();

    if (this->_apple.isEaten())
        return false;
    if (x == this->_apple.getX() && y == this->_apple.getY()) {
        this->_apple.setStatus(true);
        return true;
    }
    if (this->_banana.isEaten())
        return false;
    if (x == this->_banana.getX() && y == this->_banana.getY()) {
        this->_banana.setStatus(true);
        return true;
    }
    return false;
}

void arcade::Snake::updateGameStart(GameState &gs)
{
    gs.setAscii(this->_ascii);
}

void arcade::Snake::updateGame(GameState &gs)
{
    double duration;

    this->_key = (gs.getKey() == NOTHING) ? this->_key : gs.getKey();
    gs.setScore(this->score);

    if (this->isGigantic()) {
        gs.setState(GAME_END);
        gs.win = true;
        return;
    }

    if (this->isOuroboros() || this->isParpaing()) {
        gs.setState(GAME_END);
        gs.win = false;
        return;
    }

    duration = (std::clock() - this->_clock) / (double) CLOCKS_PER_SEC;
    if (duration >= this->_tickRate) {
        this->updateSnakeDirection(this->_key);
        this->updateSnakePosition();
        this->_clock = std::clock();
    }

    if (this->isEatingApple()) {
        this->extendSnake();
    }

    this->updateSnakeMap();
    gs.setGameArray(this->_snakeMap);
}

void arcade::Snake::updateGameState(GameState &gs)
{
    switch (gs.getState()) {
        case GAME_START:
            this->updateGameStart(gs);
            break;
        case IN_GAME:
            this->updateGame(gs);
            break;
        default:
            break;
    }
}

SnakeBody::SnakeBody(size_t x, size_t y)
{
    this->y = y;
    this->x = x;
}

SnakeBody::~SnakeBody()
{
}

size_t SnakeBody::getX()
{
    return this->x;
}

size_t SnakeBody::getY()
{
    return this->y;
}

Direction SnakeBody::getDirection()
{
    return this->_direction;
}

void SnakeBody::setX(size_t x)
{
    this->x = x;
}

void SnakeBody::setY(size_t y)
{
    this->y = y;
}

void SnakeBody::setDirection(Direction direction)
{
    this->_direction = direction;
}

void SnakeBody::setVisible(bool v)
{
    this->_visible = v;
}

bool SnakeBody::isVisible()
{
    return this->_visible;
}

Apple::Apple()
{
    std::srand(std::time(nullptr));
}

Apple::~Apple()
{
}

size_t Apple::getX()
{
    return this->_x;
}

size_t Apple::getY()
{
    return this->_y;
}

void Apple::setX(size_t x)
{
    this->_x = x;
}

void Apple::setY(size_t y)
{
    this->_y = y;
}

void Apple::setRandomXY(int maxX, int maxY)
{
    this->_x = std::rand() % maxX;
    this->_y = std::rand() % maxY;
}

bool Apple::isEaten()
{
    return this->_eaten;
}

void Apple::setStatus(bool status)
{
    this->_eaten = status;
}

extern "C"
{
    arcade::IGame *instance()
    {
        return new arcade::Snake();
    }
}
