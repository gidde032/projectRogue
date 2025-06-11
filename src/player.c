#include <rogue.h>

Entity* createPlayer (Position start_pos) { //takes starting position and spawns player with specified icon, color, hP/maxHP, atk and alive bool
    Entity* newPlayer = calloc(1, sizeof(Entity));
    
    newPlayer->pos.y = start_pos.y;
    newPlayer->pos.x = start_pos.x;
    newPlayer->ch = '?';
    newPlayer->maxHP = 100;
    newPlayer->hP = 75;
    newPlayer->attack = 4;
    newPlayer->alive = true;
    newPlayer->color = COLOR_PAIR(VISIBLE_COLOR);
    return newPlayer; 
}

void handleInput(int input) { //controls, wasd movement
    Position newPos = {player->pos.y, player->pos.x};
    switch(input) {
        case 'w':
            newPos.y--;
            break;
        case 's':
            newPos.y++;
            break;
        case 'a':
            newPos.x--;
            break;
        case 'd':
            newPos.x++;
            break;
        default:
            break;
    }
    movePlayer(newPos);
}

void movePlayer(Position newPos) { //resets fov and creates new one after each legal player movement
    {
        if (map[newPos.y][newPos.x].walkable && !checkPColl(newPos)) { //checks mon collision
            clearFOV(player);
            player->pos = newPos;
            makeFOV(player);
        }
    }
}