#include "sp_history.h"

void sp_history(lv_obj_t *parent) {
    lv_obj_t *label = lv_label_create(parent);
    lv_label_set_text(label, "This is the history tab");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
}
