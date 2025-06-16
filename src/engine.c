#include <rogue.h>

bool cursesSetup(void) { //sets up ncurses library, displays error msg if computer does not support color
    initscr();
    noecho();
    curs_set(0);
    if (has_colors()) { //entity and tile color initialization
        start_color();
        init_pair(VISIBLE_COLOR, COLOR_WHITE, COLOR_BLACK);
        init_pair(SEEN_COLOR, COLOR_BLUE, COLOR_BLACK);
        init_pair(PLAYER_COLOR, COLOR_YELLOW, COLOR_BLACK);
        init_pair(GOB_COLOR, COLOR_GREEN, COLOR_BLACK);
        init_pair(SPID_COLOR, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(TROLL_COLOR, COLOR_CYAN, COLOR_BLACK);
        init_pair(HEALS_COLOR, COLOR_RED, COLOR_BLACK);
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

    while(ch = getch()) { //input handling core of game
        if (ch == 'q') {break;}
        handleInput(ch);
        drawEverything();
        gobTurn();
        spidTurn();
        trollTurn();
        if (player->hP <= 0) {break;} //kills player if mons jugged them
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