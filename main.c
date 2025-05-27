#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ncurses.h>
#include <time.h>
#include "menu.h"
#include "game.h"
#include "multiplayer.h"

int main() {
 

    init_ncurses();

    const char *choices[] = {
        "Start joc",
        "Mod joc",
        "Instructiuni",
        "Iesire"
    }; 
    
    int n_choices = sizeof(choices) / sizeof(char*);
    int highlight = 0;

    WINDOW *menu_win = newwin(10, 40, 7, 20);
    keypad(menu_win, TRUE);
    box(menu_win, 0, 0);

    while(1) {
        wclear(stdscr); 
        refresh();      
        print_menu(menu_win, highlight, choices, n_choices);

        int option = navigate_menu(menu_win, &highlight, choices, n_choices); 
        if (option != -1) {
            if (option == 0) {
                if (has_colors()) {
                    start_color();

                    init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
                    init_pair(4, COLOR_GREEN, COLOR_BLACK);
                    init_pair(8, COLOR_YELLOW, COLOR_BLACK);
                    init_pair(16, COLOR_CYAN, COLOR_BLACK);
                    init_pair(32, COLOR_RED, COLOR_BLACK);
                    init_pair(64, COLOR_BLUE, COLOR_BLACK);
                    init_pair(128, COLOR_RED, COLOR_BLACK);
                    init_pair(256, COLOR_MAGENTA, COLOR_BLACK);
                    init_pair(512, COLOR_GREEN, COLOR_BLACK);
                    init_pair(1024, COLOR_YELLOW, COLOR_BLACK);
                    init_pair(2048, COLOR_CYAN, COLOR_BLACK);

                }
                start_game();
            } else if (option == 1) {
                run_game_mode_menu();
            } else if (option == 2) {
                show_instructions();
            } else if (option == 3) {
                exit_game();
                break;
            }
        }
    }

    close_ncurses();
    return 0;
}


