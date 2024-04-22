##
## EPITECH PROJECT, 2024
## B-OOP-400-MAR-4-1-arcade-vincent.montero-fontaine
## File description:
## Makefile
##
SFML_SRC = ./graph/SFML/Events.cpp\
			./graph/SFML/Game.cpp\
			./graph/SFML/GameMenu.cpp\
			./graph/SFML/GameOver.cpp\
			./graph/SFML/Menu.cpp\
			./graph/SFML/SFML.cpp\
#* RULES
all : core games graphicals

re : fclean all

clean :
	@rm -f $(BIN_NAME)

fclean : clean
	@rm -f *.so
	@rm -f ./lib/*.so

core :
	g++ $(FLAGS) $(CORE_SRC) -o $(BIN_NAME)

graphicals : compile_ncurses compile_sfml compile_sdl2

games : compile_snake compile_nibbler

#* CORE
BIN_NAME = arcade

GS_SRC = 	./core_/GameState.cpp		\

CORE_SRC =	./core_/arcade.cpp			\
			./core_/Core.cpp			\
			./core_/ErrorHandling.cpp	\
			./core_/Parsing.cpp			\
			$(GS_SRC)					\

FLAGS = -Wall -Wextra -std=c++20 -g3 -g -fno-gnu-unique

#* GRAPH
NCURSES_LIB_NAME = arcade_ncurses.so
SDL2_LIB_NAME = arcade_sdl2.so
SFML_LIB_NAME = arcade_sfml.so

compile_ncurses :
	g++ ./graph/Ncurses.cpp $(GS_SRC) -lncurses -fPIC -shared -o $(NCURSES_LIB_NAME)
	@mv $(NCURSES_LIB_NAME) ./lib/

compile_sdl2 :
	g++ -W -Wall -Wextra ./graph/SDL.cpp $(GS_SRC) -lSDL2 -lSDL2_ttf -lSDL2_image -fPIC -shared -o $(SDL2_LIB_NAME)
	@mv $(SDL2_LIB_NAME) ./lib/

compile_sfml :
	g++ $(SFML_SRC) $(GS_SRC) -lsfml-graphics -lsfml-window -lsfml-system -fPIC -shared -o $(SFML_LIB_NAME)
	@mv $(SFML_LIB_NAME) ./lib/

#* GAMES
SNAKE_GAME_NAME = arcade_snake.so
NIBBLER_GAME_NAME = arcade_nibbler.so

compile_snake :
	g++ ./game/Snake.cpp $(GS_SRC) -fPIC -shared -o $(SNAKE_GAME_NAME)
	@mv $(SNAKE_GAME_NAME) ./lib/

compile_nibbler :
	g++ ./game/Nibbler.cpp $(GS_SRC) -fPIC -shared -o $(NIBBLER_GAME_NAME)
	@mv $(NIBBLER_GAME_NAME) ./lib/
