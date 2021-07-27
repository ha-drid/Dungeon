#include "Vanger.h"

void vangerInit(struct Vanger* vanger,
                char iD,
                uint8_t world_id,
                uint8_t escave,
                const char* name,
                POINT (*escaveGetPos)(uint8_t world, uint8_t escave),
                uint32_t inventory_height,
                uint32_t inventory_width)
{
    vanger->position = escaveGetPos(world_id, escave);

    strcpy_s(vanger->name, 20, name);
    vanger->world_id = world_id;
    vanger->escave_id = escave;
    vanger->iD = iD;

    inventoryInit(&(vanger->bag), inventory_width, inventory_height);
}

bool vangerItemColision(struct Vanger* vanger, struct Item* item)
{
    return pointCMP(vanger->position, item->position);
}

void vangerDelete(struct Vanger* vanger) {
    inventoryDelete(&(vanger->bag));
}
