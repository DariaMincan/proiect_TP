#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include "game.h"

#define HIGHSCORE_FILE "highscore.txt"

void run_game() {
    clear();    
    refresh();
    WINDOW *game_win;
    int game_height = 20; 
    int game_width = 60;
    int start_y = (LINES - game_height) / 2; 
    int start_x = (COLS - game_width) / 2;   
    int score=0;
    int highscore=load_highscore();

    game_win = newwin(game_height, game_width, start_y, start_x);
    box(game_win, 0, 0);
    keypad(game_win, TRUE); 
    wrefresh(game_win);

    
    int board[4][4] = {0};
    init_board(board); 

    while (1) {
        wclear(game_win);
        box(game_win, 0, 0);
        print_board(game_win, board); 
        mvwprintw(game_win, game_height - 19, 2, "Scor: %d", score);
        mvwprintw(game_win, game_height - 2, 2, "Record: %d", highscore);
        wrefresh(game_win);

        int ch = wgetch(game_win);
        bool moved = false;
        switch (ch) {
            case KEY_UP:
                moved = move_up(board,&score);
                break;
            case KEY_DOWN:
                moved = move_down(board,&score);
                break;
            case KEY_LEFT:
                moved = move_left(board,&score);
                break;
            case KEY_RIGHT:
                moved = move_right(board,&score);
                break;
            case 27:
                delwin(game_win);
                return;
        }


        if (moved) {
            add_new_tile(board);
        }


        if (check_game_over(board)) {

            clear();    
            refresh();
            mvwprintw(game_win, game_height / 2, game_width / 2 - 4, "Game Over!");
            mvwprintw(game_win, game_height / 2 + 1, game_width / 2 - 15, "Apasati orice tasta pentru a iesi.");
            wrefresh(game_win);
            wrefresh(game_win);
            wgetch(game_win); 
            
            if (score > highscore) {
                save_highscore(score);
            }

            delwin(game_win);
            return;
        }
    }
}

void init_board(int board[][4]) {
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            board[i][j] = 0;
        }
    }

    
    srand(time(NULL));

    
    for (int k = 0; k < 2; k++) {
        int row, col, value;
        do {
            row = rand() % 4;
            col = rand() % 4;
        } while (board[row][col] != 0); 

        
        if (rand() % 5 == 0) {
            value = 4;
        } else {
            value = 2;
        }
        board[row][col] = value;
    }
}

void print_board(WINDOW *win, int board[][4]) {
    int start_y = 3; 
    int start_x = 3; 

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int value = board[i][j];
            if (has_colors() && value != 0) {
                int color_pair = 0;
               
                if (value == 2) color_pair = 2;
                else if (value == 4) color_pair = 4;
                else if (value == 8) color_pair = 8;
                else if (value == 16) color_pair = 16;
                else if (value == 32) color_pair = 32;
                else if (value == 64) color_pair = 64;
                else if (value == 128) color_pair = 7; 
                else if (value == 256) color_pair = 8;
                else if (value == 512) color_pair = 9;
                else if (value == 1024) color_pair = 10;
                else if (value == 2048) color_pair = 11;

                if (color_pair > 0) {
                    wattron(win, COLOR_PAIR(color_pair));
                    mvwprintw(win, start_y + i * 3, start_x + j * 8, "%8d", value);
                    wattroff(win, COLOR_PAIR(color_pair));
                } else {
                    mvwprintw(win, start_y + i * 3, start_x + j * 8, "%8d", value);
                }
            } else {
                mvwprintw(win, start_y + i * 3, start_x + j * 8, "%8d", value);
            }
        }
    }
    wrefresh(win);
}
           
        
    

bool check_game_over(int board[][4]) {
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 0) {
                return false; 
            }
        }
    }

    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            
            if (j < 3 && board[i][j] == board[i][j + 1]) {
                return false; 
            }

            if (i < 3 && board[i][j] == board[i + 1][j]) {
                return false; 
            }
        }
    }

    
    return true;
}

