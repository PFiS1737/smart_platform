#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int year;
    int month;
    int day;
    char *content;
} Love;

Love *get_love_list(int *count);
