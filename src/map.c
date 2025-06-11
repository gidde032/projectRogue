#include <rogue.h>

Tile** createMapTiles(void) { //generates base map with only wall tiles
    Tile** tiles = calloc(MAP_HEIGHT, sizeof(Tile*));;

    for (int y = 0; y < MAP_HEIGHT; y++) {
        tiles[y] = calloc(MAP_WIDTH, sizeof(Tile));
        for (int x = 0; x < MAP_WIDTH; x++) {
            tiles[y][x].ch = '#';
            tiles[y][x].color = COLOR_PAIR(VISIBLE_COLOR);
            tiles[y][x].walkable = false;
            tiles[y][x].transparent = false;
            tiles[y][x].visible = false;
            tiles[y][x].seen = false;
        }
    }
    return tiles;
}

Position setupMap(void) {
    int y, x, height, width, n_rooms;
    //chestsPlaced = 0;
    //n_chests = (rand() % 6) + 4;
    n_rooms = (rand() % 20) + 12;
    Room* rooms = calloc(n_rooms, sizeof(Room));
    //Entity** chests = calloc(n_chests, sizeof(Entity));
    Position start_pos;

    for (int i = 0; i < n_rooms; i++) { //auto-gens between 12-32 rooms with a width of 5-17 tiles and a height of 3-9 tiles
        y = (rand() % (MAP_HEIGHT - 9)) + 1;
        x = (rand() % (MAP_WIDTH - 17)) + 1;
        height = (rand() % 6) + 3;
        width = (rand() % 12) + 5;
        rooms[i] = createRoom(y, x, height, width);
        addRoomToMap(rooms[i]);
       /* if (chestsPlaced < n_chests) {
            chests[chestsPlaced] = createChest(rooms[i].center);
            chestsPlaced++;
        } */
        if (i > 0) { //after first room connects separated rooms
            connectRooms(rooms[i-1].center, rooms[i].center);
        }
    }

    for (int z = 0; z < n_rooms; z += 3) { //draws goblins for every 3 rooms, balances amt of mons
        int gobY = (rand() % (rooms[z].height - 2)) + rooms[z].pos.y + 1; //random y-pos for gob in room
        int gobX = (rand() % (rooms[z].width - 2)) + rooms[z].pos.x + 1; //random x-pos for gob in room
        Position gobPos = {gobY, gobX};
        Entity* gob = createGoblin(gobPos, ((rand() % 6) + 6), ((rand() % 3) + 1)); //creates gob hP and atk, hP is (6 +- 6) and atk is (1 +- 3) currently
        mons[monCount++] = gob;
    } 

    start_pos.y = rooms[0].center.y;
    start_pos.x = rooms[0].center.x;
    free(rooms);
    return start_pos;
}

void freeMap(void) {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        free(map[y]);
    }
    free(map);
}