/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-arcade-vincent.montero-fontaine
** File description:
** Nibbler
*/

#include "Nibbler.hpp"

arcade::Nibbler::Nibbler() : _arena(_height), _snakeMap(_height)
{
    this->initArena();
    this->initSnake(BASE_LENGTH);
    this->updateSnakeMap();
    this->setAscii();
    this->initApples(MAX_APPLES_NIBBLER);
    this->_banana.setStatus(true);
}

arcade::Nibbler::~Nibbler()
{
    // size_t i = 0, size = this->_snake.size();

    // while (i < size)
    //     delete this->_snake[i];
    //? free apples
}

void arcade::Nibbler::setAscii()
{
    std::ifstream file(NIBBLER_COVER);
    std::string line;
    this->_ascii.clear();

    while (std::getline(file, line)) {
        this->_ascii.push_back(line);
    }
}

void arcade::Nibbler::initSnake(size_t length)
{
    size_t x = 5;
    size_t y = this->_height - 2;

    for (int i = 0; i < length; i ++) {
        this->_snake.push_back(new SnakeBody(x - i, y));
    }
}

void arcade::Nibbler::displaySnake()
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

void arcade::Nibbler::extendSnake()
{
    SnakeBody *tail = new SnakeBody(0, 0);
    tail->setVisible(false);

    this->_snake.push_back(tail);
}

void arcade::Nibbler::initArena()
{
    this->_arena = {
        "###################",
        "#                 #",
        "# ### # ### # ### #",
        "#     #     #     #",
        "# ### # ### # ### #",
        "# #             # #",
        "# # ### ### ### # #",
        "#   #   #_#   #   #",
        "# # # # ### # # # #",
        "#     #     #     #",
        "# # # # ### # # # #",
        "#   #   #_#   #   #",
        "# # ### ### ### # #",
        "# #             # #",
        "# ### # ### # ### #",
        "#     #     #     #",
        "# ### # ### # ### #",
        "#                 #",
        "###################"
    };

    this->_snakeMap = {
        "###################",
        "#                 #",
        "# ### # ### # ### #",
        "#     #     #     #",
        "# ### # ### # ### #",
        "# #             # #",
        "# # ### ### ### # #",
        "#   #   # #   #   #",
        "# # # # ### # # # #",
        "#     #     #     #",
        "# # # # ### # # # #",
        "#   #   # #   #   #",
        "# # ### ### ### # #",
        "# #             # #",
        "# ### # ### # ### #",
        "#     #     #     #",
        "# ### # ### # ### #",
        "#                 #",
        "###################"
    };
}

void arcade::Nibbler::displayMap(std::vector<std::string> map)
{
    size_t i = 0, size = map.size();

    while (i < size) {
        std::cout << map[i] << std::endl;
        i ++;
    }
}

void arcade::Nibbler::updateTick()
{
    // this->_tmpTick -= this->_tickSub;
    if (this->_tickRate <= this->_maxTick) {
        this->_tickRate = this->_maxTick;
        return;
    }
    this->_tickRate -= this->_tickSub;
}

void arcade::Nibbler::updateArena()
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

bool arcade::Nibbler::isAnEmptyCase(Apple* apple)
{
    size_t i = 0, size = this->_apples.size();

    while (i < size) {
        if (this->_apples[i]->getX() == apple->getX() && this->_apples[i]->getY() == apple->getY())
            return false;
        i ++;
    }
    if (this->_snakeMap[apple->getY()][apple->getX()] != EMPTY)
        return false;
    return true;
}

void arcade::Nibbler::initApples(int n)
{
    int i = 0;
    Apple* tmp = NULL;

    while (i < n) {
        tmp = new Apple;
        do {
            tmp->setRandomXY(this->_width, this->_height);
        }
        while (!this->isAnEmptyCase(tmp));
        this->_apples.push_back(tmp);
        i ++;
    }
}

