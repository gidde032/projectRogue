#include <rogue.h>

void makeFOV(Entity* player) { //builds the player's FOV
    int y, x, distance;
    int RADIUS = 15;
    Position target;

    map[player->pos.y][player->pos.x].visible = true;
    map[player->pos.y][player->pos.x].seen = true;

    for (y = player->pos.y - RADIUS; y < player->pos.y + RADIUS; y++) {
        for (x = player->pos.x - RADIUS; x < player->pos.x + RADIUS; x++) {
            target.y = y;
            target.x = x;
            distance = getDistance(player->pos, target);
            if (distance < RADIUS) {
                if (isInMap(y, x) && lineOfSight(player->pos, target)) {
                    map[y][x].visible = true;
                    map[y][x].seen = true;
                }
            }

        }
    }
}

void clearFOV(Entity* player) { //resets FOV for next iteration
    int y, x;
    int RADIUS = 15;
    for (y = player->pos.y - RADIUS; y < player->pos.y + RADIUS; y++) {
        for (x = player->pos.x - RADIUS; x < player->pos.x + RADIUS; x++) {
            if (isInMap(y, x))
                map[y][x].visible = false;
        }
    }
}

int getDistance(Position origin, Position target) { //distance calculator
    double dy, dx;
    int distance;
    dx = target.x - origin.x;
    dy = target.y - origin.y;
    distance = floor(sqrt((dx * dx) + (dy * dy)));
    return distance;
}

bool isInMap(int y, int x) { //checks if tile is within bounds of map
    if ((0 < y && y < MAP_HEIGHT - 1) && (0 < x && x < MAP_WIDTH - 1)) {
        return true;
    }
    else return false;
}

bool lineOfSight(Position origin, Position target) { //goes through tiles from origin to target looking for non transparent tiles, if it finds one returns true
    int t, x, y, absDX, absDY, signX, signY, dX, dY;
    dX = origin.x - target.x;
    dY = origin.y - target.y;
    absDX = abs(dX);
    absDY = abs(dY);
    signX = getSign(dX);
    signY = getSign(dY);
    x = target.x;
    y = target.y;
    if (absDX > absDY) {
        t = absDY * 2 - absDX;
        do { 
            if (t >= 0) {
                y += signY;
                t -= absDX * 2;
            }
            x += signX;
            t += absDY * 2;
            if (x == origin.x && y == origin.y) {
                return true;
            }
        }
        while (map[y][x].transparent);
        return false;
    }
    else {
        t = absDX * 2 - absDY;
        do { 
            if (t >= 0) {
                x += signX;
                t -= absDY * 2;
            }
            y += signY;
            t += absDX * 2;
            if (x == origin.x && y == origin.y) {
                return true;
            }
        }
        while (map[y][x].transparent);
        return false;
    }
}    

int getSign(int a) { 
    return (a < 0) ? -1 : 1;
}