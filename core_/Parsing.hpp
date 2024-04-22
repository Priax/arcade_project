/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-arcade-vincent.montero-fontaine
** File description:
** Parsing
*/

#ifndef PARSING_HPP_
#define PARSING_HPP_

#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <filesystem>

namespace arcade {
    class Parsing;
}

class arcade::Parsing {
    public:
        static std::map<std::string, int> parseOneScoreFile(std::string scoreFilePath);
        static std::map<std::string, std::map<std::string, int>> parseScoresFromFile(std::string filepath);
        static std::string getUsername(std::string &line);
        static int getScore(std::string &line);
        static std::vector<std::string> getLibsFromPath(std::string path);
        static std::vector<std::string> getGraphFromLibs(std::vector<std::string> libs);
        static std::vector<std::string> getGamesFromLibs(std::vector<std::string> libs);
        static int getLibType(std::string lib);
        static void writeScores(std::string filepath, std::map<std::string, int> scores);

    protected:
    private:
};

//* GLOBALS
const std::map<std::string, std::string> GRAPH_LIB_LIST = {
    {"SDL2", "arcade_sdl2.so"},
    {"nCurses", "arcade_ncurses.so"},
    {"NDK++", "arcade_ndk++.so"},
    {"aa-lib", "arcade_aalib.so"},
    {"libcaca", "arcade_libcaca.so"},
    {"Allegro5", "arcade_allegro5.so"},
    {"Xlib", "arcade_xlib.so"},
    {"GTK+", "arcade_gtk+.so"},
    {"SFML", "arcade_sfml.so"},
    {"Irrlicht", "arcade_irrlicht.so"},
    {"OpenGL", "arcade_opengl.so"},
    {"Vulkan", "arcade_vulkan.so"},
    {"Qt5", "arcade_qt5"}};

const std::map<std::string, std::string> GAME_LIB_LIST = {
    {"Snake", "arcade_snake.so"},
    {"Nibbler", "arcade_nibbler.so"},
    {"Pacman", "arcade_pacman.so"},
    {"Qix", "arcade_qix.so"},
    {"Centipede", "arcade_centipede.so"},
    {"Solarfox", "arcade_solarfox.so"}};

#endif /* !PARSING_HPP_ */
