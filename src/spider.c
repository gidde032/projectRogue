/* #include <rogue.h>

Entity* createSpider(Position pos, int hP, int attack) { //creates a goblin type monster
    Entity* newSpider = calloc(1, sizeof(Entity));
    newSpider->pos = pos;
    newSpider->ch = 'G';
    newSpider->color = COLOR_PAIR(VISIBLE_COLOR);
    newSpider->hP = hP;
    newSpider->maxHP = hP + (hP/5); //allows 1.2x overheal
    newSpider->attack = attack;
    newSpider->alive = true;
    return newSpider;
}

void spiderTurn(void) {
    for (int i = 0; i < monCount; i++) {
        if (mons[i]->alive && lineOfSight(mons[i]->pos, player->pos)) {
            Position delta = {((player->pos.y > mons[i]->pos.y) ? 1 : -1), ((player->pos.x > mons[i]->pos.x) ? 1 : -1)};
            Position newPos = {(mons[i]->pos.y + delta.y), (mons[i]->pos.x + delta.x)};
            if(map[newPos.y][newPos.x].walkable && !checkPColl(newPos)) {
                mons[i]->pos = newPos;
            }
        }
    }
} */