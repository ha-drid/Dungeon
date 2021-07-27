#include "Building.h"

void buildingInit(struct Building* building, const char* name, POINT pos, uint8_t world, char iD, const char* path)
{
    building->position = pos;
    building->world_id = world;
    building->iD = iD;
    strcpy_s(building->name, 20, name);

    locationInit(&(building->location), 20, 20);
    locationLoad(&(building->location), path);

    building->npc.count = 0;
    building->npc.data = NULL;
}

void buildingAddNpc(struct Building* building, const char* name, long x, long y, char iD)
{
    typedef struct Object TObj;

    uint32_t i = building->npc.count;

    ++building->npc.count;
    building->npc.data = (TObj*)malloc(sizeof(TObj) * building->npc.count);

    building->npc.data[i].iD = iD;
    building->npc.data[i].position.x = x;
    building->npc.data[i].position.y = y;
    building->npc.data[i].world_id = building->world_id;
    strcpy_s(building->npc.data[i].name, 20, name);
}

void buildingMapShow(struct Building* building, short x, short y)
{
    for (uint32_t i = 0; i < building->npc.count; ++i)
        locationPutObject(&(building->location), &(building->npc.data[i]));

    locationMapShow(&(building->location), x, y);
}

void buildingPutOnMap(struct Building* building, uint32_t width_map, uint32_t height_map, char** map)
{
    if ((building->position.y < 0) || (building->position.y >= height_map) ||
        (building->position.x < 0) || (building->position.x >= width_map))
        return;

    map[building->position.y][building->position.x] = building->iD;
}

void buildingDelete(struct Building* building)
{
    free(building->npc.data);
    building->npc.count = 0;

    locationDelete(&(building->location));
}
