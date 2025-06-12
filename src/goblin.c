#include <rogue.h>

Entity* createGoblin(Position pos, int hP, int attack) { //creates a goblin type monster
    Entity* newGob = calloc(1, sizeof(Entity));
    newGob->pos = pos;
    newGob->ch = 'G';
    newGob->color = COLOR_PAIR(GOB_COLOR);
    newGob->hP = hP;
    newGob->maxHP = hP + (hP/5); //allows 1.2x overheal
    newGob->attack = attack;
    newGob->alive = true;
    return newGob;
}

void gobTurn(void) {
    for (int i = 0; i < monCount; i++) {
        if (!mons[i] || !mons[i]->alive || (mons[i]->ch != 'G')) {continue;} //skip if null, dead, or not a gob
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