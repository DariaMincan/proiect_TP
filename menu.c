#include <ncurses.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <stdio.h>
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


void print_menu(WINDOW *menu_win, int highlight, const char *choices[], int n_choices) {
    int x = 2, y = 2;
    for (int i = 0; i < n_choices; i++) {
        if (i == highlight) {
            wattron(menu_win, A_REVERSE);
        }
        mvwprintw(menu_win, y, x, "%s", choices[i]);
        wattroff(menu_win, A_REVERSE);
        y++;
    }
    wrefresh(menu_win);
}


int navigate_menu(WINDOW *menu_win, int *highlight, const char *choices[], int n_choices) { 
 
    
    int ch = wgetch(menu_win);
    
    wrefresh(menu_win);

    if (ch == 'w' || ch == 'W' || ch == KEY_UP) {
        if (*highlight > 0) {
            (*highlight)--; 
        }
    }
    else if (ch == 's' || ch == 'S' || ch == KEY_DOWN) {
        if (*highlight < n_choices - 1) {
            (*highlight)++; 
        }
    }
    else if (ch == 10) {
        return *highlight; 
    }
    else if (ch == 27) {
        return 3;
    }

    return -1;
}


void start_game() {
    run_game(); 
    clear();    
    refresh();
}

void game_mode() {
    clear();
    mvprintw(0, 0, "Ai ales Mod joc! Apasa orice tasta pentru a continua."); 
    refresh();
    int ch;
    while ((ch = getch()) != KEY_LEFT) {
    }
}

void show_instructions() {
    clear();
    mvprintw(0, 0, "Ai ales Instructiuni! Apasa orice tasta pentru a continua.");
    mvprintw(2, 0, "1. Foloseste sagetile pentru a misca piesele.");
    mvprintw(3, 0, "2. Combina piesele de aceeasi valoare pentru a le dubla.");
    mvprintw(4, 0, "3. Castiga cand ajungi la 2048.");
    refresh();
    int ch;
    while ((ch = getch()) != KEY_LEFT) {
    }
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
        "Single Player",
        "Multiplayer",
        "Inapoi la meniul principal"
    };
    int n_mode_choices = sizeof(mode_choices) / sizeof(char*);
    int mode_highlight = 0;
    int mode_choice = -1;

    clear();    
    refresh();
    WINDOW *mode_menu_win = newwin(8, 30, 9, 25);
    keypad(mode_menu_win, TRUE);
    box(mode_menu_win, 0, 0);
    wrefresh(mode_menu_win);

    while (mode_choice == -1) {
        print_menu(mode_menu_win, mode_highlight, mode_choices, n_mode_choices);
        mode_choice = navigate_menu(mode_menu_win, &mode_highlight, mode_choices, n_mode_choices);
    }

   

    switch (mode_choice) {
        case 0: 
            run_game();
            break;
        case 1: 
            run_multiplayer_game();
            break;
        case 2: 
        print_menu(mode_menu_win, mode_highlight, mode_choices, n_mode_choices);
            break;
        case 3: 
        print_menu(mode_menu_win, mode_highlight, mode_choices, n_mode_choices);
            break;
    }
    delwin(mode_menu_win);
}


