#ifndef __game__
#define __game__
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <time.h>

void run_game();
void init_board(int (*)[4]);
void print_board(WINDOW *, int (*)[4]);
bool check_game_over(int (*)[4]);
bool move_left(int [][4],int*);
bool move_right(int [][4],int*);
bool move_up(int [][4],int*);
bool move_down(int [][4],int*);
void add_new_tile(int [][4]);
int load_highscore();
void save_highscore();

#endif
