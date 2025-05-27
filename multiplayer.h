#ifndef __multiplayer__
#define __multiplayer__
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <ncurses.h>
#include <time.h>
#include "game.h"
#include "menu.h"

typedef struct {
    int board[4][4];
    int score;
} PlayerState;

void run_multiplayer_game(); 

#endif