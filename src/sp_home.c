#include "sp_home.h"

void init_textarea(lv_obj_t *parent);
void init_material(lv_obj_t *parent);

void sp_home(lv_obj_t *parent) {
    init_textarea(parent);
}

// TODO: 这里应该是只把 home 里的输入栏作为占位符
//       点击后，转跳到一个专门显示输入栏和搜索结果的页面
//
// TODO: (backend) 这里如果要做`关键词联想`，需要后端提供接口
void ta_event_cb(lv_event_t *e);
void init_textarea(lv_obj_t *parent) {
    lv_obj_t *pinyin_ime = lv_ime_pinyin_create(lv_screen_active());

    lv_obj_t *ta = lv_textarea_create(parent);
    lv_textarea_set_one_line(ta, true);
    lv_textarea_set_placeholder_text(ta, "请输入内容");
    lv_obj_set_size(ta, LV_PCT(100), 50);
    lv_obj_align(ta, LV_ALIGN_TOP_LEFT, 0, 0);

    lv_obj_t *kb = lv_keyboard_create(lv_screen_active());
    lv_ime_pinyin_set_keyboard(pinyin_ime, kb);
    lv_keyboard_set_textarea(kb, ta);
    lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_event_cb(ta, ta_event_cb, LV_EVENT_ALL, pinyin_ime);
}

void ta_event_cb(lv_event_t *e) {
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
