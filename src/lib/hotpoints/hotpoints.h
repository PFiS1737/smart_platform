#include <stdio.h>
#include <stdlib.h>

#include "lvgl.h"

typedef struct Analysis
{
    int percentage;
} Analysis;

typedef struct
{
    int year;
    int month;
    int day;

    int stars; // max: 5

    char *title;
    char *content;

    Analysis *analysis[7];
} Hotpoint;

typedef struct
{
    Hotpoint *list;
    int count;
} HotpointList;

HotpointList *get_hotpoint_list(void);