void arcade::Nibbler::updateApples()
{
    //     if (this->_apple.isEaten() && !this->isGigantic()) {
    //     this->updateTick();
    //     this->score += APPLE_POINTS;
    //     do {
    //         this->_apple.setRandomXY(this->_width, this->_height);
    //     }
    //     while (this->_snakeMap[this->_apple.getY()][this->_apple.getX()] != EMPTY);
    // }
    // this->_apple.setStatus(false);
    // this->_snakeMap[this->_apple.getY()][this->_apple.getX()] = APPLE;

    size_t i = 0, size = this->_apples.size();
    int x = this->_snake[0]->getX();
    int y = this->_snake[0]->getY();

    while (i < size) {
        if (!this->_apples[i]->isEaten()) {
            if (this->_apples[i]->getX() == x && this->_apples[i]->getY() == y) {
            this->_apples[i]->setStatus(true);
            this->score += APPLE_POINTS;
            this->updateTick();
            this->extendSnake();
            } else {
                this->_snakeMap[this->_apples[i]->getY()][this->_apples[i]->getX()] = APPLE;
            }
        }
        i ++;
    }
}

void arcade::Nibbler::updateBanana()
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
            if (!this->_fst) {
                this->_fst = true;
            } else {
                this->score += BANANA_POINTS;
            }
        }
        this->_banana.setStatus(false);
        this->_snakeMap[this->_banana.getY()][this->_banana.getX()] = BANANA;
    }
}

void arcade::Nibbler::updateSnake()
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

bool arcade::Nibbler::areAllApplesEaten()
{
    size_t i = 0, size = this->_apples.size();

    while (i < size) {
        if (!this->_apples[i]->isEaten())
            return false;
        i ++;
    }
    return true;
}

void arcade::Nibbler::updateSnakeMap()
{
    this->updateArena();
    this->updateApples();
    this->updateBanana();
    this->updateSnake();

    this->_snakeMap[0][0] = this->_arena[0][0];
}

void arcade::Nibbler::updateSnakePosition()
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

void arcade::Nibbler::updateSnakeDirection(keyPressed key)
{
    Direction dir = this->_snake[0]->getDirection();

    switch (dir) {
        case LEFT:
        case RIGHT:
            if (key == UP_KEY) {
                this->_snake[0]->setDirection(UP);
                if (this->isParpaing()) {
                    this->_snake[0]->setDirection(dir);
                    break;
                }
                this->_stop = false;
            } else if (key == DOWN_KEY) {
                this->_snake[0]->setDirection(DOWN);
                if (this->isParpaing()) {
                    this->_snake[0]->setDirection(dir);
                    break;
                }
                this->_stop = false;
            }
            break;
        case UP:
        case DOWN:
            if (key == LEFT_KEY) {
                this->_snake[0]->setDirection(LEFT);
                if (this->isParpaing()) {
                    this->_snake[0]->setDirection(dir);
                    break;
                }
                this->_stop = false;
            } else if (key == RIGHT_KEY) {
                this->_snake[0]->setDirection(RIGHT);
                if (this->isParpaing()) {
                    this->_snake[0]->setDirection(dir);
                    break;
                }
                this->_stop = false;
            }
            break;
        default:
            return;
    }
}

// void arcade::Nibbler::setupSpeed()
// {
//     this->_tmpTick = this->_tickRate;
//     this->_tickRate = this->_maxTick;
// }

void arcade::Nibbler::keyEvents(keyPressed key)
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

bool arcade::Nibbler::isOuroboros()
{
    int x = this->_snake[0]->getX();
    int y = this->_snake[0]->getY();

    if (this->_snakeMap[y][x] == TAIL)
        return true;
    return false;
}

bool arcade::Nibbler::isParpaing()
{
    int x = this->_snake[0]->getX();
    int y = this->_snake[0]->getY();

    switch (this->_snake[0]->getDirection()) {
        case UP:
            y += -1;
            break;
        case DOWN:
            y += 1;
            break;
        case RIGHT:
            x += 1;
            break;
        case LEFT:
            x += -1;
            break;
        default:
            break;
    }

    if (this->_snakeMap[y][x] == WALL)
        return true;
    if (y <= 0 || y >= this->_height - 1)
        return true;
    if (x <= 0 || x >= this->_width - 1)
        return true;
    return false;
}

