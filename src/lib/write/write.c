#include "write.h"

typedef struct
{
    lv_obj_t *label;
    const char *full_text;
    int len;
    int index;
    char *buffer;
    typewriter_done_cb_t done_cb;
    void *cb_user_data;
} type_writer_ctx_t;

static void type_writer_cb(lv_timer_t *timer) {
    type_writer_ctx_t *ctx = (type_writer_ctx_t *)timer->user_data;

    int step = lv_rand(16, 28);
    // int step = lv_rand(200, 400);
    ctx->index += step;
    if(ctx->index > ctx->len) {
        ctx->index = ctx->len;
    }

    strncpy(ctx->buffer, ctx->full_text, ctx->index);
    ctx->buffer[ctx->index] = '\0';
    lv_label_set_text(ctx->label, ctx->buffer);

    if(ctx->index >= ctx->len) {
        lv_timer_del(timer);

        if(ctx->done_cb) {
            ctx->done_cb(ctx->cb_user_data);
        }

        free(ctx->buffer);
        free(ctx);

        ESP_LOGI("typewriter", "Done");
    }
}

void type_write_to_label(lv_obj_t *label, const char *text, typewriter_done_cb_t done_cb, void *user_data) {
    type_writer_ctx_t *ctx = malloc(sizeof(type_writer_ctx_t));
    ctx->label = label;
    ctx->full_text = text;
    ctx->len = strlen(text);
    ctx->index = 0;
    ctx->buffer = malloc(ctx->len + 1);
    ctx->done_cb = done_cb;
    ctx->cb_user_data = user_data;

    lv_timer_create(type_writer_cb, 1000, ctx);
}
