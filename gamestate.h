#ifndef __multiplayer__
#define __multiplayer__
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ncurses.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>



#define MAX_GRID_SIZE 5 

typedef struct {
    int board[MAX_GRID_SIZE][MAX_GRID_SIZE]; 
    int score;                               
    int moves;                               
    int current_grid_size;                   
    bool game_over;                          
    bool won;                                
}GameState;


extern GameState saved_game_state;
extern bool game_saved; 


#endif