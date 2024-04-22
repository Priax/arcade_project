/*
 ** EPITECH PROJECT, 2024
 ** B-OOP-400-MAR-4-1-arcade-vincent.montero-fontaine
 ** File description:
 ** SDL
 */
#include "SDL.hpp"

arcade::SDL::SDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return;
    }

    if (TTF_Init() < 0) {
        std::cerr << "SDL_ttf initialization failed: " << TTF_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    _window = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1500, 900, SDL_WINDOW_SHOWN);
    if (_window == nullptr) {
        std::cerr << "Failed to create SDL window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (_renderer == nullptr) {
        std::cerr << "Failed to create SDL renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(_window);
        SDL_Quit();
        return;
    }

    _font = TTF_OpenFont("./ressources/ThaleahFat.ttf", 24);
    if (_font == nullptr) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        SDL_DestroyRenderer(_renderer);
        SDL_DestroyWindow(_window);
        SDL_Quit();
        return;
    }
    _state = GAME_LIB;
    _textXOffset = 50;
    _textYOffset = 10;
    _rectXOffset = 45;
    _rectYOffset = 0;
    _spacing = 50;
    _wall_texture = loadTexture("ressources/wall.jpg", _renderer);
    if (_wall_texture == nullptr) {
        std::cerr << "Failed to load texture!" << std::endl;
        SDL_DestroyRenderer(_renderer), SDL_DestroyWindow(_window);
        TTF_CloseFont(_font), SDL_Quit();
        throw Error("Couldn't load texture", "Wall.jpg");
    }
    _apple_texture = loadTexture("ressources/apple.png", _renderer);
    if (_apple_texture == nullptr) {
        SDL_DestroyRenderer(_renderer), SDL_DestroyWindow(_window);
        TTF_CloseFont(_font), SDL_DestroyTexture(_wall_texture), SDL_Quit();
        std::cerr << "Failed to load texture!" << std::endl;
        throw Error("Couldn't load texture", "Apple.jpg");
    }
    _yellow_apple_texture = loadTexture("ressources/yellow_apple.png", _renderer);
    if (_yellow_apple_texture == nullptr) {
        SDL_DestroyRenderer(_renderer), SDL_DestroyWindow(_window);
        TTF_CloseFont(_font), SDL_DestroyTexture(_wall_texture);
        SDL_DestroyTexture(_apple_texture), SDL_Quit();
        std::cerr << "Failed to load texture!" << std::endl;
        throw Error("Couldn't load texture", "yellow_apple.jpg");
    }
    _snake_texture = loadTexture("ressources/block.png", _renderer);
    if (_snake_texture == nullptr) {
        SDL_DestroyRenderer(_renderer), SDL_DestroyWindow(_window);
        TTF_CloseFont(_font), SDL_DestroyTexture(_wall_texture), SDL_DestroyTexture(_apple_texture);
        SDL_Quit();
        std::cerr << "Failed to load texture!" << std::endl;
        throw Error("Couldn't load texture", "block.png");
    }
    _head_texture = loadTexture("ressources/head.png", _renderer);
}

arcade::SDL::~SDL()
{
    TTF_CloseFont(_font);
    SDL_DestroyRenderer(_renderer);
    TTF_Quit();
    SDL_Quit();
    SDL_DestroyTexture(_wall_texture);
    SDL_DestroyTexture(_apple_texture);
    SDL_DestroyWindow(_window);
}

void arcade::SDL::displayWindow(GameState &gs)
{
    switch (gs.getState()) {
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
            //! FAIRE LE MENU DE GAME OVER
            this->gameOverMenu(gs);
            break;
        default:
            break;
    }
}

void arcade::SDL::gameOverMenu(GameState &gs)
{
    SDL_Event event;

    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            gs.setState(arcade::screenState::STOP);
        }
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    gs.setState(arcade::screenState::STOP);
                    break;
                case SDLK_RETURN:
                    std::cout << "Game should restart" << std::endl;
                    gs.setState(arcade::screenState::GAME_START);
                    break;
                case SDLK_TAB:
                    std::cout << "Returning to menu" << std::endl;
                    gs.setState(arcade::screenState::ARCADE_MENU);
                    break;
                default:
                    break;
            }
        }
        SDL_RenderClear(_renderer);
    }
}

