/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-arcade-vincent.montero-fontaine
** File description:
** Game
*/
#include "../SFML.hpp"

void arcade::SFML::setGameSprites(GameState &gs)
{
    if (gs.getState() == GAME_END)
    {
        _isCreated = false;
    }

    float x = sf::VideoMode::getDesktopMode().width / 2 - (gs.getGameArray().size() / 2 * 32);
    float y = sf::VideoMode::getDesktopMode().height  / 2 - (gs.getGameArray()[0].size() / 2 * 32);
    sf::Vector2f position = {x, y};
    std::string map("");
    int size = gs.getGameArray()[0].size();
    for (size_t i = 0; i < gs.getGameArray().size(); i++)
    {
            map += gs.getGameArray()[i];
    }
    for (int i = 0; i < map.size(); i++)
    {
        _GameAssets.push_back(setGameSprite(map[i]));
        _GameAssets[i].setPosition(position);
        if ((i+1) % size == 0)
        {
            position.x = x;
            position.y += 32;
        } else {
            position.x += 32;
        }
    }

}



void arcade::SFML::setGameAssets(GameState &gs)
{
    _textures.clear();
    _textFont.loadFromFile("./assets/SFML/Tag.ttf");
    sf::String str = sf::String("Score : " + std::to_string(gs.getScore()));
    sf::Text text =sf::Text(str, _textFont, 45);
    text.setFillColor(sf::Color::Cyan);
    _CurrentScore = text;
    // _assets.clear();
    setGameTextures();
    // setGameSprites(gs);
    this->initGameArray(gs);
}

void arcade::SFML::setGameTextures()
{
    sf::Texture wallTexture = sf::Texture();
    wallTexture.loadFromFile("./assets/SFML/mur.png");
    sf::Texture appleTexture = sf::Texture();
    appleTexture.loadFromFile("./assets/SFML/apple.png");
    sf::Texture tailTexture = sf::Texture();
    tailTexture.loadFromFile("./assets/SFML/tail.png");
    sf::Texture headTexture = sf::Texture();
    headTexture.loadFromFile("./assets/SFML/head.png");
    sf::Texture spaceTexture = sf::Texture();
    spaceTexture.loadFromFile("./assets/SFML/transparent.png");
    sf::Texture bananaTexture = sf::Texture();
    bananaTexture.loadFromFile("./assets/SFML/banana.png");
    _textures.insert({"wall", wallTexture});
    _textures.insert({"apple", appleTexture});
    _textures.insert({"tail", tailTexture});
    _textures.insert({"head", headTexture});
    _textures.insert({"space", spaceTexture});
    _textures.insert({"banana", bananaTexture});
}

void arcade::SFML::initGameArray(GameState &gs)
{
    float h = 32, w = 32;
    sf::RectangleShape tmp;
    float x = sf::VideoMode::getDesktopMode().width / 2 - (gs.getGameArray().size() / 2 * 32);
    float y = sf::VideoMode::getDesktopMode().height  / 2 - (gs.getGameArray()[0].size() / 2 * 32);
    for (size_t i = 0; i < gs.getGameArray().size(); i ++) {
        for (size_t j = 0; j < gs.getGameArray()[i].size(); j ++) {
            tmp = sf::RectangleShape();
            tmp.setPosition({x + h * j, y + i * w});
            tmp.setSize({w, h});
            // tmp.setOutlineColor(sf::Color::Red);
            // tmp.setOutlineThickness(4);
            _gameArray.push_back(tmp);
            // std::cout << "\t" << j << std::endl;
        }
        // std::cout << i << std::endl;
    }
}

void arcade::SFML::displayGameArray()
{
    for (size_t i = 0; i < _gameArray.size(); i ++) {
        _window.draw(_gameArray[i]);
        // std::cout << i << std::endl;
    }
}

void arcade::SFML::updateGameArray(GameState &gs)
{
    size_t k = 0;
    sf::Texture tmp;
    sf::String str = sf::String("Score :" + std::to_string(gs.getScore()));
    _CurrentScore.setString(str);
    for (size_t i = 0; i < gs.getGameArray().size(); i ++) {
        for (size_t j = 0; j < gs.getGameArray().size(); j ++) {
            switch (gs.getGameArray()[i][j]) {
                case WALL:
                    _gameArray[k].setTexture(&_textures["wall"]);
                    // this->_gameArray[k].setFillColor(sf::Color::Magenta);
                    break;
                case INVISIBLE:
                case EMPTY:
                    _gameArray[k].setTexture(&_textures["space"]);
                    // this->_gameArray[k].setFillColor(sf::Color::Black);
                    break;
                case HEAD:
                    _gameArray[k].setTexture(&_textures["head"]);
                    // this->_gameArray[k].setFillColor(sf::Color::Cyan);
                    break;
                case TAIL:
                    _gameArray[k].setTexture(&_textures["tail"]);
                    // this->_gameArray[k].setFillColor(sf::Color::Blue);
                    break;
                case APPLE:
                    _gameArray[k].setTexture(&_textures["apple"]);
                    // this->_gameArray[k].setFillColor(sf::Color::Red);
                    break;
                case BANANA:
                    _gameArray[k].setTexture(&_textures["banana"]);
                default:
                    break;
            }
            k ++;
        }
    }
}

void arcade::SFML::displayGame(arcade::GameState &gs)
{
    _window.clear();
    GameEvents(gs);
    updateGameArray(gs);
    displayGameArray();
    _window.draw(_CurrentScore);
    _window.display();
}
