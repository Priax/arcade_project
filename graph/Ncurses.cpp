/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-arcade-vincent.montero-fontaine
** File description:
** Ncurses
*/

#include "Ncurses.hpp"

arcade::Ncurses::Ncurses()
{
    initscr();
    curs_set(0);
    keypad(stdscr, TRUE);
    this->initColors();
}

arcade::Ncurses::~Ncurses()
{
    endwin();
}

void arcade::Ncurses::initColors()
{
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_WHITE);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    init_pair(4, COLOR_BLACK, COLOR_RED);
    init_pair(5, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(6, COLOR_CYAN, COLOR_CYAN);
    init_pair(7, COLOR_RED, COLOR_RED);
    init_pair(8, COLOR_BLUE, COLOR_BLUE);
    init_pair(9, COLOR_YELLOW, COLOR_YELLOW);
}

void arcade::Ncurses::gameEndEvents(GameState &gs)
{
    int key;

    nodelay(stdscr, TRUE);
    key = getch();
    nodelay(stdscr, FALSE);

    switch (key)
    {
        case 27: //?ESC KEY
            gs.setState(STOP);
            break;
        case 10: //?ENTER KEY
            gs.setState(GAME_START);
            break;
        case 9: //?TAB KEY
            gs.setState(ARCADE_MENU);
            break;
        default:
            break;
    }
}

void arcade::Ncurses::displayGameEnd(GameState &gs)
{
    std::string score;
    size_t i = 0, len = gs.getAscii().size();
    int x = 35, y = 5;
    double duration = (std::clock() - this->_clock) / (double) CLOCKS_PER_SEC;

    this->displayArcadeBorder();
    attron(COLOR_PAIR(3));
    while (i < len) {
        mvprintw(y, x, "%s", gs.getAscii()[i].c_str());
        y ++;
        i ++;
    }
    attron(COLOR_PAIR(1));

    if (duration >= this->_tickRate) {
        score = "SCORE: " + std::to_string(gs.getScore());
        mvprintw(14, 61, gs.win ? "GAME WON" : "GAME LOST");
        mvprintw(15, 60, "%s", score.c_str());
    }
    if (duration - this->_tickRate >= this->_idleRate) {
        this->_clock = std::clock();
    }
    attron(COLOR_PAIR(3));

    this->gameEndEvents(gs);
}

void arcade::Ncurses::displayWindow(GameState &gs)
{
    erase();
    this->_maxGame = gs.getGamesList().size() - 1;
    this->_maxGraph = gs.getGraphList().size() - 1;
    switch (gs.getState())
    {
    case arcade::screenState::ARCADE_MENU:
        this->displayArcadeMenu(gs);
        break;
    case arcade::screenState::GAME_START:
        this->displayGameStart(gs);
        break;
    case arcade::screenState::IN_GAME:
        this->displayGame(gs);
        break;
    case arcade::screenState::GAME_END:
        this->displayGameEnd(gs);
        break;
    default:
        break;
    }
    refresh();
}

void arcade::Ncurses::convertKey(GameState &gs, int key)
{
    keyPressed newKey = NOTHING;

    switch (key) {
        case KEY_RIGHT:
            newKey = RIGHT_KEY;
            break;
        case KEY_LEFT:
            newKey = LEFT_KEY;
            break;
        case KEY_UP:
            newKey = UP_KEY;
            break;
        case KEY_DOWN:
            newKey = DOWN_KEY;
            break;
        case ' ': //? SPACE KEY
            newKey = SPACE_KEY;
            break;
        default:
            break;
    }
    gs.setKey(newKey);
}

void arcade::Ncurses::gameEvents(GameState &gs)
{
    int key;

    nodelay(stdscr, TRUE);
    key = getch();
    nodelay(stdscr, FALSE);

    switch (key) {
        case 27: //? ESC KEY
            gs.setState(STOP);
            break;
        case 9: //?TAB KEY
            gs.setState(ARCADE_MENU);
            break;
        case 10: //?ENTER KEY
            gs.setState(GAME_START);
            break;
        default:
            this->convertKey(gs, key);
            break;
    }
}

void arcade::Ncurses::setCellColor(char cell)
{
    int color;

    switch (cell) {
        case WALL:
            color = 5;
            break;
        case TAIL:
            color = 8;
            break;
        case HEAD:
            color = 6;
            break;
        case APPLE:
            color = 7;
            break;
        case BANANA:
            color = 9;
            break;
        default:
            break;
    }
    attron(COLOR_PAIR(color));
}

