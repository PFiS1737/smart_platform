#include "favorites.h"

int compare(const void *a, const void *b);

// TODO: (backend) 这里应该是从后端获取数据
FavoriteList *get_favorite_list() {
    int count = 10;
    Favorite *favorites = malloc(sizeof(Favorite) * count);
    for(int i = 0; i < count; i++) {
        favorites[i].year = 2025;
        favorites[i].month = 4;
        favorites[i].day = i + 1;
        favorites[i].content = malloc(2000);
        snprintf(
            favorites[i].content, 2000,
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
    qsort(favorites, count, sizeof(Favorite), compare);

    FavoriteList *list = malloc(sizeof(FavoriteList));
    list->list = favorites;
    list->count = count;

    return list;
}

int compare(const void *a, const void *b) {
    const Favorite *love_a = (const Favorite *)a;
    const Favorite *love_b = (const Favorite *)b;

    if(love_a->year != love_b->year) {
        return love_b->year - love_a->year;
    }
    if(love_a->month != love_b->month) {
        return love_b->month - love_a->month;
    }
    return love_b->day - love_a->day;
}
