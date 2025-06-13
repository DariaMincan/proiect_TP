#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ncurses.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include "game.h"        
#include "multiplayer.h" 
#include "menu.h"     


int main() {
 

    init_ncurses();
    setup_ncurses_colors(); 
    srand(time(NULL));
    run_main_menu();      
    close_ncurses();
    return 0;
}