void add_new_tile(int board[][4]) {

    int value = (rand() % 10 == 0) ? 4 : 2;

    int empty_cells = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 0) {
                empty_cells++;
            }
        }
    }

    if (empty_cells > 0) {
        int random_index = rand() % empty_cells;
        int count = 0;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (board[i][j] == 0) {
                    if (count == random_index) {
                        board[i][j] = value;
                        return;
                    }
                    count++;
                }
            }
        }
    }
}

bool move_left(int board[][4],int *score) {
    bool moved = false;
    for (int i = 0; i < 4; i++) {
        // Elimină spațiile goale
        int non_zero_index = 0;
        for (int j = 0; j < 4; j++) {
            if (board[i][j] != 0) {
                board[i][non_zero_index++] = board[i][j];
                if (j != non_zero_index - 1) {
                    board[i][j] = 0;
                    moved = true;
                }
            }
        }

        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 0 && board[i][j] == board[i][j + 1]) {
                board[i][j] *= 2;
                *score+=board[i][j];
                board[i][j + 1] = 0;
                moved = true;
                for (int k = j + 2; k < 4; k++) {
                    board[i][k - 1] = board[i][k];
                    if (k - 1 != k) {
                        board[i][k] = 0;
                    }
                }
            }
        }
    }
    return moved;
}

bool move_right(int board[][4],int *score) {
    bool moved = false;
    for (int i = 0; i < 4; i++) {
        int non_zero_index = 3;
        for (int j = 3; j >= 0; j--) {
            if (board[i][j] != 0) {
                board[i][non_zero_index--] = board[i][j];
                if (j != non_zero_index + 1) {
                    board[i][j] = 0;
                    moved = true;
                }
            }
        }
        for (int j = 3; j > 0; j--) {
            if (board[i][j] != 0 && board[i][j] == board[i][j - 1]) {
                board[i][j] *= 2;
                *score+=board[i][j];
                board[i][j - 1] = 0;
                moved = true;
                for (int k = j - 2; k >= 0; k--) {
                    board[i][k + 1] = board[i][k];
                    if (k + 1 != k) {
                        board[i][k] = 0;
                    }
                }
            }
        }
    }
    return moved;
}

bool move_up(int board[][4],int *score) {
    bool moved = false;
    for (int j = 0; j < 4; j++) {
        int non_zero_index = 0;
        for (int i = 0; i < 4; i++) {
            if (board[i][j] != 0) {
                board[non_zero_index++][j] = board[i][j];
                if (i != non_zero_index - 1) {
                    board[i][j] = 0;
                    moved = true;
                }
            }
        }
        for (int i = 0; i < 3; i++) {
            if (board[i][j] != 0 && board[i][j] == board[i + 1][j]) {
                board[i][j] *= 2;
                *score+=board[i][j];
                board[i + 1][j] = 0;
                moved = true;
                for (int k = i + 2; k < 4; k++) {
                    board[k - 1][j] = board[k][j];
                    if (k - 1 != k) {
                        board[k][j] = 0;
                    }
                }
            }
        }
    }
    return moved;
}

bool move_down(int board[][4],int *score) {
    bool moved = false;
    for (int j = 0; j < 4; j++) {
        int non_zero_index = 3;
        for (int i = 3; i >= 0; i--) {
            if (board[i][j] != 0) {
                board[non_zero_index--][j] = board[i][j];
                if (i != non_zero_index + 1) {
                    board[i][j] = 0;
                    moved = true;
                }
            }
        }
        for (int i = 3; i > 0; i--) {
            if (board[i][j] != 0 && board[i][j] == board[i - 1][j]) {
                board[i][j] *= 2;
                *score+=board[i][j];
                board[i - 1][j] = 0;
                moved = true;
                for (int k = i - 2; k >= 0; k--) {
                    board[k + 1][j] = board[k][j];
                    if (k + 1 != k) {
                        board[k][j] = 0;
                    }
                }
            }
        }
    }
    return moved;
}

int load_highscore() {
    FILE *f = fopen(HIGHSCORE_FILE, "r");
    int highscore = 0;
    if (f != NULL) {
        fscanf(f, "%d", &highscore);
        fclose(f);
    }
    return highscore;
}

void save_highscore(int highscore) {
    FILE *f = fopen(HIGHSCORE_FILE, "w");
    if (f != NULL) {
        fprintf(f, "%d", highscore);
        fclose(f);
    }
}