#include <rogue.h>

Room createRoom(int y, int x, int height, int width) { //creates room, takes a y and x position and room dimensions
    Room newRoom;
    newRoom.pos.y = y;
    newRoom.pos.x = x;
    newRoom.height = height;
    newRoom.width = width;
    newRoom.center.y = y + (int)(height / 2);
    newRoom.center.x = x + (int)(width / 2);
    return newRoom;
}

void addRoomToMap(Room room) { //creates given room on map, fills with specified character
    for (int y = room.pos.y; y < room.pos.y + room.height; y++) {
        for (int x = room.pos.x; x < room.pos.x + room.width; x++) {
            map[y][x].ch = '.';
            map[y][x].walkable = true;
            map[y][x].transparent = true;
        }
    }
}

void connectRooms(Position centerOne, Position centerTwo) { //creates a one tile wide hallway between disconnected rooms
    Position temp;
    temp.x = centerOne.x;
    temp.y = centerOne.y;
    while (true) { //algorithm for finding the most optimal path between the center of two rooms, if disconnected creates a connection
        if (abs((temp.x - 1) - centerTwo.x) < abs(temp.x - centerTwo.x))
            temp.x--;
        else if (abs((temp.x + 1) - centerTwo.x) < abs(temp.x - centerTwo.x))
            temp.x++;
        else if (abs((temp.y - 1) - centerTwo.y) < abs(temp.y - centerTwo.y))
            temp.y--;
        else if (abs((temp.y + 1) - centerTwo.y) < abs(temp.y - centerTwo.y))
            temp.y++;
        else break;
        map[temp.y][temp.x].ch = '.';
        map[temp.y][temp.x].walkable = true;
        map[temp.y][temp.x].transparent = true;
    }
}