void arcade::SDL::renderUserInput(const std::string &text, const SDL_Color &color, int x, int y)
{
    SDL_Surface *textSurface = TTF_RenderText_Solid(_font, text.c_str(), color);
    if (textSurface == nullptr) {
        std::cerr << "Failed to render text surface: " << TTF_GetError() << std::endl;
        return;
    }
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(_renderer, textSurface);
    if (textTexture == nullptr) {
        std::cerr << "Failed to create text texture: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(textSurface);
        return;
    }
    SDL_Rect textRect = {x, y, textSurface->w, textSurface->h};
    SDL_RenderCopy(_renderer, textTexture, nullptr, &textRect);
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
}

void arcade::SDL::renderRect(SDL_Renderer *renderer, const SDL_Rect &rect, const SDL_Color &color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawRect(renderer, &rect);
}

std::ostream &operator<<(std::ostream &os, const arcade::SDL::Menu_State &state)
{
    switch (state) {
        case arcade::SDL::GRAPH_LIB:
            os << "GRAPH_LIB";
            break;
        case arcade::SDL::GAME_LIB:
            os << "GAME_LIB";
            break;
        case arcade::SDL::TYP_USR:
            os << "TYP_USR";
            break;
        case arcade::SDL::DEFAULT:
            os << "DEFAULT";
            break;
        default:
            os << "Unknown state";
            break;
    }
    return os;
}

void arcade::SDL::handle_typing(SDL_Event &event, std::string &inputText, std::string &savedText)
{
    switch (event.key.keysym.sym) {
        case SDLK_BACKSPACE:
            if (!inputText.empty()) {
                inputText.pop_back();
            }
            break;
        case SDLK_RETURN:
            savedText = inputText;
            inputText.clear();
            break;
        default:
            if (event.key.keysym.sym >= SDLK_SPACE && event.key.keysym.sym <= 126
                && event.key.keysym.sym != '\n') {
                bool shiftPressed = (event.key.keysym.mod & KMOD_SHIFT) != 0;
                char keyPressed = event.key.keysym.sym;
                if (shiftPressed && keyPressed >= 'a' && keyPressed <= 'z') {
                    keyPressed -= ('a' - 'A');
                }
                inputText += keyPressed;
            }
            break;
    }
}

void arcade::SDL::move_rectangle(SDL_Event &event, SDL_Rect &myRect, int numItems)
{
    switch (event.key.keysym.sym) {
        case SDLK_UP:
            myRect.y -= _spacing;
            if (myRect.y < _rectYOffset)
                myRect.y = (numItems - 1) * _spacing;
            break;
        case SDLK_DOWN:
            myRect.y += _spacing;
            if (myRect.y >= _rectYOffset + numItems * _spacing)
                myRect.y = _rectYOffset;
            break;
        default:
            break;
    }
}

void arcade::SDL::render_sdl(GameState &gs, std::string &inputText, SDL_Rect myRect, SDL_Color rectColor, SDL_Color textColor, std::vector<std::string> Libs)
{
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);

    SDL_Surface *image = SDL_LoadBMP("ressources/background.bmp");
    if (image == NULL) {
        throw Error("No Background", "background.bmp");
    } else {
        SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, image);
        if (texture == NULL) {
            throw Error("Couldn't load texture", "image background in render_sdl");
        } else {
            SDL_RenderCopy(_renderer, texture, NULL, NULL);
            SDL_DestroyTexture(texture);
        }
        SDL_FreeSurface(image);
    }
    if (_state == TYP_USR) {
        render_text("Enter your name here: ", textColor, _textXOffset + 160, _textYOffset + 110, 20, 1000);
        if (!inputText.empty()) {
            renderUserInput(inputText, textColor, _textXOffset + 160, _textYOffset + 110 + 25);
        }
    } else {
        render_vector(Libs, textColor, _textXOffset + 160, _textYOffset + 110);
        renderRect(_renderer, {myRect.x + _rectXOffset + 110, myRect.y + _rectYOffset + 110, myRect.w, myRect.h}, rectColor);
    }
    std::map<std::string, int> Scores = gs.getGameScores(gs.getGameLib());
    int scoreX = _textXOffset + 160 + 300;
    int scoreY = _textYOffset + 110;
    int scoreSpacing = 20;

    for (const auto &score : Scores) {
        render_text(score.first + ":  " + std::to_string(score.second), textColor, scoreX, scoreY, 20, 1000);
        scoreY += scoreSpacing;
    }
    SDL_RenderPresent(_renderer);
    SDL_Delay(10);
}

