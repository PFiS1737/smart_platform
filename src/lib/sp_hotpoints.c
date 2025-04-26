#include "sp_hotpoints.h"
#include "core/lv_obj.h"
#include "misc/lv_timer.h"

extern lv_obj_t *tabview;

static HotpointList *hotpoint_list;

lv_obj_t *init_btn;

static void init_hotpoint_detail(lv_obj_t *parent, int idx);
static void init_btn_cb(lv_event_t *e);
void sp_hotpoints(lv_obj_t *parent) {

    init_btn = lv_btn_create(parent);
    lv_obj_center(init_btn);
    lv_obj_t *label = lv_label_create(init_btn);
    lv_label_set_text(label, "点击获取热点");
    lv_obj_add_event_cb(init_btn, init_btn_cb, LV_EVENT_CLICKED, parent);
}

static void init_btn_timer_cb(lv_timer_t *timer);
static void init_btn_cb(lv_event_t *e) {
    lv_obj_t *parent = lv_event_get_user_data(e);

    lv_obj_t *btn_label = lv_obj_get_child(init_btn, 0);
    lv_label_set_text(btn_label, "等待服务器响应...");

    lv_timer_create(init_btn_timer_cb, 5000, parent);
}

static void init_btn_timer_cb(lv_timer_t *timer) {
    lv_obj_del(init_btn);

    lv_obj_t *menu = lv_menu_create((lv_obj_t *)timer->user_data);
    lv_obj_set_size(menu, LV_PCT(100), LV_PCT(100));

    lv_obj_t *menu_main_page = lv_menu_page_create(menu, NULL);

    hotpoint_list = get_hotpoint_list();
    for(int i = 0; i < hotpoint_list->count; i++) {
        lv_obj_t *cont = lv_menu_cont_create(menu_main_page);
        lv_obj_t *label = lv_label_create(cont);

        char *title = malloc(150);
        strcpy(title, hotpoint_list->list[i].title);
        strcat(title, "  ");
        for(int j = 0; j < hotpoint_list->list[i].stars; j++) {
            strcat(title, "★");
        }
        for(int j = hotpoint_list->list[i].stars; j < 5; j++) {
            strcat(title, "☆");
        }

        lv_label_set_text_fmt(label, "%d. %s", i + 1, title);
        lv_obj_set_size(label, LV_PCT(100), LV_SIZE_CONTENT);
        lv_obj_set_style_text_font(label, &lv_font_han_sans_20_3500, 0);

        lv_obj_t *content_page = lv_menu_page_create(menu, title);
        init_hotpoint_detail(content_page, i);

        lv_menu_set_load_page_event(menu, cont, content_page);
    }

    lv_menu_set_page(menu, menu_main_page);

    lv_timer_del(timer);
}

void init_detail_analysis(lv_obj_t *parent, int idx);
void init_detail_content(lv_obj_t *parent, int idx);
void init_hotpoint_detail(lv_obj_t *parent, int idx) {
    lv_obj_t *tabview = lv_tabview_create(parent, LV_DIR_LEFT, 80);

    init_detail_analysis(lv_tabview_add_tab(tabview, "分析"), idx);
    init_detail_content(lv_tabview_add_tab(tabview, "内容"), idx);
}

static void draw_event_cb(lv_event_t *e);
void init_detail_analysis(lv_obj_t *parent, int idx) {
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
        lv_chart_set_next_value(chart, ser, idx == 0 ? (int32_t)lv_rand(75, 95) : (int32_t)lv_rand(60, 85));
    }
}

static void goto_writing_cb(lv_event_t *e);
void init_detail_content(lv_obj_t *parent, int idx) {
    lv_obj_set_layout(parent, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(parent, LV_FLEX_FLOW_COLUMN);

    lv_obj_t *label = lv_label_create(parent);
    lv_obj_set_size(label, LV_PCT(100), LV_SIZE_CONTENT);
    char *text = (char *)malloc(2000);
    strcpy(text, "        ");
    strcat(text, hotpoint_list->list[idx].content);
    lv_label_set_text(label, text);

    lv_obj_t *btn = lv_btn_create(parent);
    lv_obj_set_size(btn, LV_PCT(100), LV_SIZE_CONTENT);
    lv_obj_t *btn_label = lv_label_create(btn);
    lv_label_set_text(btn_label, "生成作文");
    lv_obj_add_event_cb(btn, goto_writing_cb, LV_EVENT_CLICKED, NULL);
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

static void goto_writing_cb(lv_event_t *e) {
    lv_tabview_set_act(tabview, 1, LV_ANIM_ON);
}
