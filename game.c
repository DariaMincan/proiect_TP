#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "game.h"


#define HIGHSCORE_FILE "highscore.txt"
int current_grid_size = 4;
bool has_won_2048=false;


void run_game() {
    clear();    
    refresh();
    WINDOW *game_win;
    int moves = 0; 
    int score = 0; 
    int cell_width = 9;
    int cell_height = 4;

    int game_width = current_grid_size * cell_width + current_grid_size + 2; 
    int game_height = current_grid_size * cell_height + current_grid_size + 2; 

    if (game_width > COLS) game_width = COLS;
    if (game_height > LINES) game_height = LINES;

    int start_y = (LINES - game_height) / 2;
    int start_x = (COLS - game_width) / 2;

 
    int highscore = load_highscore();

    game_win = newwin(game_height, game_width, start_y, start_x);
    box(game_win, 0, 0);
    keypad(game_win, TRUE); 
    wrefresh(game_win);

    
    int board[current_grid_size][current_grid_size];
    init_board(board); 
    

    while (1) {
        wclear(game_win);
        box(game_win, 0, 0);
        print_board(game_win, board); 
        mvwprintw(game_win, 1, game_width - 15, "Moves: %d", moves);
        mvwprintw(game_win, 1, 2, "Score: %d", score);
        mvwprintw(game_win, game_height - 2, 2, "Record: %d", highscore);
        if(has_won_2048){
            mvprintw(1, 20, "[AI ATINS 2048!]");
        }
        wrefresh(game_win);

        int ch = wgetch(game_win); 
        bool moved = false;
        switch (ch) {
            case KEY_UP:
                moved = move_up(board, &score);
                break;
            case KEY_DOWN:
                moved = move_down(board, &score);
                break;
            case KEY_LEFT:
                moved = move_left(board, &score);
                break;
            case KEY_RIGHT:
                moved = move_right(board, &score);
                break;
            case 27: 
                delwin(game_win);
                return; 
        }


        if (moved) {
            add_new_tile(board);
            moves++;
        }


        if (check_game_over(board)) {
   
            wclear(game_win); 
            box(game_win, 0, 0); 
            
           
            mvwprintw(game_win, game_height / 2, game_width / 2 - 5, "GAME OVER!");
            wrefresh(game_win); 

        
            int ch_exit;
            do {
                ch_exit = wgetch(game_win); 
            } while (ch_exit != 'q' && ch_exit != 'Q'); 
            
 
            if (score > highscore) {
                save_highscore(score);
            }

            delwin(game_win);
            return;
        }
    }
}

void init_board(int board[][current_grid_size]) {
    
    for (int i = 0; i < current_grid_size; i++) {
        for (int j = 0; j < current_grid_size; j++) {
            board[i][j] = 0;
        }
    }

    
    srand(time(NULL));

    
    for (int k = 0; k < 2; k++) {
        int row, col, value;
        do {
            row = rand() % current_grid_size;
            col = rand() % current_grid_size;
        } while (board[row][col] != 0); 

        
        if (rand() % 10 == 0) {
            value = 4;
        } else {
            value = 2;
        }
        board[row][col] = value;
    }
}
void print_board(WINDOW *win, int board[][current_grid_size]) {

    int max_y, max_x;
    getmaxyx(win, max_y, max_x);

    int cell_height = max_y / current_grid_size;
    int cell_width = max_x / current_grid_size;

    if (cell_height < 3) {
        cell_height = 3;
    }
    if (cell_width < 8) {
        cell_width = 8;
    }

    int start_y = (max_y - (current_grid_size * cell_height)) / 2;
    int start_x = (max_x - (current_grid_size * cell_width)) / 2;

    for (int i = 0; i < current_grid_size; i++) {
        for (int j = 0; j < current_grid_size; j++) {
            int value = board[i][j];
            int y_pos = start_y + i * cell_height + cell_height / 2; 
            int x_pos = start_x + j * cell_width + cell_width / 2;   

            if (has_colors() && value != 0) {
                int color_pair = 0;

                if (value == 2)
                    color_pair = 2;
                else if (value == 4)
                    color_pair = 4;
                else if (value == 8)
                    color_pair = 8;
                else if (value == 16)
                    color_pair = 16;
                else if (value == 32)
                    color_pair = 32;
                else if (value == 64)
                    color_pair = 64;
                else if (value == 128)
                    color_pair = 128;
                else if (value == 256)
                    color_pair = 8;
                else if (value == 512)
                    color_pair = 9;
                else if (value == 1024)
                    color_pair = 10;
                else if (value == 2048)
                    color_pair = 11;

                    if (color_pair > 0) {
                        wattron(win, COLOR_PAIR(color_pair));
                        mvwprintw(win, y_pos, x_pos - (count_digits(value) / 2), "%d", value);
                        wattroff(win, COLOR_PAIR(color_pair));
                    } else {
                        mvwprintw(win, y_pos, x_pos - (count_digits(value) / 2), "%d", value);
                    }
                } else {
                    mvwprintw(win, y_pos, x_pos - (count_digits(value) / 2), "%d", value);
                }
            }
        }
        wrefresh(win);
    }
    

