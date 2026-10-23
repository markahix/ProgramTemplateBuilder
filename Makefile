CC=g++

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
INS_DIR := /usr/local/bin

EXE := $(BIN_DIR)/programtemplatemaker
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

CPPFLAGS := -Iinclude -MMD -MP
CFLAGS   := -Wall
LDFLAGS  := -Llib -static
LDLIBS   := -lm -lstdc++fs

.PHONY: all clean install

all: $(EXE)

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CC) -std=c++17 $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

install: $(EXE)
	ln -sf $(abspath $(EXE)) $(INS_DIR)/programtemplatemaker

-include $(OBJ:.o=.d)
