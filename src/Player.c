#include "Player.h"

void playerInit(struct Player* player,
                char iD,
                uint8_t world_id,
                uint8_t escave,
                const char* name,
                POINT (*escaveGetPos)(uint8_t world, uint8_t escave))
{
    vangerInit(player, iD, world_id, escave, name, escaveGetPos, 4, 4);
}

void playerLoadSaveGame(struct Player* player, POINT (*escaveGetPos)(uint8_t world, uint8_t escave), const char* path)
{
    struct stat s = { 0 };
    if (stat(path, &s) == -1) {
        mkdir(path);
    }

    char str[100];
    uint32_t count = 100;
    void clear() {
        memset(str, ' ', count);
        str[0] = '\0';
    }

    clear();
    strcat_s(str, count, path);
    strcat_s(str, count, "\\Player");

    if (objectLoad(player, str) == false) {

        playerInit(player, 'V', 0, 0, path, escaveGetPos);
        playerSave(player, path);
        return;

    }

    clear();
    strcat_s(str, count, path);
    strcat_s(str, count, "\\Bag");
    inventoryLoad(&(player->bag), str);
}

void playerLoadLocation(struct Player* player, struct Location* loc)
{
    char c[100];

    sprintf(c, "res\\world\\fostral\\world.txt");

    locationLoad(loc, c);
}

void playerSetPosition(struct Player* player, long x, long y)
{
    player->position.x = x;
    player->position.y = y;
}

void playerMoveMap(struct Player* player, struct Location* loc)
{
    player->oldPosition = player->position;

    if (GetAsyncKeyState ('W') < 0) --player->position.y;
    if (GetAsyncKeyState ('S') < 0) ++player->position.y;
    if (GetAsyncKeyState ('A') < 0) --player->position.x;
    if (GetAsyncKeyState ('D') < 0) ++player->position.x;

     if ((player->position.x < -1) || (player->position.x >= loc->width ))
        return;

    if (player->position.y <= -1)
        player->position.y = (long)loc->height - 1;

    if (player->position.y >= (long)loc->height)
        player->position.y = 0;
}

void playerPutOnMap(struct Player* player, uint32_t width_map, uint32_t height_map, char** map)
{
    // if ((player->position.y < 0) || (player->position.y >= height_map) ||
    //    (player->position.x < 0) || (player->position.x >= width_map))
    //    return;

    map[player->position.y][player->position.x] = player->iD;
}

void playerPosRetreat(struct Player* player, struct Location* loc, const char symbol)
{
    if (loc->map[player->position.y][player->position.x] == symbol)
        player->position = player->oldPosition;
}

void playerObjectColision(struct Player* player, struct Object* obj, void (*event)(struct Player* player, struct Object* obj))
{
    if ( (player->position.x == obj->position.x) &&
         (player->position.y == obj->position.y) )
    {
        event(player, obj);
    }
}

void playerBuildingColision(struct Player* player, struct Building* obj, void (*event)(struct Player* player, struct Building* obj))
{
    if ( (player->position.x == obj->position.x) &&
         (player->position.y == obj->position.y))
    {
        event(player, obj);
    }
}

void playerSave(struct Player* player, const char* path)
{
    char str[100];
    uint32_t count = 100;
    void clear() {
        memset(str, ' ', count);
        str[0] = '\0';
    }

    clear();
    strcat_s(str, count, path);
    strcat_s(str, count, "\\player");
    objectSave(player, str);

    clear();
    strcat_s(str, count, path);
    strcat_s(str, count, "\\bag");
    inventorySave(&(player->bag), str);
}

void playerDelete(struct Player* player)
{
    vangerDelete(player);
}
