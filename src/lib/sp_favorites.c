#include "sp_favorites.h"

void sp_favorites(lv_obj_t *parent) {
    lv_obj_t *menu = lv_menu_create(parent);
    lv_obj_set_size(menu, LV_PCT(100), LV_PCT(100));

    lv_obj_t *back_btn = lv_menu_get_main_header_back_button(menu);
    lv_obj_t *back_button_label = lv_label_create(back_btn);
    lv_label_set_text(back_button_label, "    返回"); // left padding

    lv_obj_t *menu_main_page = lv_menu_page_create(menu, NULL);

    FavoriteList *favorite_list = get_favorite_list(); // TODO:
    for(int i = 0; i < favorite_list->count; i++) {
        Favorite item = favorite_list->list[i];
        char *content = item.content;
        char *substr = lv_malloc(300);
        lv_strncpy(substr, content, 299);

        lv_obj_t *content_page = lv_menu_page_create(menu, NULL);

        lv_obj_t *cont = lv_menu_cont_create(content_page);
        lv_obj_t *label = lv_label_create(cont);
        lv_label_set_text(label, content);
        lv_obj_set_size(label, LV_PCT(100), LV_SIZE_CONTENT);

        cont = lv_menu_cont_create(menu_main_page);
        label = lv_label_create(cont);
        lv_label_set_text_fmt(label, "%d. (%04d-%02d-%02d) %s...", i + 1, item.year, item.month, item.day, substr);
        lv_obj_set_size(label, LV_PCT(100), LV_SIZE_CONTENT);

        lv_menu_set_load_page_event(menu, cont, content_page);
    }

    lv_menu_set_page(menu, menu_main_page);
}
