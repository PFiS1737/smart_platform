#include "sp_history.h"

HistoryList *history_list;

void sp_history(lv_obj_t *parent) {
    lv_obj_t *menu = lv_menu_create(parent);
    lv_obj_set_size(menu, LV_PCT(100), LV_PCT(100));

    lv_obj_t *menu_main_page = lv_menu_page_create(menu, NULL);

    history_list = get_history_list();
    for(int i = 0; i < history_list->count; i++) {
        lv_obj_t *cont = lv_menu_cont_create(menu_main_page);
        lv_obj_t *label = lv_label_create(cont);

        lv_label_set_text_fmt(label, "%s  %s", i == 0 ? "（最新）" : "", history_list->list[i].title);
        lv_obj_set_size(label, LV_PCT(100), LV_SIZE_CONTENT);
        lv_obj_set_style_text_font(label, &lv_font_han_sans_20_3500, 0);

        lv_obj_t *content_page = lv_menu_page_create(menu, history_list->list[i].title);
        lv_obj_t *content_label = lv_label_create(content_page);
        lv_obj_set_size(content_label, LV_PCT(100), LV_SIZE_CONTENT);
        lv_label_set_text(content_label, history_list->list[i].content);

        lv_menu_set_load_page_event(menu, cont, content_page);
    }

    lv_menu_set_page(menu, menu_main_page);
}
