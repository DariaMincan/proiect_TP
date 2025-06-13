#include <ncurses.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "game.h"         
#include "multiplayer.h"

void init_ncurses() {
    initscr();
    cbreak();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
}


void close_ncurses() {
    endwin();
}


void run_main_menu() {
    const char *choices[] = {
        "Mod joc",
        "Instructiuni",
        "Iesire"
    };
    int n_choices = sizeof(choices) / sizeof(char*);
    int highlight = 0;

    int menu_height = 10;
    int menu_width = 40;
    int start_y, start_x;

    WINDOW *menu_win = menu_setup(menu_height, menu_width, &start_y, &start_x);

    int option;
    while(1) {
        clear();
        refresh(); 

        box(menu_win, 0, 0);
        print_menu(menu_win, highlight, choices, n_choices);

        option = navigate_menu(menu_win, &highlight, choices, n_choices);

        if (option != -1) { 
            if (option == 0) { 
                run_game_mode_menu();
            } else if (option == 1) { 
                show_instructions();
            } else if (option == 2) {
                exit_game(); 
                break; 
            }
       
            clear();
            refresh();
           
            box(menu_win, 0, 0);
            wrefresh(menu_win);
        }
    }
    delwin(menu_win);
}


WINDOW* menu_setup(int menu_height, int menu_width, int *start_y, int *start_x) {
    *start_y = (LINES - menu_height) / 2;
    *start_x = (COLS - menu_width) / 2;

    WINDOW *menu_win = newwin(menu_height, menu_width, *start_y, *start_x);
    keypad(menu_win, TRUE);
    box(menu_win, 0, 0);
    wrefresh(menu_win); 

    return menu_win;
}

void print_menu(WINDOW *menu_win, int highlight, const char *choices[], int n_choices) {
    int max_y, max_x;
    getmaxyx(menu_win, max_y, max_x); 

    int y_start_pos = (max_y - n_choices) / 2;
    if (y_start_pos < 1) y_start_pos = 1; 

    for (int i = 0; i < n_choices; i++) {
 
        int choice_len = strlen(choices[i]);
        int x_pos = (max_x - choice_len) / 2;
        if (x_pos < 1) x_pos = 1;

        if (i == highlight) {
            wattron(menu_win, A_REVERSE);
        }
        mvwprintw(menu_win, y_start_pos + i, x_pos, "%s", choices[i]);
        wattroff(menu_win, A_REVERSE);
    }
    wrefresh(menu_win);
}




int navigate_menu(WINDOW *menu_win, int *highlight_ptr, const char *choices[], int n_choices) {
    int ch; 

   
    while (1) {

        print_menu(menu_win, *highlight_ptr, choices, n_choices);
        wrefresh(menu_win); 

        ch = wgetch(menu_win); 

        switch (ch) {
            case 'w':
            case 'W':
            case KEY_UP:
                (*highlight_ptr)--; 
                if (*highlight_ptr < 0) {
                    *highlight_ptr = n_choices - 1; 
                }
                break;
            case 's':
            case 'S':
            case KEY_DOWN:
                (*highlight_ptr)++; 
                if (*highlight_ptr >= n_choices) {
                    *highlight_ptr = 0;
                }
                break;
            case 10: 
                return *highlight_ptr; 
            case 'q':
            case 'Q':
                return -1; 
            default:
                break;
        }
    }
}


void start_game() {
    run_game(); 
    clear();    
    refresh();
}



void show_instructions() {
    clear();
    mvprintw(0, 0, "Ai ales Instructiuni!");
    mvprintw(2, 0, "1. Foloseste sagetile pentru a misca piesele.");
    mvprintw(3, 0, "2. Combina piesele de aceeasi valoare pentru a le dubla.");
    mvprintw(4, 0, "3. SCopul jocului e sa aduni cat mai multe puncte.");
    refresh();
    int ch_exit;
    do {
        ch_exit = getch(); 
    } while (ch_exit != 'q' && ch_exit != 'Q'); 

}

void exit_game() {
    clear();
    mvprintw(0, 0, "Iesire din joc...");
    refresh();
    int ch;
    while ((ch = getch()) != KEY_LEFT) {
    }
}


void run_game_mode_menu() {
    const char *mode_choices[] = {
        "Single Player (4x4)", 
        "Single Player (3x3)", 
        "Single Player (5x5)", 
        "Multiplayer",
        "Inapoi la meniul principal"
    };
    int n_mode_choices = sizeof(mode_choices) / sizeof(char*);
    int mode_highlight = 0; 

    clear();
    refresh();
    WINDOW *mode_menu_win = newwin(8, 30, 9, 25);
    keypad(mode_menu_win, TRUE);
    box(mode_menu_win, 0, 0);
    wrefresh(mode_menu_win);

    int selected_option_index; 


    selected_option_index = navigate_menu(mode_menu_win, &mode_highlight, mode_choices, n_mode_choices);

    delwin(mode_menu_win); 

    if (selected_option_index == -1) {
        return;
    }

  
    switch (selected_option_index) {
        case 0: 
            current_grid_size = 4; 
            run_game();
            break;
        case 1: 
            current_grid_size = 3;
            run_game();
            break;
        case 2: 
            current_grid_size = 5; 
            run_game();
            break;
        case 3: 
            current_grid_size = 4; 
            run_multiplayer_game();
            break;
        case 4: 
            break; 
    }
}

