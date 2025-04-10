#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int year;
    int month;
    int day;
    char *content;
} Favorite;

typedef struct
{
    Favorite *list;
    int count;
} FavoriteList;

FavoriteList *get_favorite_list();
