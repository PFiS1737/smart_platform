#include "loves.h"

int compare_love(const void *a, const void *b);

// TODO: (backend) 这里应该是从后端获取数据
LoveList *get_love_list() {
    int count = 10;
    Love *loves = malloc(sizeof(Love) * count);
    for(int i = 0; i < count; i++) {
        loves[i].year = 2025;
        loves[i].month = 4;
        loves[i].day = i + 1;
        loves[i].content = malloc(2000);
        snprintf(
            loves[i].content, 2000,
            "This is the content of love %d: "
            "非常非常长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长"
            "长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长"
            "长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长"
            "长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长"
            "长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长"
            "长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长"
            "长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长"
            "长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长"
            "长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长"
            "长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长"
            "长长长长长长长长长长长长长长长长长长长长长长长长长长长长长 结束",
            i + 1);
    }
    qsort(loves, count, sizeof(Love), compare_love);

    LoveList *list = malloc(sizeof(LoveList));
    list->list = loves;
    list->count = count;

    return list;
}

int compare_love(const void *a, const void *b) {
    const Love *love_a = (const Love *)a;
    const Love *love_b = (const Love *)b;

    if(love_a->year != love_b->year) {
        return love_b->year - love_a->year;
    }
    if(love_a->month != love_b->month) {
        return love_b->month - love_a->month;
    }
    return love_b->day - love_a->day;
}
