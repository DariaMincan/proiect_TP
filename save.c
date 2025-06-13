#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ncurses.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include "menu.h"
#include "game.h"
#include "multiplayer.h"
#include "gamestate.h"
#include "save.h"





bool save_game(const GameState *state, const char *filename) {
    FILE *fp = fopen(filename, "wb"); 
    if (fp == NULL) {
        perror("Error opening file for saving");
        return false;
    }

    
    size_t written = fwrite(state, sizeof(GameState), 1, fp);
    fclose(fp);

    if (written != 1) {
        perror("Error writing game state to file");
        return false;
    }
    return true;
}

bool load_game(GameState *state, const char *filename) {
    FILE *fp = fopen(filename, "rb"); 
    if (fp == NULL) {
        perror("Error opening file for loading"); 
        return false; 
    }

 
    size_t read = fread(state, sizeof(GameState), 1, fp);
    fclose(fp);

    if (read != 1) {
        perror("Error reading game state from file");
        return false;
    }
    return true;
}


bool check_saved_game_exists(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp != NULL) {
        fclose(fp);
        return true;
    }
    return false;
}