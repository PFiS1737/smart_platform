#pragma once

#include "esp_wifi.h"
#include "lvgl_wifi_connect.h"

wifi_ap_record_t *get_wifi_list(uint16_t *ap_num);
int connect_to_wifi(const char *ssid, const char *password);
