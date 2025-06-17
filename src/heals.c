#include <rogue.h>

void useHeal(Heal* heal) { //boosts players hP by the heal's healing up to maxHP, changes heal icon and zeroes healing;
    heal->used = true;
    heal->ch = '0';
    player->hP = player->hP + heal->healing;
    if (player->hP > player->maxHP) {player->hP = player->maxHP;}
    heal->healing = 0;
}

Heal* createMedkit(Position pos) { //best hp regeneration item
    Heal* medkit = calloc(1, sizeof(Heal));
    medkit->pos = pos;
    medkit->ch = '+';
    medkit->color = COLOR_PAIR(HEALS_COLOR);
    medkit->healing = 50;
    medkit->used = false;
    return medkit;
}

Heal* createBandage(Position pos) {
    Heal* bandage = calloc(1, sizeof(Heal));
    bandage->pos = pos;
    bandage->ch = '*';
    bandage->color = COLOR_PAIR(HEALS_COLOR);
    bandage->healing = 25;
    bandage->used = false;
    return bandage;
}
