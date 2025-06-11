#include <rogue.h>

bool cursesSetup(void) { //sets up ncurses library, displays error msg if computer does not support color
    initscr();
    noecho();
    curs_set(0);
    if (has_colors()) {
        start_color();
        init_pair(VISIBLE_COLOR, COLOR_WHITE, COLOR_BLACK);
        init_pair(SEEN_COLOR, COLOR_BLUE, COLOR_BLACK);
        return true;
    }
    else {
        mvprintw(20, 50, "SYSTEM DOES NOT SUPPORT COLOR");
        getch();
        return false;
    }
}

void gameLoop(void) { //gameplay loop, ends game when user presses specified character
    int ch;

    makeFOV(player);
    drawEverything();

    while(ch = getch()) {
        if (ch == 'q') {break;}
        handleInput(ch);
        gobTurn();
        drawEverything();
    }
}

void closeGame(void) { //exits game and frees leftover memory
    endwin();
    free(player);
    
    for (int i = 0; i < monCount; i++) {
        if (mons[i]) {
            free(mons[i]);
        }
    }
    free(mons);
}