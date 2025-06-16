#include <rogue.h>

void attack(Entity* attacker, Entity* defender) {
    defender->hP -= attacker->attack;
    if (defender->hP <= 0) {
        defender->alive = false;
        defender->ch = 'X';   
    }
}

bool checkPColl(Position newPos) { //player collision physics
    for (int i = 0; i < monCount; i++) {
        if (mons[i]->alive && (mons[i]->pos.y == newPos.y) && (mons[i]->pos.x == newPos.x)) {
            attack(player, mons[i]);
            return true;
        }
    }
    for (int i = 0; i < healCount; i++) {
        if (!(heals[i]->used) && (heals[i]->pos.y == newPos.y) && (heals[i]->pos.x == newPos.x)) { //uses unused heals if on same tile as player
            useHeal(heals[i]);
            return true;
        }
    }
    return false;
}

bool checkMonColl(Position newPos) { //monster collision physics
    for (int i = 0; i < monCount; i++) {
        if ((player->pos.y == newPos.y) && (player->pos.x == newPos.x)) { //on mon turn checks if mon moves into and attacks player
                attack(mons[i], player);
                return true;
        }
        for (int j = 0; j < monCount; j++) { //stops mons from grouping on same tile
            if ((mons[j]->pos.y == newPos.y) && (mons[j]->pos.x == newPos.x)) {return true;}
        }
        for (int k = 0; k < healCount; k++) { //stops mons from going on same tile as unused heals
            if (!(heals[k]->used) && (heals[k]->pos.y == newPos.y) && (heals[k]->pos.x == newPos.x)) {return true;}
        }
    }
    return false;
}

int combatDist(Position a, Position b) { //distance checking func for player-mon combat
    return abs(a.y - b.y) + abs(a.x - b.x);
}