bool arcade::Nibbler::isGigantic()
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

bool arcade::Nibbler::isEatingApple()
{
    int x = this->_snake[0]->getX();
    int y = this->_snake[0]->getY();

    // if (this->_apple.isEaten())
    //     return false;
    // if (x == this->_apple.getX() && y == this->_apple.getY()) {
    //     this->_apple.setStatus(true);
    //     return true;
    // }
    if (this->_banana.isEaten())
        return false;
    if (x == this->_banana.getX() && y == this->_banana.getY()) {
        this->_banana.setStatus(true);
        return true;
    }
    return false;
}

void arcade::Nibbler::updateGameStart(GameState &gs)
{
    gs.setAscii(this->_ascii);
}

void arcade::Nibbler::setCorrectDirection(char a, char b, Direction i, Direction j)
{
    if (a != WALL && b != WALL) {
        this->_stop = true;
        return;
    }
    if (a != WALL && b == WALL) {
        this->_snake[0]->setDirection(i);
        return;
    }
    if (a == WALL && b != WALL) {
        this->_snake[0]->setDirection(j);
    }
}

void arcade::Nibbler::correctDirection()
{
    char a = WALL, b = WALL;
    int x = this->_snake[0]->getX();
    int y = this->_snake[0]->getY();

    switch (this->_snake[0]->getDirection()) {
        case UP:
        case DOWN:
            a = this->_snakeMap[y][x - 1];
            b = this->_snakeMap[y][x + 1];
            this->setCorrectDirection(a, b, LEFT, RIGHT);
            break;
        case LEFT:
        case RIGHT:
            a = this->_snakeMap[y - 1][x];
            b = this->_snakeMap[y + 1][x];
            this->setCorrectDirection(a, b, UP, DOWN);
            break;
        default:
            break;
    }
}

void arcade::Nibbler::displayDirection(Direction dir)
{
    std::string str;

    switch (dir)
    {
        case UP:
            str = "UP";
            break;
        case DOWN:
            str = "DOWN";
            break;
        case LEFT:
            str = "LEFT";
            break;
        case RIGHT:
            str = "RIGHT";
            break;
        default:
            str = "UNKNOWN";
            break;
    }
    std::cout << str << std::endl;
}

void arcade::Nibbler::updateGame(GameState &gs)
{
    double duration = (std::clock() - this->_clock) / (double) CLOCKS_PER_SEC;
    this->_key = (gs.getKey() == NOTHING) ? this->_key : gs.getKey();

    if (this->isGigantic() || this->areAllApplesEaten()) {
        gs.setState(GAME_END);
        gs.win = true;
        return;
    }

    this->updateSnakeMap();
    gs.setGameArray(this->_snakeMap);
    gs.setScore(this->score);

    if (!this->_stop && this->isParpaing()) {
        this->correctDirection();
        if (!this->_stop) {
            this->updateSnakePosition();
            usleep(1000000 * 0.4);
        }
        this->_key = NOTHING;
        this->updateSnakeMap();
        gs.setGameArray(this->_snakeMap);
        gs.setScore(this->score);
        return;
    }
    else if (this->isOuroboros()) {
        gs.setState(GAME_END);
        gs.win = false;
        return;
    }

    if (duration >= this->_tickRate) {
        this->updateSnakeDirection(this->_key);
        if (!this->_stop)
            this->updateSnakePosition();
        this->_clock = std::clock();
    }

    if (this->isEatingApple()) {
        this->extendSnake();
    }

    this->updateSnakeMap();
    gs.setGameArray(this->_snakeMap);
    gs.setScore(this->score);
}

void arcade::Nibbler::updateGameState(GameState &gs)
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
        return new arcade::Nibbler();
    }
}
