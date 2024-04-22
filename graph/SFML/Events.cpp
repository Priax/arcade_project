/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-arcade-vincent.montero-fontaine
** File description:
** events
*/

#include "../SFML.hpp"

void arcade::SFML::enterUsername(GameState &gs)
{
    if (_event.key.code == sf::Keyboard::A && _event.type == sf::Event::KeyPressed) gs.setUsername(gs.getUsername()+"a");
    if (_event.key.code == sf::Keyboard::B && _event.type == sf::Event::KeyPressed) gs.setUsername(gs.getUsername()+"b");
    if (_event.key.code == sf::Keyboard::C && _event.type == sf::Event::KeyPressed) gs.setUsername(gs.getUsername()+"c");
    if (_event.key.code == sf::Keyboard::D && _event.type == sf::Event::KeyPressed) gs.setUsername(gs.getUsername()+"d");
    if (_event.key.code == sf::Keyboard::E && _event.type == sf::Event::KeyPressed) gs.setUsername(gs.getUsername()+"e");
    if (_event.key.code == sf::Keyboard::F && _event.type == sf::Event::KeyPressed) gs.setUsername(gs.getUsername()+"f");
    if (_event.key.code == sf::Keyboard::G && _event.type == sf::Event::KeyPressed) gs.setUsername(gs.getUsername()+"g");
    if (_event.key.code == sf::Keyboard::H && _event.type == sf::Event::KeyPressed) gs.setUsername(gs.getUsername()+"h");
    if (_event.key.code == sf::Keyboard::I && _event.type == sf::Event::KeyPressed) gs.setUsername(gs.getUsername()+"i");
    if (_event.key.code == sf::Keyboard::J && _event.type == sf::Event::KeyPressed) gs.setUsername(gs.getUsername()+"j");
    if (_event.key.code == sf::Keyboard::K && _event.type == sf::Event::KeyPressed) gs.setUsername(gs.getUsername()+"k");
    if (_event.key.code == sf::Keyboard::L && _event.type == sf::Event::KeyPressed) gs.setUsername(gs.getUsername()+"l");
    if (_event.key.code == sf::Keyboard::M && _event.type == sf::Event::KeyPressed) gs.setUsername(gs.getUsername()+"m");
    if (_event.key.code == sf::Keyboard::N && _event.type == sf::Event::KeyPressed) gs.setUsername(gs.getUsername()+"n");
    if (_event.key.code == sf::Keyboard::O && _event.type == sf::Event::KeyPressed) gs.setUsername(gs.getUsername()+"o");
    if (_event.key.code == sf::Keyboard::P && _event.type == sf::Event::KeyPressed) gs.setUsername(gs.getUsername()+"p");
    if (_event.key.code == sf::Keyboard::Q && _event.type == sf::Event::KeyPressed) gs.setUsername(gs.getUsername()+"q");
    if (_event.key.code == sf::Keyboard::R && _event.type == sf::Event::KeyPressed) gs.setUsername(gs.getUsername()+"r");
    if (_event.key.code == sf::Keyboard::S && _event.type == sf::Event::KeyPressed) gs.setUsername(gs.getUsername()+"s");
    if (_event.key.code == sf::Keyboard::T && _event.type == sf::Event::KeyPressed) gs.setUsername(gs.getUsername()+"t");
    if (_event.key.code == sf::Keyboard::U && _event.type == sf::Event::KeyPressed) gs.setUsername(gs.getUsername()+"u");
    if (_event.key.code == sf::Keyboard::V && _event.type == sf::Event::KeyPressed) gs.setUsername(gs.getUsername()+"v");
    if (_event.key.code == sf::Keyboard::W && _event.type == sf::Event::KeyPressed) gs.setUsername(gs.getUsername()+"w");
    if (_event.key.code == sf::Keyboard::X && _event.type == sf::Event::KeyPressed) gs.setUsername(gs.getUsername()+"x");
    if (_event.key.code == sf::Keyboard::Y && _event.type == sf::Event::KeyPressed) gs.setUsername(gs.getUsername()+"y");
    if (_event.key.code == sf::Keyboard::Z && _event.type == sf::Event::KeyPressed) gs.setUsername(gs.getUsername()+"z");
    if (_event.key.code == sf::Keyboard::BackSpace && _event.type == sf::Event::KeyPressed && !gs.getUsername().empty()) {
        std::string buf = gs.getUsername();
        buf.pop_back();
        gs.setUsername(buf);
    }
    if (_event.key.code == sf::Keyboard::Enter && _event.type == sf::Event::KeyPressed && !gs.getUsername().empty()){
        gs.setGameLib(gs.getGamesList()[_libGameIndex]);
        gs.setGraphLib(gs.getGraphList()[_libGraphIndex]);
        gs.setState(GAME_START);
        _isCreated = false;
    }
}

