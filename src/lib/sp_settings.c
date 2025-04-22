#include "sp_settings.h"

lv_obj_t *wifi_status_label;

void init_wifi_page(lv_obj_t *parent);
void sp_settings(lv_obj_t *parent) {
    lv_obj_t *menu = lv_menu_create(parent);
    lv_obj_set_size(menu, LV_PCT(100), LV_PCT(100));

    lv_obj_t *cont;

    lv_obj_t *wifi_page = lv_menu_page_create(menu, NULL);

    cont = lv_menu_cont_create(wifi_page);
    init_wifi_page(cont);

    lv_obj_t *main_page = lv_menu_page_create(menu, NULL);

    cont = lv_menu_cont_create(main_page);

    wifi_status_label = lv_label_create(cont);
    lv_label_set_text(wifi_status_label, "WiFi 设置");
    lv_obj_set_style_text_font(wifi_status_label, &lv_font_han_sans_20_3500, 0);
    lv_menu_set_load_page_event(menu, cont, wifi_page);

    lv_menu_set_page(menu, main_page);
}

static lv_obj_t *ssid_btn_pool[10];
static lv_obj_t *ssid_label_pool[10];
static const char *ssid_list[10];

void wifi_btn_cb(lv_event_t *e);
void init_wifi_page(lv_obj_t *parent) {
    lv_obj_set_layout(parent, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(parent, LV_FLEX_FLOW_COLUMN);

    uint16_t ap_num = 0;
    wifi_ap_record_t *wifi_list = get_wifi_list(&ap_num);

    if(!wifi_list)
        return;

    for(int i = 0; i < (ap_num > 10 ? 10 : ap_num); i++) {
        ssid_btn_pool[i] = lv_btn_create(parent);
        lv_obj_set_size(ssid_btn_pool[i], LV_PCT(100), LV_SIZE_CONTENT);
        ssid_label_pool[i] = lv_label_create(ssid_btn_pool[i]);
        lv_obj_set_size(ssid_label_pool[i], LV_PCT(100), LV_SIZE_CONTENT);

        const char *ssid = (const char *)wifi_list[i].ssid;
        ESP_LOGI("wifi", "wifi_list[%d].ssid: %s", i, ssid);

        lv_label_set_text(ssid_label_pool[i], ssid);
        lv_obj_set_style_text_font(ssid_label_pool[i], &lv_font_han_sans_20_3500, 0);

        ssid_list[i] = ssid;

        lv_obj_add_event_cb(ssid_btn_pool[i], wifi_btn_cb, LV_EVENT_CLICKED, &i);
    }
}

static void wifi_cancel_cb(lv_event_t *e) {
    lv_obj_t *win = (lv_obj_t *)lv_event_get_user_data(e);
    lv_obj_del(win);
}

static lv_obj_t *kb;

static void ta_event_cb(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *ta = lv_event_get_target(e);

    if(code == LV_EVENT_FOCUSED) {
        lv_keyboard_set_textarea(kb, ta);
        lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
    } else if(code == LV_EVENT_DEFOCUSED) {
        lv_keyboard_set_textarea(kb, NULL);
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    } else if(code == LV_EVENT_READY) {
        const char *ssid = ssid_list[*(int *)e->user_data];
        const char *password = lv_textarea_get_text(ta);

        ESP_LOGI("wifi", "GET: ssid: %s", ssid);
        ESP_LOGI("wifi", "GET: password: %s", password);

        if(connect_to_wifi(ssid, password)) {
            lv_obj_t *mbox = lv_msgbox_create(NULL, "", "连接成功", NULL, true);
            lv_obj_set_style_text_font(mbox, &lv_font_han_sans_20_3500, 0);
            lv_label_set_text_fmt(wifi_status_label, "WiFi 连接成功: %s", ssid);
            lv_obj_center(mbox);
        } else {
            lv_obj_t *mbox = lv_msgbox_create(NULL, "", "连接失败", NULL, true);
            lv_obj_set_style_text_font(mbox, &lv_font_han_sans_20_3500, 0);
            lv_obj_center(mbox);
        }

        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
}

void wifi_btn_cb(lv_event_t *e) {
    lv_obj_t *win = lv_win_create(lv_scr_act(), 60);
    lv_win_add_title(win, "请输入密码");
    lv_obj_set_style_text_font(win, &lv_font_han_sans_20_3500, 0);

    lv_obj_t *btn = lv_win_add_btn(win, LV_SYMBOL_CLOSE, 100);
    lv_obj_add_event_cb(btn, wifi_cancel_cb, LV_EVENT_CLICKED, win);

    lv_obj_t *cont = lv_win_get_content(win);

    kb = lv_keyboard_create(lv_scr_act());
    lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);

    lv_obj_t *ta = lv_textarea_create(cont);
    lv_textarea_set_one_line(ta, true);
    lv_obj_set_size(ta, LV_PCT(100), 150);
    lv_obj_add_event_cb(ta, ta_event_cb, LV_EVENT_ALL, (int *)e->user_data);

    lv_keyboard_set_textarea(kb, ta);
}
