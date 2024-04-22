/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-arcade-vincent.montero-fontaine
** File description:
** SFML
*/

#ifndef SFML_HPP_
#define SFML_HPP_

#include "IGraph.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <memory>
#include "../core_/GameState.hpp"
namespace arcade {
    class SFML;
}

class arcade::SFML : public arcade::IGraph {
    public:
        SFML();
        ~SFML();
        void displayWindow(GameState &gs);

    protected:
    private:
        sf::String setGraphString(std::string str);
        sf::String setGameString(std::string str);
        void setLibs(GameState &gs);
        void displayArcadeMenu(GameState &gs);
        void displayGameMenu(GameState &gs);
        void displayGame(GameState &gs);
        void displaySnake(GameState &gs);
        void displayNibbler(GameState &gs);
        void displayGameOverMenu(GameState &gs);
        void setMenuAssets(GameState &gs);
        void setGameMenuAssets(GameState &gs);
        void setGameAssets(GameState &gs);
        void updateGameSprite(char c, sf::Sprite &sprite);
        sf::Sprite setGameSprite(char c);

        void setGameOverMenuAssets();
        void GameEvents(GameState &gs);

        void GameOverEvents(GameState &gs);
        void setFont();
        void enterUsername(GameState &gs);
        void MenuEvents(GameState &gs);
        void GameMenuEvents(GameState &gs);
        void setMenuTextures();
        void setMenuSprites();
        void setGameMenuTextures();
        void setGameMenuSprites();
        void setGameMenuScores(GameState &gs);
        void setGameOverMenuTextures();
        void setGameOverMenuSprites();
        void setGameTextures();
        void setGameSprites(GameState &gs);
        arcade::screenState _status;
        int _libGraphIndex = 0;
        int _libGameIndex = 0;
        bool _isCreated = false;
        sf::RenderWindow _window;
        sf::Event _event;
        std::string _map;
        std::string _gameName;
        sf::Text _CurrentScore;
        std::vector<sf::Text>_score = {};
        std::vector<sf::Sprite>_GameAssets = {};
        std::map<std::string, sf::Sprite> _assets;
        std::map<const std::string, sf::Texture> _textures;
        std::vector<sf::Text> _libGraph;
        std::vector<sf::Text> _libGame;
        sf::Font _textFont;


        std::vector<sf::RectangleShape> _gameArray = {};
        void initGameArray(GameState &gs);
        void displayGameArray();
        void updateGameArray(GameState &gs);
};

#endif /* !SFML_HPP_ */
