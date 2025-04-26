#pragma once

#include "esp_log.h"
#include "lvgl.h"

typedef void (*typewriter_done_cb_t)(void *user_data);

void type_write_to_label(lv_obj_t *label, const char *text, typewriter_done_cb_t done_cb, void *user_data);