void arcade::Ncurses::displayGame(GameState &gs)
{
    int bx = 30, x, y = 0, h = 2, w = 4;

    for (size_t i = 0; i < gs.getGameArray().size(); i ++) {
        x = bx;
        for (size_t j = 0; j < gs.getGameArray()[i].size(); j ++) {
            this->setCellColor(gs.getGameArray()[i][j]);
            for (int a = 0; a < h; a ++) {
                for (int k = 0; k < w; k ++)
                    mvaddch(y + a, x + k, ' ');
            }
            x += w;
            attron(COLOR_PAIR(3));
        }
        y += h;
    }

    mvprintw(0, 0, "SCORE: %s", std::to_string(gs.getScore()).c_str());

    this->gameEvents(gs);
}

void arcade::Ncurses::arcadeGameStartEvents(GameState &gs)
{
    int key;

    nodelay(stdscr, TRUE);
    key = getch();
    nodelay(stdscr, FALSE);

    switch (key)
    {
        case 27: //? ESC KEY
            gs.setState(STOP);
            break;
        case 10: //? ENTER KEY
            gs.setState(IN_GAME);
            break;
        case 9: //?TAB KEY
            gs.setState(ARCADE_MENU);
            break;
        default:
            break;
    }
}

void arcade::Ncurses::displayGameStart(GameState &gs)
{
    size_t i = 0, len = gs.getAscii().size();
    int x = 30, y = 5;
    double duration = (std::clock() - this->_clock) / (double) CLOCKS_PER_SEC;

    this->displayArcadeBorder();
    attron(COLOR_PAIR(3));
    while (i < len) {
        mvprintw(y, x, "%s", gs.getAscii()[i].c_str());
        y ++;
        i ++;
    }
    attron(COLOR_PAIR(1));
    if (duration >= this->_tickRate) {
        mvprintw(15, 60, "Press start...");
    }
    if (duration - this->_tickRate >= this->_idleRate) {
        this->_clock = std::clock();
    }
    attron(COLOR_PAIR(3));

    this->arcadeGameStartEvents(gs);
}

void arcade::Ncurses::usernameMenuEvent(GameState &gs)
{
    getstr(this->_username);
    gs.setUsername(this->_username);
    gs.setState(GAME_START);
}

void arcade::Ncurses::arcadeMenuEvents(GameState &gs)
{
    int key;

    nodelay(stdscr, TRUE);
    key = getch();
    nodelay(stdscr, FALSE);

    switch (key)
    {
        case 27: //? ESC KEY
            gs.setState(arcade::screenState::STOP);
            break;
        case KEY_UP:
            this->changeSelection(-1);
            break;
        case KEY_DOWN:
            this->changeSelection(1);
            break;
        case 10: //? ENTER KEY
            this->nextStep(gs);
            break;
        default:
            break;
    }
}

void arcade::Ncurses::nextStep(GameState &gs)
{
    switch (this->_step) {
        case arcade::arcadeStepMenu::GRAPH:
            gs.setGraphLib(gs.getGraphList()[this->_graphSelect]);
            this->_step = GAMES;
            break;
        case arcade::arcadeStepMenu::GAMES:
            gs.setGameLib(gs.getGamesList()[this->_gameSelect]);
            this->_step = USERNAME;
            break;
        default:
            break;
    }
}

int arcade::Ncurses::safeIncrement(int current, int max)
{
    if (current < 0)
        return max;
    if (current > max)
        return 0;
    return current;
}

void arcade::Ncurses::changeSelection(int i)
{
    switch (this->_step) {
        case arcade::arcadeStepMenu::GRAPH:
            this->_graphSelect = this->safeIncrement(this->_graphSelect + i, this->_maxGraph);
            break;
        case arcade::arcadeStepMenu::GAMES:
            this->_gameSelect = this->safeIncrement(this->_gameSelect + i, this->_maxGame);
            break;
        default:
            break;
    }
}

void arcade::Ncurses::displayUpperLine(std::string title, int color, int x, int y, int w)
{
    int i = 0;

    attron(COLOR_PAIR(color));
    mvaddch(y, x, ACS_ULCORNER);
    mvaddch(y, x + 1, ACS_HLINE);
    mvaddch(y, x + 2, ' ');
    mvprintw(y, x + 3, "%s", title.c_str());
    i = title.length() + 3;
    mvaddch(y, x + i, ' ');
    i ++;
    while (i < w) {
        mvaddch(y, x + i, ACS_HLINE);
        i ++;
    }
    mvaddch(y, x + w, ACS_URCORNER);
}

void arcade::Ncurses::displayLowerLine(int color, int x, int y, int w)
{
    attron(COLOR_PAIR(color));
    mvaddch(y, x, ACS_LLCORNER);
    for (int i = 1; i < w; i ++)
        mvaddch(y, x + i, ACS_HLINE);
    mvaddch(y, x + w, ACS_LRCORNER);
}

