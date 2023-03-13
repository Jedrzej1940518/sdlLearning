OBJS = main.cpp gameState.cpp levels/menu.cpp sdl.cpp utils.cpp button.cpp levels/arena.cpp object.cpp

CXX = ccache g++

COMPILER_FLAGS = -w -g

LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

OBJ_NAME = starships

all: $(OBJS)
		$(CXX) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)