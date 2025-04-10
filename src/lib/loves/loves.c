#include "loves.h"

int compare_love(const void *a, const void *b);

// TODO: (backend) 这里应该是从后端获取数据
Love *get_love_list(int *count) {
    Love *love_list = malloc(sizeof(Love) * 10);
    for(int i = 0; i < 10; i++) {
        love_list[i].year = 2025;
        love_list[i].month = 4;
        love_list[i].day = i + 1;
        love_list[i].content = malloc(2000);
        snprintf(
            love_list[i].content, 2000,
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
    *count = 10;
    qsort(love_list, *count, sizeof(Love), compare_love);
    return love_list;
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
