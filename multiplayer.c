#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <string.h>
#include "multiplayer.h" 

void run_multiplayer_game() {
    clear();
    refresh();

    int game_height = 18; 
    int game_width = 38;  
    int spacing = 2;
    int start_y = (LINES - game_height) / 2;
    int start_x1 = (COLS - (2 * game_width + spacing)) / 2; 
    int start_x2 = start_x1 + game_width +spacing; 

    WINDOW *win1, *win2;
    PlayerState player1, player2;


    win1 = newwin(game_height, game_width, start_y, start_x1);
    box(win1, 0, 0);
    keypad(win1, TRUE);
    wrefresh(win1);

    win2 = newwin(game_height, game_width, start_y, start_x2);
    box(win2, 0, 0);
    keypad(win2, TRUE);
    wrefresh(win2);

 
    init_board(player1.board);
    player1.score = 0;
    init_board(player2.board);
    player2.score = 0;

    while (1) {
        
        wclear(win1);
        box(win1, 0, 0);
        print_board(win1, player1.board);
        mvwprintw(win1, game_height - 2, 2, "Jucator 1: %d", player1.score);
        wrefresh(win1);

        wclear(win2);
        box(win2, 0, 0);
        print_board(win2, player2.board);
        mvwprintw(win2, game_height - 2, 2, "Jucator 2: %d", player2.score);
        wrefresh(win2);

        int ch = getch(); 

        bool moved1 = false;
        bool moved2 = false;

        switch (ch) {
            case 'w':
            case 'W':
                moved1 = move_up(player1.board, &player1.score);
                break;
            case 's':
            case 'S':
                moved1 = move_down(player1.board, &player1.score);
                break;
            case 'a':
            case 'A':
                moved1 = move_left(player1.board, &player1.score);
                break;
            case 'd':
            case 'D':
                moved1 = move_right(player1.board, &player1.score);
                break;


            case KEY_UP:
                moved2 = move_up(player2.board, &player2.score);
                break;
            case KEY_DOWN:
                moved2 = move_down(player2.board, &player2.score);
                break;
            case KEY_LEFT:
                moved2 = move_left(player2.board, &player2.score);
                break;
            case KEY_RIGHT:
                moved2 = move_right(player2.board, &player2.score);
                break;
            case 27: 
                delwin(win1);
                delwin(win2);
                return;
        }

        if (moved1) {
            add_new_tile(player1.board);
        }
        if (moved2) {
            add_new_tile(player2.board);
        }

        if (check_game_over(player1.board) && check_game_over(player2.board) && player1.score==player2.score) {
            clear();
            mvprintw(LINES / 2, COLS / 2 - 10, "Amandoi jucatorii au pierdut!");
            mvprintw(LINES / 2 + 1, COLS / 2 - 15, "Apasati orice tasta pentru a iesi.");
            refresh();
            getch();
            break;
        } else if (check_game_over(player1.board) && check_game_over(player2.board) && player1.score<=player2.score) {
            clear();
            mvprintw(LINES / 2, COLS / 2 - 10, "Jucatorul 1 a pierdut!");
            mvprintw(LINES / 2 + 1, COLS / 2 - 15, "Apasati orice tasta pentru a iesi.");
            refresh();
            getch();
            break;
        } else if (check_game_over(player1.board) && check_game_over(player2.board) && player1.score>=player2.score) {
            clear();
            mvprintw(LINES / 2, COLS / 2 - 10, "Jucatorul 2 a pierdut!");
            mvprintw(LINES / 2 + 1, COLS / 2 - 15, "Apasati orice tasta pentru a iesi.");
            refresh();
            getch();
            break;
        }
    }

    delwin(win1);
    delwin(win2);
}