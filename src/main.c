#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>
#include <stdint-gcc.h>
#include <locale.h>
#include <windows.h>
#include <conio.h>
#include <pthread.h>

#include "Object.h"
#include "Location.h"
#include "Player.h"
#include "Building.h"
#include "Buildings.h"
#include "main.h"
#include "Inventory.h"
#include "Item.h"

void playerBuildingEvent(struct Player* player, struct Building* obj)
{
    POINT exit_escave;
    for (uint32_t y = 0; y < obj->location.height; ++y)
        for (uint32_t x = 0; x < obj->location.width; ++x)
            if (obj->location.mapInFile[y][x] == '!')
                playerSetPosition(player, x, y);
            else if (obj->location.mapInFile[y][x] == 'E') {
                exit_escave.x = x;
                exit_escave.y = y;
            }

    system("cls");
    while (GetAsyncKeyState(VK_ESCAPE) >= 0)
    {
        locationMapInit(&(obj->location));

        playerPutOnMap(player, obj->location.width, obj->location.height, obj->location.map);

        buildingMapShow(obj, 0, 2);
        printf("\n\nE = exit escave");

        playerMoveMap(player, &(obj->location));

        for (uint32_t i = 0; i < obj->npc.count; ++i)
            if (playerObjectColision(player, &(obj->npc.data[i]), )

        playerPosRetreat(player, &(obj->location), '#');

        if (pointCMP(player->position, exit_escave))
            break;

        Sleep(100);
    }

    player->position.x = obj->position.x;
    player->position.y = obj->position.y;
    system("cls");
    Sleep(500);
}

int main()
{
    setlocale(LC_ALL, "ru");

    struct Player player;
    playerLoadSaveGame(&player, escaveGetPos, "res\\save_game\\Namys");

    struct Location location;
    locationInit(&location, 130, 30);
    playerLoadLocation(&player, &location);

    pthread_t th1;

    void *move(void* arg) {

        playerMoveMap(&player, &location);
        playerPosRetreat(&player, &location, '#');

        pthread_exit(&th1);

        return NULL;
    }

    struct Building podish;
    buildingInit(&podish, "Podish", ESCAVE_POS[0][0], 0,'E', "res\\world\\fostral\\escaves\\main_escave.txt");
    buildingAddNpc(&podish, "Lipkiy", 5, 5, 'L');

    struct Item item;
    itemInit(&item, 's', 15, 15, 0, sword);

    while (GetAsyncKeyState(VK_ESCAPE) >= 0)
    {
        pthread_create(&th1, NULL, move, NULL);
        pthread_detach(th1);

        locationMapInit(&location);

        buildingPutOnMap(&podish, location.width, location.height, location.map);
        playerPutOnMap(&player, location.width, location.height, location.map);
        itemPutOnMap(&item, location.width, location.height, location.map);

        //buildingsPutOnMap(&b, location.width, location.height, location.map);

        if (GetAsyncKeyState(VK_SPACE) < 0)
            playerBuildingColision(&player, &podish, playerBuildingEvent);

        if (GetAsyncKeyState('E') < 0) {
            system("cls");
            while (GetAsyncKeyState(VK_ESCAPE) >= 0)
            {
                inventoryShow(&(player.bag), 0, 2);
            }
            system("cls");
        }
        if (vangerItemColision(&player, &item)) {
            inventoryPush(&(player.bag), &item);
            item.position.x = -1;
            item.position.y = -1;
            }
        locationMapShow(&location, 0, 2);

    }

    buildingDelete(&podish);
    playerSave(&player, "res\\save_game\\Namys");
    playerDelete(&player);
    //buildingsDelete(&b);

    locationDelete(&location);

    return 0;
}
