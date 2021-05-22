CC		= g++
CFLAGS	= -Wall -O2 -g
LDFLAGS	= -lSDL2 -lGLU -lGL -lm -lglut -lstdc++

BIN_DIR	= bin
INC_DIR = -I include
SRC_DIR	= src
OBJ_DIR	= obj

SRC_FILES 	= $(shell find $(SRC_DIR)/ -type f -name '*.cpp')
OBJ_FILES 	= $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o, $(SRC_FILES))
# Nom de l'exécutable 
EXEC_BIN	= main.out 

all : $(OBJ_FILES)

# Nom de l'exécutable 
main : $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)/
	$(CC) -o $(BIN_DIR)/$(EXEC_BIN) $(OBJ_FILES) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p "$(@D)"
	$(CC) -c $< -o $@ $(CFLAGS) $(INC_DIR)

clean :
	rm -rf *~
	rm -rf $(SRC_DIR)/*/*~
	rm -rf $(OBJ_DIR)/
	rm -rf $(BIN_DIR)/*
