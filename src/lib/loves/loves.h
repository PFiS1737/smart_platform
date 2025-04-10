#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int year;
    int month;
    int day;
    char *content;
} Love;

typedef struct
{
    Love *list;
    int count;
} LoveList;

LoveList *get_love_list();
