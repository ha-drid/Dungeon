#include "Buildings.h"

/*
struct Object
{
    char iD;
    POINT position;
    uint8_t world_id;
    char name[20];
};
*/

void buildingsInit(struct Buildings* b, const char* file)
{
    b->capacity = 0;
    b->data = NULL;

    FILE* f;
    fopen_s(&f, file, "rt");
    char escaveMapFile[100];
    if (f)
    {
        while (feof(f) == NULL)
        {
            buildingsAdd(b);
            struct Building* p_building = b->data + (b->capacity - 1);

            locationInit(&(p_building->location), 30, 30);

            fgets(p_building->name, 1000, f);
            fscanf_s(f, "%c", &(p_building->iD));
            fscanf_s(f, "%ld", &(p_building->position.x));
            fscanf_s(f, "%ld", &(p_building->position.y));
            fscanf_s(f, "%hu", &(p_building->world_id));

            fscanf_s(f, "%s\n", escaveMapFile);

            locationLoad(&(p_building->location), escaveMapFile);
        }
    }
}

void buildingsAdd(struct Buildings* b)
{
    ++b->capacity;
    b->data = realloc(b->data, sizeof(struct Building) * b->capacity);
}

void buildingsPutOnMap(struct Buildings* b, uint32_t width_map, uint32_t height_map, char** map)
{
    for (uint32_t i = 0; i < b->capacity; ++i)
    {
        if ((b->data[i].position.y < 0) || (b->data[i].position.y >= height_map) ||
            (b->data[i].position.x < 0) || (b->data[i].position.x >= width_map))
            continue;

         map[b->data[i].position.y][b->data[i].position.x] = b->data[i].iD;
    }
}

void buildingsDelete(struct Buildings* b)
{
    for (uint32_t i = 0; i < b->capacity; ++i)
    {
        locationDelete(&(b->data[i].location));
    }
    b->capacity = 0;
    free(b->data);
}
