#include "sp_hotpoints.h"

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
void init_detail_timeline(lv_obj_t *parent);
void init_hotpoint_detail(lv_obj_t *parent) {
    lv_obj_t *tabview = lv_tabview_create(parent);
    lv_tabview_set_tab_bar_position(tabview, LV_DIR_LEFT);
    lv_tabview_set_tab_bar_size(tabview, 80);

    init_detail_analysis(lv_tabview_add_tab(tabview, "分析"));
    init_detail_timeline(lv_tabview_add_tab(tabview, "背景"));
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
    lv_obj_set_width(chart, LV_PCT(100));
    lv_obj_set_flex_grow(chart, 1);
    lv_chart_set_type(chart, LV_CHART_TYPE_LINE);
    lv_chart_set_point_count(chart, 7);
    lv_chart_set_div_line_count(chart, 5, 7);

    lv_obj_add_event_cb(chart, draw_event_cb, LV_EVENT_DRAW_POST_END, NULL);
    lv_obj_add_flag(chart, LV_OBJ_FLAG_SEND_DRAW_TASK_EVENTS);

    lv_obj_t *scale_x = lv_scale_create(wrapper);
    lv_obj_set_size(scale_x, LV_PCT(100), 25);
    lv_obj_set_style_pad_hor(scale_x, lv_chart_get_first_point_center_offset(chart), 0);
    lv_scale_set_mode(scale_x, LV_SCALE_MODE_HORIZONTAL_BOTTOM);
    lv_scale_set_total_tick_count(scale_x, 7);
    lv_scale_set_major_tick_every(scale_x, 1);
    static const char *src_x[] = {"1", "2", "3", "4", "5", "6", "7 (今天)", NULL};
    lv_scale_set_text_src(scale_x, src_x);

    lv_chart_series_t *ser = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_GREEN), LV_CHART_AXIS_PRIMARY_Y);

    for(uint32_t i = 0; i < 7; i++) {
        lv_chart_set_next_value(chart, ser, (int32_t)lv_rand(10, 90));
    }
}

void init_detail_timeline(lv_obj_t *parent) {
    lv_obj_t *menu = lv_menu_create(parent);
    lv_obj_set_size(menu, LV_PCT(100), LV_PCT(100));

    lv_obj_t *menu_main_page = lv_menu_page_create(menu, NULL);

    char *demos[] = {
        "事件11 这些是临时占位文本",
        "事件10 仅提供演示",
        "事件9 注意要考虑到文本很长",
        "事件8 比如这"
        "样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样"
        "样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样"
        "样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样"
        "样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样"
        "样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样"
        "样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样样",
        "事件7 或非常短 比如",
        "6",
        "事件5 test",
        "事件4 test test",
        "事件3 test test test",
        "事件2 test test test test",
        "事件1 test test test test test"};

    for(int i = 0; i < sizeof(demos) / sizeof(demos[0]); i++) {
        lv_obj_t *label = lv_label_create(lv_menu_cont_create(menu_main_page));
        lv_obj_set_size(label, LV_PCT(100), LV_SIZE_CONTENT);
        lv_label_set_text(label, demos[i]);
    }

    lv_menu_set_page(menu, menu_main_page);
}

static void draw_event_cb(lv_event_t *e) {
    lv_obj_t *chart = lv_event_get_target_obj(e);
    lv_chart_series_t *ser = lv_chart_get_series_next(chart, NULL);

    lv_point_t p;
    lv_chart_get_point_pos_by_id(chart, ser, 4, &p); // TODO: '4' as demo

    lv_layer_t *layer = lv_event_get_layer(e);

    char *text = "政策发布";
    uint32_t text_width = lv_text_get_width(text, strlen(text), &lv_font_han_sans_16_3500, 0);

    lv_draw_rect_dsc_t draw_rect_dsc;
    lv_draw_rect_dsc_init(&draw_rect_dsc);
    draw_rect_dsc.bg_color = lv_color_black();
    draw_rect_dsc.bg_opa = LV_OPA_50;
    draw_rect_dsc.radius = 3;

    lv_area_t chart_obj_coords;
    lv_obj_get_coords(chart, &chart_obj_coords);
    lv_area_t rect_area;
    rect_area.x1 = chart_obj_coords.x1 + p.x - text_width / 2 - 4;
    rect_area.x2 = chart_obj_coords.x1 + p.x + text_width / 2 + 4;
    rect_area.y1 = chart_obj_coords.y1 + p.y - 40;
    rect_area.y2 = chart_obj_coords.y1 + p.y - 10;
    lv_draw_rect(layer, &draw_rect_dsc, &rect_area);

    lv_draw_label_dsc_t draw_label_dsc;
    lv_draw_label_dsc_init(&draw_label_dsc);
    draw_label_dsc.color = lv_color_white();
    draw_label_dsc.text = text;
    draw_label_dsc.font = &lv_font_han_sans_16_3500;
    draw_label_dsc.text_local = 1;
    draw_label_dsc.align = LV_TEXT_ALIGN_CENTER;
    lv_area_t label_area = rect_area;
    lv_area_set_height(&label_area, lv_font_get_line_height(draw_label_dsc.font) + 4);
    lv_area_align(&rect_area, &label_area, LV_ALIGN_CENTER, 0, 0);
    lv_draw_label(layer, &draw_label_dsc, &label_area);
}
