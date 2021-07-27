#include "Item.h"

void itemInit(struct Item* item, char iD, long x, long y, uint16_t world_id, uint16_t type)
{
    item->iD = iD;
    item->type = type;
    item->position.x = x;
    item->position.y = y;
    item->world_id = world_id;
}

void itemPutOnMap(struct Item* item, uint32_t width_map, uint32_t height_map, char** map)
{
    if ((item->position.y < 0) || (item->position.y >= height_map) ||
        (item->position.x < 0) || (item->position.x >= width_map))
        return;

    map[item->position.y][item->position.x] = item->iD;
}
