#include <rogue.h>

Entity* createTroll(Position pos, int hP, int attack) { //creates a troll type monster
    Entity* newTroll = calloc(1, sizeof(Entity));
    newTroll->pos = pos;
    newTroll->ch = 'T';
    newTroll->color = COLOR_PAIR(TROLL_COLOR);
    newTroll->hP = hP;
    newTroll->maxHP = hP + (hP/5); //allows 1.2x overheal
    newTroll->attack = attack;
    newTroll->alive = true;
    return newTroll;
}

void trollTurn(void) {
    for (int i = 0; i < monCount; i++) {
        if (!mons[i] || !mons[i]->alive || (mons[i]->ch != 'T')) {continue;} //skip if null, dead, or not a gob
        if (combatDist(mons[i]->pos, player->pos) == 1) { //checks if gob w/in one tile of player and attacks
            attack(mons[i], player);
            continue;
        }
        if (lineOfSight(mons[i]->pos, player->pos)) { //gob moves if in player LOS
            Position delta = {((player->pos.y > mons[i]->pos.y) ? 1 : -1), ((player->pos.x > mons[i]->pos.x) ? 1 : -1)};
            Position newPos = {(mons[i]->pos.y + delta.y), (mons[i]->pos.x + delta.x)};
            if(map[newPos.y][newPos.x].walkable && !checkMonColl(newPos)) {
                clearFOV(player);
                mons[i]->pos = newPos;
                makeFOV(player);
            }
        }
    }
}