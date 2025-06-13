#ifndef __menu__
#define __menu__
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <ncurses.h>
#include <time.h>
#include "game.h"
#include "multiplayer.h"




void init_ncurses();
void close_ncurses();
void run_main_menu();
WINDOW* menu_setup(int , int , int *, int *);
void print_menu(WINDOW *, int , const char **, int);
int navigate_menu(WINDOW *, int *, const char **, int);
void start_game();
void game_mode();
void show_instructions();
void exit_game();
void run_game_mode_menu();

#endif