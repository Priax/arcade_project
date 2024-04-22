/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-arcade-vincent.montero-fontaine
** File description:
** Menu
*/

#include "../SFML.hpp"

sf::String arcade::SFML::setGraphString(std::string str)
{
    if (str == "./lib/arcade_sfml.so")
        return sf::String("SFML");
    if (str == "./lib/arcade_sdl2.so")
        return sf::String("SDL");
    if (str == "./lib/arcade_ncurses.so")
        return sf::String("Ncurses");
    if (str == "arcade_ndk++.so")
        return sf::String("NDK++");
    if (str == "arcade_aalib.so")
        return sf::String("AALib");
    if (str == "arcade_libcaca.so")
        return sf::String("Lib CaCa");
    if (str == "arcade_allegro5.so")
        return sf::String("Allegro5");
    if (str == "arcade_xlib.so")
        return sf::String("XLib");
    if (str == "arcade_gtk+.so")
        return sf::String("GTK+");
    if (str == "arcade_irrlicht.so")
        return sf::String("IrrLicht");
    if (str == "arcade_opengl.so")
        return sf::String("OpenGL");
    if (str =="arcade_vulkan.so")
        return sf::String("Vulkan");
    if (str =="arcade_qt5")
        return sf::String("Qt");
    else
        return sf::String(str);
}

sf::String arcade::SFML::setGameString(std::string str)
{
    if (str == "./lib/arcade_snake.so")
        return sf::String("Snake");
    if (str == "./lib/arcade_nibbler.so")
        return sf::String("Nibbler");
    if (str == "./lib/arcade_pacman.so")
        return sf::String("Pacman");
    if (str == "arcade_qix.so")
        return sf::String("Qix");
    if (str == "arcade_centipede.so")
        return sf::String("Centipede");
    if (str == "arcade_solarfox.so")
        return sf::String("SolarFox");
    else
        return sf::String(str);
}

void arcade::SFML::setLibs(GameState &gs)
{
    for (std::size_t i = 0; i < gs.getGraphList().size(); i++) {
        sf::String str = setGraphString(gs.getGraphList()[i]);
        sf::Text toAdd = sf::Text(str, _textFont, 50);
        if (i == _libGraphIndex) {
            toAdd.setFillColor(sf::Color(75, 0, 0));
        } else {
            toAdd.setFillColor(sf::Color(0, 0, 0));
        }
        float position = 950.0-(i*70.0);
        toAdd.setPosition({50.0, position});
        _libGraph.push_back(toAdd);
    }
    for (std::size_t i = 0; i < gs.getGamesList().size(); i++) {
        sf::String str = setGameString(gs.getGamesList()[i]);
        sf::Text toAdd = sf::Text(str, _textFont, 50);
        if (i == _libGameIndex) {
            toAdd.setFillColor(sf::Color(75, 0, 0));
        } else {
            toAdd.setFillColor(sf::Color(0, 0, 0));
        }
        float position = 950.0-(i*70.0);
        toAdd.setPosition({1550.0, position});
        _libGame.push_back(toAdd);
    }
}

void arcade::SFML::setMenuTextures()
{
    sf::Texture backgroundTexture = sf::Texture();
    sf::Texture logoTexture = sf::Texture();
    backgroundTexture.loadFromFile("./assets/SFML/background");
    logoTexture.loadFromFile("./assets/SFML/logo");
    _textures.insert({"background", backgroundTexture});
    _textures.insert({"logo", logoTexture});
}

void arcade::SFML::setMenuSprites()
{
    sf::Sprite backgroundSprite = sf::Sprite();
    sf::Sprite logoSprite = sf::Sprite();
    backgroundSprite.setTexture(_textures["background"]);
    backgroundSprite.setScale({0.5,0.5});
    logoSprite.setTexture(_textures["logo"]);
    _assets.insert({"background", backgroundSprite});
    _assets.insert({"logo", logoSprite});
}

void arcade::SFML::setMenuAssets(GameState &gs)
{
    _textures.clear();
    _assets.clear();
    setFont();
    setMenuTextures();
    setMenuSprites();
    setLibs(gs);
}

void arcade::SFML::displayArcadeMenu(arcade::GameState &gs)
{
    _window.clear();
    MenuEvents(gs);
    sf::String test(gs.getUsername());
    sf::Text userName(test, _textFont);
    for (auto it = _assets.begin(); it != _assets.end(); it++) {
        _window.draw(it->second);
    }
    for (std::size_t i = 0; i < _libGraph.size(); i++) {
        _window.draw(_libGraph[i]);
    }
    for (std::size_t i = 0; i < _libGame.size(); i++) {
        _window.draw(_libGame[i]);
    }
    _window.draw(userName);
    _window.display();
}
