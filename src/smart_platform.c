#include "smart_platform.h"

#include "lv_font_han_sans_16_3500.c"

void smart_platform(void) {
    lv_theme_t *theme = lv_theme_default_init(NULL, lv_palette_main(LV_PALETTE_RED), lv_palette_main(LV_PALETTE_RED),
                                              false, &lv_font_han_sans_16_3500);
    lv_display_set_theme(NULL, theme);

    lv_obj_t *tabview = lv_tabview_create(lv_screen_active());
    lv_tabview_set_tab_bar_position(tabview, LV_DIR_BOTTOM);

    lv_obj_t *tab1_home = lv_tabview_add_tab(tabview, "首页");
    lv_obj_t *tab2_hotpoints = lv_tabview_add_tab(tabview, "热点");
    lv_obj_t *tab3_write = lv_tabview_add_tab(tabview, "作文");
    lv_obj_t *tab4_mine = lv_tabview_add_tab(tabview, "我的");

    sp_home(tab1_home);
    sp_hotpoints(tab2_hotpoints);
    sp_write(tab3_write);
    sp_mine(tab4_mine);
}
