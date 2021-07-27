#include "Location.h"

void locationInit(struct Location* loc, uint32_t width, uint32_t height)
{
    loc->width = width;
    loc->height = height;

    loc->map = (char**)malloc(sizeof(char*) * height);
    loc->mapInFile = (char**)malloc(sizeof(char*) * height);

    for (uint32_t i = 0; i < height; ++i)
    {
        loc->map[i] = (char*)malloc(sizeof(char) * (width + 1));
        loc->mapInFile[i] = (char*)malloc(sizeof(char) * (width + 1));
    }

    for (uint32_t y = 0; y < loc->height; ++y)
    {
        for (uint32_t x = 0; x < loc->width; ++x)
        {
            loc->mapInFile[y][x] = ' ';
            loc->map[y][x] = ' ';
        }
        loc->mapInFile[y][width] = '\0';
        loc->map[y][width] = '\0';
    }
}

void locationLoad(struct Location* loc, const char* txtFile)
{
    FILE* f;
    fopen_s(&f, txtFile, "r");

    if (f == NULL)
    {
        printf("File %s not found\n", txtFile);
    }

    uint32_t line = 0;
    char string[ (const uint32_t)loc->width];

    while (feof(f) == NULL)
    {
        fgets(string, loc->width, f);
        size_t length = strlen(string);
        if (string[length - 1] == '\n')
        {
            --length;
        }

        strncpy(loc->mapInFile[line], string, length);

        ++line;
        if (line == loc->height)
            break;
    }

    loc->map[loc->height - 1][loc->width - 1] = '\0';

    fclose(f);
}

void locationMapInit(struct Location* loc)
{
    for (uint32_t i = 0; i < loc->height; ++i)
    {
        strncpy(loc->map[i], loc->mapInFile[i], loc->width + 1);
    }

}

void locationPutObject(struct Location* loc, struct Object* obj)
{
    if ((obj->position.y < 0) || (obj->position.y >= loc->height) ||
        (obj->position.x < 0) || (obj->position.x >= loc->width))
    {
        return;
    }

    loc->map[obj->position.y][obj->position.x] = obj->iD;

}

void locationMapShow(struct Location* loc, short x, short y)
{
    COORD coord;


    for (short i = 0; i < loc->height; ++i)
    {
        coord.X = x;
        coord.Y = y + i;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        printf("%s", loc->map[i]);
    }

}

char locationMapGetSymbol(struct Location* loc, int x, int y)
{
    if ((y < 0) || (y >= loc->height) ||
        (x < 0) || (x >= loc->width))
    {
        return ' ';
    }

    return loc->map[y][x];
}

void locationDelete(struct Location* loc)
{
    for (uint32_t i = 0; i < loc->height; ++i)
    {
        free(loc->map[i]);
        free(loc->mapInFile[i]);
    }
    free(loc->map);
    free(loc->mapInFile);

    loc->width = 0;
    loc->height = 0;
}
