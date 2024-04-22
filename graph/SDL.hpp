/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-arcade-vincent.montero-fontaine
** File description:
** SDL
*/

#ifndef SDL_HPP_
#define SDL_HPP_

#include "IGraph.hpp"
#include "../core_/GameState.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <unistd.h>

namespace arcade {
    class SDL;
}

class arcade::SDL : public arcade::IGraph {
    public:
        enum Menu_State {
            GAME_LIB,
            GRAPH_LIB,
            TYP_USR,
            DEFAULT,
        };
        class Error : public std::exception {
            public:
                Error(std::string msg = "", std::string where = "") : _error_msg(msg), _where(where) {};
                const char *what() const noexcept override {
                    return _error_msg.c_str();
                }
                const char *where() const noexcept {
                    return _where.c_str();
                }
            private:
                std::string _error_msg;
                std::string _where;
        };

        SDL();
        ~SDL();
        void displayWindow(GameState &gs);
        void displayArcadeMenu(GameState &gs);
        void renderUserInput(const std::string& text, const SDL_Color& color, int x, int y);
        void renderRect(SDL_Renderer *renderer, const SDL_Rect &rect, const SDL_Color &color);
        void handle_typing(SDL_Event &event, std::string &inputText, std::string &savedText);
        void move_rectangle(SDL_Event &event, SDL_Rect &myRect, int numItems);
        void render_sdl(GameState &gs, std::string &inputText, SDL_Rect myRect, SDL_Color rectColor, SDL_Color textColor, std::vector<std::string> Libs);
        void render_vector(const std::vector<std::string>& vec, const SDL_Color& textColor, int x, int y);
        //void render_text(const std::string& text, const SDL_Color& color, int x, int y, int maxWidth);
        void render_text(const std::string &text, const SDL_Color &color, int x, int y, int fontSize, int maxWidth);
        void displayGame(GameState &gs);
        void displayGameStart(GameState &gs);
        void chooseLib(GameState &gs, SDL_Event event, SDL_Rect myRect, size_t *currentListIndex, std::vector<std::vector<std::string>> allLists);
        void renderSprite(int x, int y, SDL_Texture *texture);
        void renderSprite(int x, int y, SDL_Texture *texture, SDL_Rect* srcRect);
        SDL_Texture *loadTexture(const std::string& path, SDL_Renderer* renderer);
        void gameEvents(GameState &gs, SDL_Event event);
        void gameOverMenu(GameState &gs);

    protected:
    private:
        SDL_Window *_window;
        SDL_Renderer *_renderer;
        TTF_Font *_font;
        int _spacing;
        Menu_State _state;
        int _textXOffset = 160;  // X offset for text rendering
        int _textYOffset = 110;  // Y offset for text rendering
        int _rectXOffset = 110;  // X offset for selection rectangle
        int _rectYOffset = 110;  // Y offset for selection rectangle
        SDL_Texture *_wall_texture;
        SDL_Texture *_apple_texture;
        SDL_Texture *_yellow_apple_texture;
        SDL_Texture *_snake_texture;
        SDL_Texture *_head_texture;
        Error _error;
};

#endif /* !SDL_HPP_ */
