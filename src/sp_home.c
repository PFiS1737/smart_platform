#include "sp_home.h"

#include "lv_font_han_sans_20_3500.c"

static lv_style_t style_card;

void init_style(void);
void init_textarea(lv_obj_t *parent);
void init_material_card(lv_obj_t *parent);
void init_notification_card(lv_obj_t *parent);
void init_hotpoints_card(lv_obj_t *parent);
void init_quick_entrance_card(lv_obj_t *parent);

void sp_home(lv_obj_t *parent) {
    lv_obj_set_layout(parent, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(parent, LV_FLEX_FLOW_COLUMN);

    init_style();

    init_textarea(parent);
    init_material_card(parent);
    init_notification_card(parent);
    init_hotpoints_card(parent);
    init_quick_entrance_card(parent);
}

void init_style(void) {
    lv_style_init(&style_card);
    lv_style_set_radius(&style_card, 10);
    lv_style_set_pad_all(&style_card, 10);
}

// TODO: 这里应该是只把 home 里的输入栏作为占位符
//       点击后，转跳到一个专门显示输入栏和搜索结果的页面
//
// TODO: (backend) 这里如果要做`关键词联想`，需要后端提供接口
static void ta_event_cb(lv_event_t *e);
void init_textarea(lv_obj_t *parent) {
    lv_obj_t *ta = lv_textarea_create(parent);
    lv_textarea_set_one_line(ta, true);
    lv_textarea_set_placeholder_text(ta, "请输入内容");
    lv_obj_set_size(ta, LV_PCT(100), 50);

    lv_obj_t *pinyin_ime = lv_ime_pinyin_create(lv_screen_active());

    lv_obj_t *kb = lv_keyboard_create(lv_screen_active());
    lv_ime_pinyin_set_keyboard(pinyin_ime, kb);
    lv_keyboard_set_textarea(kb, ta);
    lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_event_cb(ta, ta_event_cb, LV_EVENT_ALL, pinyin_ime);

    lv_obj_t *cand_panel = lv_ime_pinyin_get_cand_panel(pinyin_ime);
    lv_obj_set_size(cand_panel, LV_PCT(100), LV_PCT(10));
    lv_obj_align_to(cand_panel, kb, LV_ALIGN_OUT_TOP_MID, 0, 0);
    lv_obj_set_style_bg_opa(cand_panel, LV_OPA_100, 0);
}

void init_material_card(lv_obj_t *parent) {
    lv_obj_t *material = lv_obj_create(parent);
    lv_obj_add_style(material, &style_card, 0);
    lv_obj_set_size(material, LV_PCT(100), LV_SIZE_CONTENT);

    lv_obj_t *label = lv_label_create(material);
    lv_label_set_text(label, "作文素材");
    lv_obj_set_style_text_font(label, &lv_font_han_sans_20_3500, 0);

    // TODO:  下面是轮换播放 3 条收藏的作文素材
}

void init_notification_card(lv_obj_t *parent) {
    lv_obj_t *notification = lv_obj_create(parent);
    lv_obj_add_style(notification, &style_card, 0);
    lv_obj_set_size(notification, LV_PCT(100), LV_SIZE_CONTENT);

    lv_obj_t *label = lv_label_create(notification);
    lv_label_set_text(label, "系统通知");
    lv_obj_set_style_text_font(label, &lv_font_han_sans_20_3500, 0);

    // INFO: `今日新增热点` 删了，前端逻辑不好写，后端也难弄
    //
    // TODO: - WiFi 状态
    //       - 蓝牙状态
    //       - 存储空间警告
    //
    // TODO: 点击进入系统详情
}

void init_hotpoints_card(lv_obj_t *parent) {
    lv_obj_t *hotpoints = lv_obj_create(parent);
    lv_obj_add_style(hotpoints, &style_card, 0);
    lv_obj_set_size(hotpoints, LV_PCT(100), LV_SIZE_CONTENT);

    lv_obj_t *label = lv_label_create(hotpoints);
    lv_label_set_text(label, "热点卡片");
    lv_obj_set_style_text_font(label, &lv_font_han_sans_20_3500, 0);

    // TODO: - 一个最新讨论，这个可以再嵌套一个带高亮色的卡片
    //       - 几条热点
}

static void btnm_event_cb(lv_event_t *e);
static const char *btnm_map[];
void init_quick_entrance_card(lv_obj_t *parent) {
    lv_obj_t *entrance = lv_buttonmatrix_create(parent);
    lv_obj_add_style(entrance, &style_card, 0);
    lv_obj_set_size(entrance, LV_PCT(100), 80);
    lv_obj_set_style_text_font(entrance, &lv_font_han_sans_20_3500, 0);

    lv_buttonmatrix_set_map(entrance, btnm_map);
    lv_buttonmatrix_set_button_width(entrance, 0, LV_PCT(100) / 2 - 5);
    lv_buttonmatrix_set_button_width(entrance, 1, LV_PCT(100) / 2 - 5);

    lv_obj_add_event_cb(entrance, btnm_event_cb, LV_EVENT_ALL, NULL);
}

static void ta_event_cb(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *ta = lv_event_get_target(e);
    lv_obj_t *pinyin_ime = lv_event_get_user_data(e);
    lv_obj_t *kb = lv_ime_pinyin_get_kb(pinyin_ime);
    lv_obj_t *cand_panel = lv_ime_pinyin_get_cand_panel(pinyin_ime);

    switch(code) {
        case LV_EVENT_FOCUSED:
            lv_keyboard_set_textarea(kb, ta);
            lv_obj_remove_flag(kb, LV_OBJ_FLAG_HIDDEN);
            break;
        case LV_EVENT_DEFOCUSED:
            lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(cand_panel, LV_OBJ_FLAG_HIDDEN);
            lv_obj_remove_state(ta, LV_STATE_FOCUSED);
            lv_indev_reset(NULL, ta);
            break;
        default: break;
    }
}

static void btnm_event_cb(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *btnm = lv_event_get_target_obj(e);

    if(code == LV_EVENT_VALUE_CHANGED) {
        uint32_t id = lv_buttonmatrix_get_selected_button(btnm);
        const char *txt = lv_buttonmatrix_get_button_text(btnm, id);

        // TODO: 这里应该是跳转到对应的页面

        LV_UNUSED(txt);
        LV_LOG("%s was pressed\n", txt);
    }
}

static const char *btnm_map[] = {"生成作文", "历史记录", NULL};
