#ifndef __save__
#define __save__
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ncurses.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include "gamestate.h"

#define SAVE_FILENAME "2048_save.bin"

bool save_game(const GameState *state, const char *filename);
bool load_game(GameState *state, const char *filename);
bool check_saved_game_exists(const char *filename);

#endif