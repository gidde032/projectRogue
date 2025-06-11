#include <rogue.h>

void drawMap(void) { //determines color and draws map
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (map[y][x].visible) {
                mvaddch(y, x, map[y][x].ch | map[y][x].color);
            }
            else if (map[y][x].seen) {
                mvaddch(y, x, map[y][x].ch | COLOR_PAIR(SEEN_COLOR));
            }
            else {
                mvaddch(y, x, ' ');
            }
        }
    }
}

void drawEntity(Entity* entity) {  //determines color and draws player
    mvaddch(entity->pos.y, entity->pos.x, entity->ch | entity->color);
}

void drawEverything(void) { //clears window and draws player + map
    clear();
    drawMap();
    for (int i = 0; i < monCount; i++) { //draws alive monsters
        if (map[mons[i]->pos.y][mons[i]->pos.x].visible) {
            drawEntity(mons[i]);
        }
    } 
    drawEntity(player);
    mvprintw(0,0, "HP: %d/%d. Don't get jugged.", player->hP, player->maxHP);
}