void arcade::Ncurses::displayLibMenu(std::string title, std::vector<std::string> lib, int select, int x, int y, int h, int w)
{
    size_t i = 0, size = lib.size();

    attron(COLOR_PAIR(3));
    displayUpperLine(title, 0, x, y, w);
    mvaddch(y + 1, x, ACS_VLINE);
    mvaddch(y + 1, x + 1, ' ');
    mvaddch(y + 1, w + x, ACS_VLINE);
    while (i + 2 < h) {
        attron(COLOR_PAIR(3));
        if (i < h - 3)
            mvaddch(y + i + 2, x, ACS_VLINE);
        if (i < size) {
            if (select == i) {
                attron(COLOR_PAIR(1));
                mvaddch(y + i + 2, x + 1, '>');
            } else {
                attron(COLOR_PAIR(3));
            }
            mvprintw(y + i + 2, x + 2, "%s", lib[i].c_str());
        }
        attron(COLOR_PAIR(3));
        if (i < h - 3)
            mvaddch(y + i + 2, x + w, ACS_VLINE);
        i ++;
    }
    y += i;
    displayLowerLine(0, x, y, w);
}

void arcade::Ncurses::displayScoresMenu(std::string title, std::map<std::string, int> scores, int x, int y, int h, int w)
{
    size_t i = 0, size = scores.size();
    std::string tmp;

    this->displayUpperLine(title, 0, x, y, w);
    mvaddch(y + 1, x, ACS_VLINE);
    mvaddch(y + 1, x + 1, ' ');
    mvaddch(y + 1, w + x, ACS_VLINE);
    for (const auto &elem : scores) {
        mvaddch(y + i + 2, x, ACS_VLINE);
        mvaddch(y + i + 2, x + 1, ' ');
        tmp = "";
        tmp += elem.first;
        tmp += ":\t";
        tmp += std::to_string(elem.second);
        mvprintw(y + i + 2, x + 2, "%s", tmp.c_str());
        mvaddch(y + i + 2, x + w, ACS_VLINE);
        i ++;
    }
    mvaddch(y + i + 2, x, ACS_VLINE);
    mvaddch(y + i + 2, x + w, ACS_VLINE);
    y = y + i + 3;
    this->displayLowerLine(0, x, y, w);
}

void arcade::Ncurses::displayUsernameMenu(std::string title, int x, int y, int h, int w)
{
    int i = 1, moy = h / 2;
    this->displayUpperLine(title, 0, x, y, w);
    while (i < h) {
        mvaddch(y + i, x, ACS_VLINE);
        mvaddch(y + i, x + 1, ' ');
        mvprintw(y + i, x + 2, "%s", this->_username);
        mvaddch(y + i, x + w, ACS_VLINE);
        i ++;
    }
    this->displayLowerLine(0, x, y + h, w);
}

void arcade::Ncurses::displayKeysInfos(int y, int x)
{
    attron(COLOR_PAIR(4));
    mvprintw(y, x, "ESCAPE \tQuit\t");
    mvprintw(y + 1, x, "UP/DOWN \tBrowse\t");
    mvprintw(y + 2, x, "ENTER \tConfirm\t");
    attron(COLOR_PAIR(3));
}

void arcade::Ncurses::displayArcadeBorder()
{
    this->displayUpperLine("ARCADE", 1, 2, 2, 125);
    for (int i = 3; i < 25; i ++) {
        mvaddch(i, 2, ACS_VLINE);
        mvaddch(i, 125 + 2, ACS_VLINE);
    }
    this->displayLowerLine(1, 2, 25, 125);
}

void arcade::Ncurses::displayArcadeMenu(GameState &gs)
{
    this->displayArcadeBorder();

    this->displayLibMenu("Graphicals", gs.getGraphList(), this->_graphSelect, 5, 6, gs.getGraphList().size() + 5, 30);
    this->displayLibMenu("Games", gs.getGamesList(), this->_gameSelect, 37, 6, gs.getGamesList().size() + 5, 30);
    this->displayUsernameMenu("Username", 69, 6, 4, 25);
    this->displayScoresMenu("Scores", gs.getGameScores(gs.getGameLib()), 96, 6, gs.getGameScores(gs.getGameLib()).size() + 5, 25);
    this->displayKeysInfos(22, 103);

    curs_set(1);
    mvaddch(8, 71, ' ');
    if (this->_step == USERNAME) {
        this->usernameMenuEvent(gs);
        curs_set(0);
        return;
    }

    this->arcadeMenuEvents(gs);
}

extern "C"
{
    arcade::IGraph *instance()
    {
        return new arcade::Ncurses();
    }
}