void arcade::SFML::MenuEvents(GameState &gs)
{
    while (_window.pollEvent(_event)) {
        if (_event.type == sf::Event::Closed){
            _window.close();
            gs.setState(STOP);
        }
        if (_event.key.code == sf::Keyboard::Down && _event.type == sf::Event::KeyPressed) {
            _libGraph[_libGraphIndex].setFillColor(sf::Color(0, 0, 0));
            if (_libGraphIndex == 0)
                _libGraphIndex = _libGraph.size();
            _libGraphIndex--;
            _libGraph[_libGraphIndex].setFillColor(sf::Color(75, 0, 0));
        }
        if (_event.key.code == sf::Keyboard::Up && _event.type == sf::Event::KeyPressed) {
            _libGraph[_libGraphIndex].setFillColor(sf::Color(0, 0, 0));
            _libGraphIndex++;
            if (_libGraphIndex == _libGraph.size())
                _libGraphIndex = 0;
            _libGraph[_libGraphIndex].setFillColor(sf::Color(75, 0, 0));
        }
        if (_event.key.code == sf::Keyboard::Right && _event.type == sf::Event::KeyPressed) {
            _libGame[_libGameIndex].setFillColor(sf::Color(0, 0, 0));
            if (_libGameIndex == 0)
                _libGameIndex = _libGame.size();
            _libGameIndex--;
            _libGame[_libGameIndex].setFillColor(sf::Color(75, 0, 0));
        }
        if (_event.key.code == sf::Keyboard::Left && _event.type == sf::Event::KeyPressed) {
            _libGame[_libGameIndex].setFillColor(sf::Color(0, 0, 0));
            _libGameIndex++;
            if (_libGameIndex == _libGame.size())
                _libGameIndex = 0;
            _libGame[_libGameIndex].setFillColor(sf::Color(75, 0, 0));
        }
        enterUsername(gs);
    }
}

void::arcade::SFML::GameMenuEvents(GameState &gs)
{
    while (_window.pollEvent(_event)) {
        if (_event.type == sf::Event::Closed){
            _window.close();
            gs.setState(STOP);
        }
        if (_event.key.code == sf::Keyboard::Escape && _event.type == sf::Event::KeyPressed) {
            _window.close();
            gs.setState(STOP);
        }
        if (_event.key.code == sf::Keyboard::Space && _event.type == sf::Event::KeyPressed){
            gs.setState(IN_GAME);
            _isCreated == false;
        }
        if (_event.key.code == sf::Keyboard::Tab && _event.type == sf::Event::KeyPressed){
            gs.setState(ARCADE_MENU);
            _isCreated == false;
        }
    }
}

void::arcade::SFML::GameEvents(GameState &gs)
{
    while (_window.pollEvent(_event)) {
        if (_event.type == sf::Event::Closed){
            _window.close();
            gs.setState(STOP);
        }
        if (_event.key.code == sf::Keyboard::Escape && _event.type == sf::Event::KeyPressed) {
            _window.close();
            gs.setState(STOP);
        }
        if (_event.key.code == sf::Keyboard::Down && _event.type == sf::Event::KeyPressed) {
            gs.setKey(keyPressed::DOWN_KEY);
        }
        if (_event.key.code == sf::Keyboard::Up && _event.type == sf::Event::KeyPressed) {
            gs.setKey(keyPressed::UP_KEY);
        }
        if (_event.key.code == sf::Keyboard::Right && _event.type == sf::Event::KeyPressed) {
            gs.setKey(keyPressed::RIGHT_KEY);
        }
        if (_event.key.code == sf::Keyboard::Left && _event.type == sf::Event::KeyPressed) {
            gs.setKey(keyPressed::LEFT_KEY);
        }
        
    }
}

void::arcade::SFML::GameOverEvents(GameState &gs)
{
    while (_window.pollEvent(_event)) {
        if (_event.type == sf::Event::Closed){
            _window.close();
            gs.setState(STOP);
        }
        if (_event.key.code == sf::Keyboard::Escape && _event.type == sf::Event::KeyPressed) {
            _window.close();
            gs.setState(STOP);
        }
        if (_event.key.code == sf::Keyboard::Enter && _event.type == sf::Event::KeyPressed)
            gs.setState(GAME_START);
        
        if (_event.key.code == sf::Keyboard::Tab && _event.type == sf::Event::KeyPressed){
            gs.setState(ARCADE_MENU);
            _isCreated == false;
        }
    }
}