void arcade::SDL::render_text(const std::string &text, const SDL_Color &color, int x, int y, int fontSize, int maxWidth)
{
    TTF_Font* font = TTF_OpenFont("ressources/ThaleahFat.ttf", fontSize);
    if (!font) {
        throw Error("Couldn't load font", "font");
        return;
    }

    SDL_Surface *surface = TTF_RenderText_Blended_Wrapped(font, text.c_str(), color, maxWidth);
    TTF_CloseFont(font);

    if (!surface) {
        throw Error("Couldn't create text surface", "surface");
        return;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, surface);
    if (!texture) {
        SDL_FreeSurface(surface);
        throw Error("Couldn't create text texture", "texture");
        return;
    }

    SDL_Rect destRect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(_renderer, texture, nullptr, &destRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void arcade::SDL::render_vector(const std::vector<std::string> &vec, const SDL_Color &textColor, int x, int y)
{
    int yPos = y + _textYOffset;
    int maxWidth = 0;

    for (const auto &element : vec) {
        int textWidth, textHeight;
        TTF_SizeText(_font, element.c_str(), &textWidth, &textHeight);
        maxWidth = std::max(maxWidth, textWidth);
    }
    int totalHeight = vec.size() * _spacing;
    SDL_Rect yellowRect = {x - 5, yPos - 5, maxWidth + 10, totalHeight - 10};
    SDL_SetRenderDrawColor(_renderer, 255, 125, 255, 255);
    SDL_RenderFillRect(_renderer, &yellowRect);
    yPos = y + _textYOffset;
    for (const auto &element : vec) {
        render_text(element, textColor, x, yPos, 20, maxWidth);
        yPos += _spacing;
    }
}

SDL_Texture *arcade::SDL::loadTexture(const std::string &path, SDL_Renderer *renderer)
{
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        throw Error("Couldn't load texture", path.c_str());
        return nullptr;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (texture == nullptr) {
        throw Error("Couldn't load texture", "loadedSurface");
    }
    SDL_FreeSurface(loadedSurface);
    return texture;
}

void arcade::SDL::displayGame(GameState &gs)
{
    SDL_Event event;
    int windowWidth, windowHeight;
    SDL_GetWindowSize(_window, &windowWidth, &windowHeight);

    int tileSize = 32;
    int mapWidth = gs.getGameArray()[0].size() * tileSize;
    int mapHeight = gs.getGameArray().size() * tileSize;

    int xMargin = (windowWidth - mapWidth) / 2;
    int yMargin = (windowHeight - mapHeight) / 2;

    SDL_Color textColor = {255, 255, 255, 0};

    render_text("Score: " + std::to_string(gs.getScore()), textColor, 500, 0, 30, 1000);

    int x = xMargin, y = yMargin;

    for (size_t i = 0; i < gs.getGameArray().size(); i++) {
        x = xMargin;
        for (size_t j = 0; j < gs.getGameArray()[i].size(); j++) {
            switch (gs.getGameArray()[i][j]) {
                case '#':
                    renderSprite(x, y, _wall_texture);
                    break;
                case 'O':
                    renderSprite(x, y, _apple_texture);
                    break;
                case '0':
                    renderSprite(x, y, _yellow_apple_texture);
                    break;
                case 'H':
                    renderSprite(x, y, _snake_texture);
                    break;
                case 'D':
                    renderSprite(x, y, _head_texture);
                    break;
                default:
                    break;
            }
            x += tileSize;
        }
        y += tileSize;
    }
    this->gameEvents(gs, event);
    SDL_RenderPresent(_renderer);
    SDL_RenderClear(_renderer);
}


void arcade::SDL::gameEvents(GameState &gs, SDL_Event event)
{
    keyPressed newKey = NOTHING;

    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            gs.setState(arcade::screenState::STOP);
        }
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    gs.setState(arcade::screenState::STOP);
                    break;
                case SDLK_RIGHT:
                    newKey = RIGHT_KEY;
                    break;
                case SDLK_UP:
                    newKey = UP_KEY;
                    break;
                case SDLK_DOWN:
                    newKey = DOWN_KEY;
                    break;
                case SDLK_LEFT:
                    newKey = LEFT_KEY;
                    break;
                case SDLK_TAB:
                    gs.setState(arcade::screenState::ARCADE_MENU);
                    break;
                case SDLK_RETURN:
                    gs.setState(arcade::screenState::GAME_START);
                    break;
                default:
                    break;
            }
        }
    }
    gs.setKey(newKey);
}

