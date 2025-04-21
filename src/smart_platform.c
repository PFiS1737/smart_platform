#include "smart_platform.h"

void smart_platform(void) {
    lv_theme_t *theme = lv_theme_default_init(NULL, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                              false, &lv_font_han_sans_16_3500);
    lv_disp_set_theme(lv_disp_get_default(), theme);

    lv_obj_t *tabview = lv_tabview_create(lv_scr_act(), LV_DIR_BOTTOM, 50);
    lv_obj_set_style_text_font(tabview, &lv_font_han_sans_16_3500, 0);

    lv_obj_t *tab1_hotpoints = lv_tabview_add_tab(tabview, "热点");
    lv_obj_t *tab2_writing = lv_tabview_add_tab(tabview, "作文");
    lv_obj_t *tab3_history = lv_tabview_add_tab(tabview, "历史");
    lv_obj_t *tab4_settings = lv_tabview_add_tab(tabview, "设置");

    sp_hotpoints(tab1_hotpoints);
    sp_writing(tab2_writing);
    sp_history(tab3_history);
    sp_settings(tab4_settings);
}
