#include "sp_home.h"

void sp_home(lv_obj_t *parent) {
    lv_obj_t *label = lv_label_create(parent);
    lv_label_set_text(label, "This is the home tab");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
}
