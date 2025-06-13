#ifndef __game__
#define __game__
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include <stdbool.h>



extern int current_grid_size;
extern bool has_won_2048;






void run_game();
void init_board(int [][current_grid_size]);
void print_board(WINDOW *, int [][current_grid_size]);
bool check_game_over(int [][current_grid_size]);
bool move_left(int [][current_grid_size],int*);
bool move_right(int [][current_grid_size],int*);
bool move_up(int [][current_grid_size],int*);
bool move_down(int [][current_grid_size],int*);
void add_new_tile(int [][current_grid_size]);
int load_highscore();
void save_highscore();
void setup_ncurses_colors();
int count_digits(int );
#endif
