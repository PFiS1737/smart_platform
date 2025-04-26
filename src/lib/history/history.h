#pragma once

#include "lvgl.h"

typedef struct History
{
    char *title;
    char *content;
} History;

typedef struct HistoryList
{
    History *list;
    int count;
} HistoryList;

HistoryList *get_history_list(void);
