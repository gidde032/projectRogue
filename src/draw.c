#include <rogue.h>

void drawMap(void) { //determines color and draws map
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (map[y][x].visible) {
                mvaddch(y, x, map[y][x].ch | map[y][x].color); //visible in white
            }
            else if (map[y][x].seen) {
                mvaddch(y, x, map[y][x].ch | COLOR_PAIR(SEEN_COLOR)); //seen in blue
            }
            else {
                mvaddch(y, x, ' '); //empty char otherwise
            }
        }
    }
}

void drawEntity(Entity* entity) {  //determines color and draws player
    mvaddch(entity->pos.y, entity->pos.x, entity->ch | entity->color);
}

void drawEverything(void) { //clears window and draws player + map + mons
    clear();
    drawMap();
    for (int i = 0; i < monCount; i++) { //draws all visible monsters
        if (map[mons[i]->pos.y][mons[i]->pos.x].visible) {
            drawEntity(mons[i]);
        }
    } 
    drawEntity(player);
    mvprintw(0,0, "HP: %d/%d. Don't get jugged.", player->hP, player->maxHP);
}