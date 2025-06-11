#include <rogue.h>

void attack(Entity* attacker, Entity* defender) {
    defender->hP -= attacker->attack;
    if (defender->hP <= 0) {
        defender->alive = false;
        defender->ch = 'X';
    }
}

bool checkPColl(Position newPos) {
    for (int i = 0; i < monCount; i++) {
        if (mons[i]->alive && (mons[i]->pos.y == newPos.y) && (mons[i]->pos.x == newPos.x) && (map[mons[i]->pos.y][mons[i]->pos.x].ch != 'G')) {
            attack(player, mons[i]);
            return true;
        }
        if ((player->pos.y == newPos.y) && (player->pos.x == newPos.x)) { //on gob turn checks if gob moves into and attacks player
            attack(mons[i], player);
            return true;
        }
    }
    return false;
}