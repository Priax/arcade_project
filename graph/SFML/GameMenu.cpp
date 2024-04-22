/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-arcade-vincent.montero-fontaine
** File description:
** GameMenu
*/

#include "../SFML.hpp"
void arcade::SFML::setGameMenuAssets(GameState &gs)
{
    _textures.clear();
    _assets.clear();
    std::string game = gs.getGameLib();
    game = game.substr(13, game.size()-13);
    game = game.substr(0, game.size()-3);
    _gameName = game;
    setGameMenuTextures();
    setGameMenuSprites();
    setGameMenuScores(gs);
}

void arcade::SFML::setGameMenuScores(GameState &gs)
{
    std::map<std::string, int> scores = gs.getScores()[_gameName];
    float y = 0;
    for (auto it = scores.begin(); it != scores.end(); it++) {
        sf::String str = sf::String(it->first + " : " + std::to_string(it->second));
        sf::Text text =sf::Text(str, _textFont, 45);
        text.setFillColor(sf::Color::Cyan);
        text.setPosition({0, y});
        _score.push_back(text);
        y += 50;
    }

}

void arcade::SFML::setGameMenuSprites()
{
    _textFont.loadFromFile("./assets/SFML/Tag.ttf");
    sf::Sprite backgroundSprite = sf::Sprite();
    backgroundSprite.setTexture(_textures["background"]);
    _assets.insert({"background", backgroundSprite});
}

void arcade::SFML::setGameMenuTextures()
{
    sf::Texture backgroundTexture = sf::Texture();
    backgroundTexture.loadFromFile("./assets/SFML/moreliaviridis.png");
    _textures.insert({"background", backgroundTexture});
}

void arcade::SFML::displayGameMenu(arcade::GameState &gs)
{
    _window.clear();
    GameMenuEvents(gs);
    for (auto it = _assets.begin(); it != _assets.end(); it++) {
        _window.draw(it->second);
    }
    for (size_t i = 0; i < _score.size(); i ++) {
        _window.draw(_score[i]);
    }
    _window.display();
}