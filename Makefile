OBJS = main.cpp eventHandling.cpp levels/menu.cpp sdl.cpp utils.cpp button.cpp levels/arena.cpp

CC = g++

COMPILER_FLAGS = -w -g

LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

OBJ_NAME = starships

all: $(OBJS)
		$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)