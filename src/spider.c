#include <rogue.h>

Entity* createSpid(Position pos, int hP, int attack) { //creates a spider type monster
    Entity* newSpid = calloc(1, sizeof(Entity));
    newSpid->pos = pos;
    newSpid->ch = 'S';
    newSpid->color = COLOR_PAIR(SPID_COLOR);
    newSpid->hP = hP;
    newSpid->maxHP = hP + (hP/5); //allows 1.2x overheal
    newSpid->attack = attack;
    newSpid->alive = true;
    return newSpid;
}

void spidTurn(void) { 
    for (int i = 0; i < monCount; i++) {
        if (!mons[i] || !mons[i]->alive || (mons[i]->ch != 'S')) {continue;} //skip if null, dead, or not spid
        if (combatDist(mons[i]->pos, player->pos) == 1) { //checks if spid 1 tile away from player and attacks if true
            attack(mons[i], player);
            continue;
        }
        if (lineOfSight(mons[i]->pos, player->pos)) { //checks and moves spid if in LOS of player
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