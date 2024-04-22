/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-arcade-vincent.montero-fontaine
** File description:
** Parsing
*/

#include "Parsing.hpp"
#include <regex>

std::string  arcade::Parsing::getUsername(std::string &line)
{
    std::string username = "";
    size_t i = 0;

    while (line[i] != ':' && line[i] != '\0') {
        username += line[i];
        i ++;
    }
    return username;
}

int arcade::Parsing::getScore(std::string &line)
{
    std::string score_str = "";
    size_t i = 0;

    while (line[i] != ':' && line[i] != '\0') {
        i ++;
    }
    if (line[i] == '\0')
        return 0;
    i ++;
    while (line[i] != '\0') {
        score_str += line[i];
        i ++;
    }
    return atoi(score_str.c_str());
}

/*std::map<std::string, int> arcade::Parsing::parseScoresFromFile(std::string filepath)
{
    std::ifstream file(filepath);
    std::string line;
    std::string username;
    size_t score;
    std::map<std::string, int> scores;

    while (std::getline(file, line)) {
        username = arcade::Parsing::getUsername(line);
        score = arcade::Parsing::getScore(line);
        scores[username] = score;
    }
    return scores;
}*/
std::map<std::string, int> arcade::Parsing::parseOneScoreFile(std::string scoreFilePath)
{
    std::ifstream file(scoreFilePath);
    std::string line;
    std::map<std::string, int> scores;
    if (file.is_open()) {
        while (std::getline(file, line)) {
            std::smatch matches;
            std::regex_search(line, matches, std::regex("(\\w+):([0-9]+)"));
            if (matches.size() == 3)
                scores.insert({matches[1], stoi(matches[2])});
        }
    }
    return scores;
}

std::map<std::string, std::map<std::string, int>> arcade::Parsing::parseScoresFromFile(std::string scoresPath)
{
    std::map<std::string, std::map<std::string, int>> scores;
    for (const auto &entry : std::filesystem::directory_iterator(scoresPath)) {
        std::string temp = entry.path();
        std::smatch matches;
        std::regex_search(temp, matches, std::regex(".*/(\\w+).scores"));
        if (matches.size() == 2)
            scores.insert({matches[1], parseOneScoreFile(matches[0])});
    }
    return scores;
}

std::vector<std::string> arcade::Parsing::getLibsFromPath(std::string path)
{
    std::vector<std::string> libs;

    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        libs.push_back(entry.path());
    }
    return libs;
}

//? 0 = unknown
//? 1 = graphical
//? 2 = game
int arcade::Parsing::getLibType(std::string lib)
{
    for (const auto &elem : GRAPH_LIB_LIST) {
        if (lib.find(elem.second) != std::string::npos) {
            return 1;
        }
    }
    for (const auto &elem : GAME_LIB_LIST) {
        if (lib.find(elem.second) != std::string::npos) {
            return 2;
        }
    }
    return 0;
}

std::vector<std::string> arcade::Parsing::getGraphFromLibs(std::vector<std::string> libs)
{
    std::vector<std::string> graph;
    size_t i = 0, size = libs.size();

    while (i < size) {
        switch (arcade::Parsing::getLibType(libs[i])) {
            case 1: //?Graph
                graph.push_back(libs[i]);
                break;
            case 2: //?Game
            case 0: //?Ukwn
            default:
                break;
        }
        i ++;
    }
    return graph;
}

std::vector<std::string> arcade::Parsing::getGamesFromLibs(std::vector<std::string> libs)
{
    std::vector<std::string> games;
    size_t i = 0, size = libs.size();

    while (i < size) {
        switch (arcade::Parsing::getLibType(libs[i])) {
            case 2: //?Game
                games.push_back(libs[i]);
            case 1: //?Graph
            case 0: //?Ukwn
            default:
                break;
        }
        i ++;
    }
    return games;
}

void arcade::Parsing::writeScores(std::string filepath, std::map<std::string, int> scores)
{
    std::ofstream file(filepath);

    for (const auto &elem : scores) {
        file << elem.first << ":" << elem.second << std::endl;
    }
}
