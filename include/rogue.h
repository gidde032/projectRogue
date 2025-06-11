#ifndef ROGUE_H
#define ROGUE_H

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//color pairs for entities and tiles
#define VISIBLE_COLOR 1
#define SEEN_COLOR 2
#define GOB_COLOR 3

/* typedef struct {
    Tile** tiles;
    int numRooms;
    //int numMonsters;
    struct Room** lRooms;
    //struct Monster** lMonsters;
} Level; */

typedef struct { //position for rooms, players, etc.
    int y;
    int x;
} Position;

typedef struct { //map tiles
    char ch;
    int color;
    bool walkable;
    bool transparent;
    bool visible;
    bool seen;
} Tile;

typedef struct { //room, pos points to corner of room and center points to middle
    int height;
    int width;
    Position pos;
    Position center;
} Room;

typedef struct { //entities such as the player
    Position pos;
    char ch;
    int color;
    int hP;
    int maxHP;
    int attack;
    bool alive;
} Entity;

//draw funcs
void drawMap(void);
void drawEntity(Entity* entity);
void drawEverything(void);

//main funcs
bool cursesSetup(void);
void gameLoop(void);
void closeGame(void);

//map funcs
Tile** createMapTiles(void);
Position setupMap(void);
void freeMap(void);

//player funcs
Entity* createPlayer(Position start_pos);
void handleInput(int input);
void movePlayer(Position newPos);

//chests funcs
// Entity* createChest (Position chest_pos);

//room funcs
Room createRoom(int y, int x, int height, int width);
void addRoomToMap(Room room);
void connectRooms(Position centerOne, Position centerTwo);

//fov funcs
void makeFOV(Entity* player);
void clearFOV(Entity* player);
int getDistance(Position origin, Position target);
bool isInMap(int y, int x);
bool lineOfSight(Position origin, Position target);
int getSign(int a);

//goblin funcs
Entity* createGoblin(Position pos, int hP, int attack);
void gobTurn(void);
bool checkGColl(Position newPos);


//combat funcs
void attack(Entity* attacker, Entity* defender);
bool checkPColl(Position newPos);

//externs
extern Entity* player;
extern const int MAP_HEIGHT;
extern const int MAP_WIDTH;
extern Tile** map;
extern Entity** mons;
extern int monCount;

#endif