/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-arcade-vincent.montero-fontaine
** File description:
** GameOver
*/

#include "../SFML.hpp"
void arcade::SFML::setGameOverMenuAssets()
{
    _textures.clear();
    _assets.clear();
    setGameOverMenuTextures();
    setGameOverMenuSprites();
}

void arcade::SFML::setGameOverMenuSprites()
{
    sf::Sprite backgroundSprite = sf::Sprite();
    backgroundSprite.setTexture(_textures["background"]);
    _assets.insert({"background", backgroundSprite});
}

void arcade::SFML::setGameOverMenuTextures()
{
    sf::Texture backgroundTexture = sf::Texture();
    backgroundTexture.loadFromFile("./assets/SFML/GameOver.png");
    _textures.insert({"background", backgroundTexture});
}

void arcade::SFML::displayGameOverMenu(arcade::GameState &gs)
{
    _window.clear();
    GameOverEvents(gs);
    for (auto it = _assets.begin(); it != _assets.end(); it++) {
        _window.draw(it->second);
    }
    _window.display();
}
