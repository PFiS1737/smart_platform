#include "wifi.h"

wifi_ap_record_t *get_wifi_list(uint16_t *n) {
    wifi_scan_init();

    uint16_t ap_num;

    esp_wifi_scan_get_ap_num(&ap_num);
    if(ap_num == 0) {
        ESP_LOGI("wifi", "No AP found");
        return NULL;
    } else {
        ESP_LOGI("wifi", "Prefound %d APs", ap_num);
    }

    wifi_ap_record_t *ap_records = (wifi_ap_record_t *)malloc(sizeof(wifi_ap_record_t) * ap_num);
    if(!ap_records) {
        ESP_LOGE("wifi", "malloc error");
        return NULL;
    }

    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&ap_num, ap_records));

    ESP_LOGI("wifi", "Found %d APs", ap_num);

    *n = ap_num;

    return ap_records;
}

int connect_to_wifi(const char *ssid, const char *password) {
    // esp_wifi_disconnect();

    // ESP_LOGI("wifi", "GET: ssid: %s, password: %s", ssid, password);

    wifi_config_t wifi_config = {
        .sta =
            {
                .threshold.authmode = WIFI_AUTH_WPA2_PSK,
                .sae_pwe_h2e = WPA3_SAE_PWE_BOTH,
            },
    };

    uint8_t ssid_n[strlen(ssid)];
    uint8_t password_n[strlen(password)];
    for(uint8_t i = 0; *(ssid + i) != '\0'; i++) {
        ssid_n[i] = *(ssid + i);
    }
    for(uint8_t i = 0; *(password + i) != '\0'; i++) {
        password_n[i] = *(password + i);
    }

    memcpy(wifi_config.sta.ssid, ssid_n, sizeof(ssid_n));
    memcpy(wifi_config.sta.password, password_n, sizeof(password_n));

    esp_err_t err = esp_wifi_set_config(WIFI_IF_STA, &wifi_config);
    if(err != ESP_OK) {
        ESP_LOGE("wifi", "Failed to set wifi config");
        return 0;
    }

    err = esp_wifi_connect();
    if(err != ESP_OK) {
        ESP_LOGE("wifi", "Failed to connect to wifi");
        return 0;
    }

    return 1;
}
