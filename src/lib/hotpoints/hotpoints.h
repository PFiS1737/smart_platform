#include <stdio.h>
#include <stdlib.h>

// TODO: (api) 等后端接口确认后再设计数据格式
typedef struct Timeline
{
    int year;
    int month;
    int day;
    int hour;

    char *content;
} Timeline;

typedef struct TimelineList
{
    Timeline *list;
    int count;
} TimelineList;

typedef struct AnalysisPoint
{
    int percentage;

} AnalysisPoint;

typedef struct Analysis
{
    AnalysisPoint *list;
    int count;
} Analysis;

typedef struct
{
    int year;
    int month;
    int day;

    int stars; // max: 5

    char *title;

    Analysis *analysis;
    TimelineList *timeline;
} Hotpoint;

typedef struct
{
    Hotpoint *list;
    int count;
} HotpointList;

HotpointList *get_hotpoint_list();
