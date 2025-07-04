#include <rogue.h>

//extern declarations
Entity* player;
const int MAP_HEIGHT = 25;
const int MAP_WIDTH = 100;
Tile** map;
Entity** mons = NULL;
Heal** heals = NULL;
int monCount = 0;
int healCount = 0;
Item** items;
int itemCount = 0;
int currentLevel = 0;
int maxLevels = 3;
int monsJugged = 0;

int main(void) {
    Position start_pos;
    bool workingComputer = cursesSetup(); //sets up ncurses package and game window
    if (workingComputer) {
        srand(time(NULL)); //seeds random generator
        map = createMapTiles(); //generates starting map
        mons = calloc(200, sizeof(Entity*)); //creates monster array
        heals = calloc(30, sizeof(Heal*)); //creates heals array
        items = calloc(30, sizeof(Item*));//creates items array
        start_pos = setupMap(); //generates starting position
        player = createPlayer(start_pos); //generates player
        showTitleScreen(); 
        gameLoop(); //gameplay loop
        showDeathScreen();
        closeGame(); //frees memory when quit
    }
    else {
        endwin();
    }
    return 0;
}