void arcade::SDL::renderSprite(int x, int y, SDL_Texture *texture)
{
    SDL_Rect destRect = {x, y, 32, 32};
    SDL_RenderCopy(_renderer, texture, NULL, &destRect);
}

void arcade::SDL::renderSprite(int x, int y, SDL_Texture *texture, SDL_Rect* srcRect)
{
    SDL_Rect destRect = {x, y, 32, 32};
    SDL_RenderCopy(_renderer, texture, srcRect, &destRect);
}

void arcade::SDL::displayGameStart(GameState &gs)
{
    SDL_Event event;

    Uint32 textStartTime = SDL_GetTicks();
    Uint32 elapsedTime = 0;
    Uint32 flickerInterval = 800;
    bool renderText = true;
    SDL_Color textColor = {255, 255, 255, 0};

    while (_window && gs.getState() != arcade::screenState::IN_GAME
        && gs.getState() != arcade::screenState::STOP) {

        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                gs.setState(arcade::screenState::STOP);
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    gs.setState(arcade::screenState::STOP);
                }
                if (event.key.keysym.sym == SDLK_RETURN) {
                    gs.setState(arcade::screenState::IN_GAME);
                }
            }
        }
        elapsedTime = SDL_GetTicks() - textStartTime;
        if (renderText && elapsedTime >= flickerInterval) {

             int windowWidth, windowHeight;
            SDL_GetWindowSize(_window, &windowWidth, &windowHeight);

            int textX = (windowWidth - (_textXOffset + 350)) / 2;
            int textY = (windowHeight - (_textYOffset - 350)) / 2;

            render_text("Press enter key.", textColor, textX, textY, 50, 1000);
            SDL_RenderPresent(_renderer);
            renderText = false;
            textStartTime = SDL_GetTicks();
        } else if (!renderText && elapsedTime >= flickerInterval / 2) {
            SDL_RenderClear(_renderer);
            SDL_RenderPresent(_renderer);
            renderText = true;
            textStartTime = SDL_GetTicks();
        }
        SDL_Delay(10);
    }
}

void arcade::SDL::chooseLib(GameState &gs, SDL_Event event, SDL_Rect myRect,
    size_t *currentListIndex, std::vector<std::vector<std::string>> allLists)
{
    if (event.key.keysym.sym == SDLK_RETURN) {
        switch (_state) {
            case arcade::SDL::Menu_State::GAME_LIB:
                gs.setGameLib(allLists[*currentListIndex][myRect.y / _spacing]);
                break;
            case arcade::SDL::Menu_State::GRAPH_LIB:
                gs.setGraphLib(allLists[*currentListIndex][myRect.y / _spacing]);
                break;
            default:
                break;
        }
        if (*currentListIndex < allLists.size() - 1) {
            *currentListIndex = (static_cast<int>(_state) + 1) % (DEFAULT + 1);
            myRect.y = 0;
        }
        _state = static_cast<Menu_State>((static_cast<int>(_state) + 1) % (DEFAULT + 1));
    }
}

void arcade::SDL::displayArcadeMenu(GameState &gs)
{
    SDL_Event event;
    SDL_Color textColor = {255, 255, 255, 0};
    SDL_Rect myRect = {45, 0, 250, 50};

    SDL_Color rectColor = {255, 0, 0, 255};

    std::string inputText, savedText;
    std::vector<std::vector<std::string>> allLists = {gs.getGamesList(), gs.getGraphList()};
    //std::map<std::string, int> Scores = gs.getScores();
    //std::map<std::string, int> Scores = gs.getGameScores(gs.getGameLib());
    size_t currentListIndex = 0;
    std::string selectedValue;

    while (gs.getState() != arcade::screenState::STOP && _window && gs.getState() != arcade::screenState::GAME_START) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                gs.setState(arcade::screenState::STOP);
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    gs.setState(arcade::screenState::STOP);
                }
                if (_state == TYP_USR) {
                    handle_typing(event, inputText, savedText);
                    if (event.key.keysym.sym == SDLK_RETURN) {
                        gs.setUsername(savedText);
                        gs.setState(arcade::screenState::GAME_START);
                        break;
                    }
                } else if (_state != TYP_USR) {
                    move_rectangle(event, myRect, allLists[currentListIndex].size());
                    chooseLib(gs, event, myRect, &currentListIndex, allLists);
                }
            }
        }
        render_sdl(gs, inputText, myRect, rectColor, textColor, allLists[currentListIndex]);
    }
}

extern "C"
{
    arcade::IGraph *instance() {
        return new arcade::SDL();
    }
}
