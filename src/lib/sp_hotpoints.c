#include "sp_hotpoints.h"
#include "core/lv_obj_pos.h"

void init_hotpoint_detail(lv_obj_t *parent);

void sp_hotpoints(lv_obj_t *parent) {
    lv_obj_t *menu = lv_menu_create(parent);
    lv_obj_set_size(menu, LV_PCT(100), LV_PCT(100));

    lv_obj_t *menu_main_page = lv_menu_page_create(menu, NULL);

    // TODO: (api) 等后端接口确认后动态生成
    for(int i = 0; i < 1; i++) {
        lv_obj_t *cont = lv_menu_cont_create(menu_main_page);
        lv_obj_t *label = lv_label_create(cont);
        lv_label_set_text(label, "1. 人工智能伦理 ★★★☆☆");
        lv_obj_set_size(label, LV_PCT(100), LV_SIZE_CONTENT);
        lv_obj_set_style_text_font(label, &lv_font_han_sans_20_3500, 0);

        lv_obj_t *content_page = lv_menu_page_create(menu, "人工智能伦理 ★★★☆☆");
        init_hotpoint_detail(content_page);

        lv_menu_set_load_page_event(menu, cont, content_page);
    }

    lv_menu_set_page(menu, menu_main_page);
}

void init_detail_analysis(lv_obj_t *parent);
void init_detail_content(lv_obj_t *parent);
void init_hotpoint_detail(lv_obj_t *parent) {
    lv_obj_t *tabview = lv_tabview_create(parent, LV_DIR_LEFT, 80);

    init_detail_analysis(lv_tabview_add_tab(tabview, "分析"));
    init_detail_content(lv_tabview_add_tab(tabview, "背景"));
}

static void draw_event_cb(lv_event_t *e);
void init_detail_analysis(lv_obj_t *parent) {
    lv_obj_t *wrapper = lv_obj_create(parent);
    lv_obj_set_size(wrapper, LV_PCT(100), LV_PCT(100));
    lv_obj_set_layout(wrapper, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(wrapper, LV_FLEX_FLOW_COLUMN);

    lv_obj_t *label = lv_label_create(wrapper);
    lv_label_set_text(label, "热度趋势 (近 7 天)");

    lv_obj_t *chart = lv_chart_create(wrapper);
    lv_obj_set_size(chart, LV_PCT(100), 200);
    lv_chart_set_type(chart, LV_CHART_TYPE_LINE);
    lv_chart_set_point_count(chart, 7);
    lv_chart_set_div_line_count(chart, 5, 7);

    lv_chart_set_axis_tick(chart, LV_CHART_AXIS_PRIMARY_X, 5, 5, 7, 1, true, 30);
    // lv_chart_set_axis_tick(chart, LV_CHART_AXIS_PRIMARY_Y, 20, 4, 5, 5, true, 50);

    lv_obj_add_event_cb(chart, draw_event_cb, LV_EVENT_DRAW_PART_BEGIN, NULL);

    lv_chart_series_t *ser = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_GREEN), LV_CHART_AXIS_PRIMARY_Y);

    for(uint32_t i = 0; i < 7; i++) {
        lv_chart_set_next_value(chart, ser, (int32_t)lv_rand(10, 90));
    }
}

void init_detail_content(lv_obj_t *parent) {
    lv_obj_t *label = lv_label_create(parent);
    lv_obj_set_size(label, LV_PCT(100), LV_SIZE_CONTENT);
    lv_label_set_text(
        label,
        "非常长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长"
        "长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长"
        "长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长"
        "长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长"
        "长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长"
        "长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长"
        "长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长"
        "长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长"
        "长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长"
        "长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长"
        "长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长"
        "长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长"
        "长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长"
        "长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长"
        "长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长长"
        "长长长长长长长长长长长长长长长长长长长长长长长长长长长长长的测试文本");
}

static void draw_event_cb(lv_event_t *e) {
    lv_obj_draw_part_dsc_t *dsc = lv_event_get_draw_part_dsc(e);
    if(!lv_obj_draw_part_check_type(dsc, &lv_chart_class, LV_CHART_DRAW_PART_TICK_LABEL))
        return;

    if(dsc->id == LV_CHART_AXIS_PRIMARY_X && dsc->text) {
        const char *src[] = {"1", "2", "3", "4", "5", "6", "7 (今天)"};
        lv_snprintf(dsc->text, dsc->text_length, "%s", src[dsc->value]);
    }
}