int count_digits(int n) {
    if (n == 0)
        return 1;
    int count = 0;
    while (n != 0) {
        n /= 10;
        count++;
    }
    return count;
}
           
        
    

bool check_game_over(int board[][current_grid_size]) {
    
    for (int i = 0; i < current_grid_size; i++) {
        for (int j = 0; j < current_grid_size; j++) {
            if (board[i][j] == 0) {
                return false; 
            }
            if (board[i][j] == 2048) {
                has_won_2048 = true;
            }
        }
    }

    
    for (int i = 0; i < current_grid_size; i++) {
        for (int j = 0; j < current_grid_size; j++) {
            
            if (j < current_grid_size-1 && board[i][j] == board[i][j + 1]) {
                return false; 
            }

            if (i < current_grid_size-1 && board[i][j] == board[i + 1][j]) {
                return false; 
            }
        }
    }

    
    return true;
}

void add_new_tile(int board[][current_grid_size]) {

    int value = (rand() % 10 == 0) ? 4 : 2;

    int empty_cells = 0;
    for (int i = 0; i < current_grid_size; i++) {
        for (int j = 0; j < current_grid_size; j++) {
            if (board[i][j] == 0) {
                empty_cells++;
            }
        }
    }

    if (empty_cells > 0) {
        int random_index = rand() % empty_cells;
        int count = 0;
        for (int i = 0; i < current_grid_size; i++) {
            for (int j = 0; j < current_grid_size; j++) {
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

bool move_left(int board[][current_grid_size],int *score) {
    bool moved = false;
    for (int i = 0; i < current_grid_size; i++) {
        int non_zero_index = 0;
        for (int j = 0; j < current_grid_size; j++) {
            if (board[i][j] != 0) {
                board[i][non_zero_index++] = board[i][j];
                if (j != non_zero_index - 1) {
                    board[i][j] = 0;
                    moved = true;
                }
            }
        }

        for (int j = 0; j < current_grid_size-1; j++) {
            if (board[i][j] != 0 && board[i][j] == board[i][j + 1]) {
                board[i][j] *= 2;
                *score+=board[i][j];
                board[i][j + 1] = 0;
                moved = true;
                for (int k = j + 2; k < current_grid_size; k++) {
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

bool move_right(int board[][current_grid_size],int *score) {
    bool moved = false;
    for (int i = 0; i < current_grid_size; i++) {
        int non_zero_index = current_grid_size-1;
        for (int j = current_grid_size-1; j >= 0; j--) {
            if (board[i][j] != 0) {
                board[i][non_zero_index--] = board[i][j];
                if (j != non_zero_index + 1) {
                    board[i][j] = 0;
                    moved = true;
                }
            }
        }
        for (int j = current_grid_size-1; j > 0; j--) {
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

bool move_up(int board[][current_grid_size],int *score) {
    bool moved = false;
    for (int j = 0; j < current_grid_size; j++) {
        int non_zero_index = 0;
        for (int i = 0; i < current_grid_size; i++) {
            if (board[i][j] != 0) {
                board[non_zero_index++][j] = board[i][j];
                if (i != non_zero_index - 1) {
                    board[i][j] = 0;
                    moved = true;
                }
            }
        }
        for (int i = 0; i < current_grid_size-1; i++) {
            if (board[i][j] != 0 && board[i][j] == board[i + 1][j]) {
                board[i][j] *= 2;
                *score+=board[i][j];
                board[i + 1][j] = 0;
                moved = true;
                for (int k = i + 2; k < current_grid_size; k++) {
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

bool move_down(int board[][current_grid_size],int *score) {
    bool moved = false;
    for (int j = 0; j < current_grid_size; j++) {
        int non_zero_index = current_grid_size-1;
        for (int i = current_grid_size-1; i >= 0; i--) {
            if (board[i][j] != 0) {
                board[non_zero_index--][j] = board[i][j];
                if (i != non_zero_index + 1) {
                    board[i][j] = 0;
                    moved = true;
                }
            }
        }
        for (int i = current_grid_size-1; i > 0; i--) {
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




void setup_ncurses_colors() {
    if (has_colors()) {
        start_color();

        init_pair(1, COLOR_WHITE, COLOR_BLACK);
        init_pair(2, COLOR_CYAN, COLOR_BLACK);      
        init_pair(4, COLOR_GREEN, COLOR_BLACK);     
        init_pair(8, COLOR_YELLOW, COLOR_BLACK);    
        init_pair(16, COLOR_BLUE, COLOR_BLACK);     
        init_pair(32, COLOR_MAGENTA, COLOR_BLACK);  
        init_pair(64, COLOR_RED, COLOR_BLACK);      
        init_pair(128, COLOR_CYAN, COLOR_BLACK);    
        init_pair(256, COLOR_GREEN, COLOR_BLACK);
        init_pair(512, COLOR_YELLOW, COLOR_BLACK);
        init_pair(1024, COLOR_BLUE, COLOR_BLACK);
        init_pair(2048, COLOR_MAGENTA, COLOR_BLACK);
    }
}



