#include "Inventory.h"

void inventoryInit(struct Inventory* inv, uint32_t width, uint32_t height)
{
    inv->slots.height = height;
    inv->slots.width = width;

    typedef struct Slot TSlot;

    inv->slots.data = (TSlot**)malloc(sizeof(TSlot*) * height);

    for (uint32_t i = 0; i < height; ++i)
        inv->slots.data[i] = (TSlot*)malloc(sizeof(TSlot) * width);

    for (uint32_t y = 0; y < height; ++y)
        for (uint32_t x = 0; x < width; ++x)
        {
            inv->slots.data[y][x].count = 0;
            memset(&inv->slots.data[y][x].item, 0, sizeof(struct Item));
        }
}

void inventoryShow(struct Inventory* inv, short x, short y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    for (uint32_t y = 0; y < inv->slots.height; ++y)
    {
        for (uint32_t x = 0; x < inv->slots.width; ++x)
        {
            printf("  iD:%hu count:%u  ", inv->slots.data[y][x].item.type, inv->slots.data[y][x].count);
        }
        printf("\n");
    }
}

void inventoryPush(struct Inventory* inv, const struct Item* const item)
{
    for (uint32_t y = 0; y < inv->slots.height; ++y) {
        for (uint32_t x = 0; x < inv->slots.width; ++x) {
            if (inv->slots.data[y][x].item.type == 0) {

                inv->slots.data[y][x].item.iD = item->iD;
                inv->slots.data[y][x].item.position = item->position;
                inv->slots.data[y][x].item.type = item->type;
                inv->slots.data[y][x].item.world_id = item->world_id;

                inv->slots.data[y][x].count = 1;
                return;
            }
            else if (inv->slots.data[y][x].item.type == item->type) {

                inv->slots.data[y][x].item.iD = item->iD;
                inv->slots.data[y][x].item.position = item->position;
                inv->slots.data[y][x].item.type = item->type;
                inv->slots.data[y][x].item.world_id = item->world_id;

                ++inv->slots.data[y][x].count;
                return;
            }
        }
    }
}

void inventorySave(struct Inventory* inv, const char* path)
{
    FILE* f;
    fopen_s(&f, path, "wb");

    fwrite(&(inv->slots.width), 1, sizeof(inv->slots.width), f);
    fwrite(&(inv->slots.height), 1, sizeof(inv->slots.height), f);

    for (uint32_t y = 0; y < inv->slots.height; ++y)
        for (uint32_t x = 0; x < inv->slots.width; ++x)
            fwrite(&(inv->slots.data[y][x]), 1, sizeof(struct Slot), f);

    fclose(f);
}

void inventoryLoad(struct Inventory* inv, const char* path)
{
    FILE* f;
    fopen_s(&f, path, "rb");

    fread(&(inv->slots.width), 1, sizeof(inv->slots.width), f);
    fread(&(inv->slots.height), 1, sizeof(inv->slots.height), f);

    inventoryInit(inv, inv->slots.width, inv->slots.width);

    for (uint32_t y = 0; y < inv->slots.height; ++y)
    {
        for (uint32_t x = 0; x < inv->slots.width; ++x)
        {
            fread(&(inv->slots.data[y][x]), 1, sizeof(inv->slots.data[y][x]), f);
        }
    }

    fclose(f);
}

void inventoryDelete(struct Inventory* inv)
{
    for (uint32_t i = 0; i < inv->slots.height; ++i)
        free(inv->slots.data[i]);

    free(inv->slots.data);
    inv->slots.height = 0;
    inv->slots.width = 0;
}
