#include "Object.h"

void objectSave(struct Object* obj, const char* path)
{
    FILE* f = fopen(path, "wb");

        fwrite(obj, 1, sizeof(struct Object), f);

    fclose(f);
}

bool objectLoad(struct Object* obj, const char* save_file)
{
    FILE* f = fopen(save_file, "rb");

    if (f == NULL)
        return false;

        fread(obj, 1, sizeof(struct Object), f);

    fclose(f);

    return true;
}

