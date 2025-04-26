#include "sp_writing.h"
#include "misc/lv_timer.h"

extern lv_obj_t *tabview;

lv_obj_t *begin_btn = NULL;
lv_obj_t *title = NULL;
lv_obj_t *content = NULL;
lv_obj_t *footer = NULL;

static void begin_writing_cb(lv_event_t *e);
void sp_writing(lv_obj_t *parent) {
    lv_obj_set_layout(parent, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(parent, LV_FLEX_FLOW_COLUMN);

    title = lv_label_create(parent);
    lv_label_set_text(title, "作文：习近平今年首次出访重要成果");
    lv_obj_set_style_text_font(title, &lv_font_han_sans_20_3500, 0);
    lv_obj_set_size(title, LV_SIZE_CONTENT, LV_SIZE_CONTENT);

    lv_obj_t *sp = lv_obj_create(parent);
    lv_obj_set_size(sp, LV_PCT(100), 1);
    lv_obj_set_style_bg_color(sp, lv_color_black(), 0);

    begin_btn = lv_btn_create(parent);
    lv_obj_t *btn_label = lv_label_create(begin_btn);
    lv_label_set_text(btn_label, "开始写作");
    lv_obj_add_event_cb(begin_btn, begin_writing_cb, LV_EVENT_CLICKED, parent);
}

static const char *res1;
static const char *res2;

typedef struct
{
    lv_obj_t *parent;
    lv_event_cb_t rewrite_btn_cb;
} write_done_cb_ctx_t;
static void writer_done_cb(void *user_data);

static void rewrite_btn_cb_1(lv_event_t *e);
static void rewrite_btn_cb_2(lv_event_t *e);
static void rewrite_btn_cb_3(lv_event_t *e);

static void begin_writing_timer_cb(lv_timer_t *timer) {
    lv_obj_del(begin_btn);

    lv_label_set_text(title, "正在写作：论国际合作与多边关系的重要性...");

    lv_obj_t *parent = timer->user_data;
    content = lv_label_create(parent);
    lv_obj_set_size(content, LV_PCT(100), LV_SIZE_CONTENT);
    lv_label_set_text(content, "");

    write_done_cb_ctx_t *ctx = malloc(sizeof(write_done_cb_ctx_t));

    ctx->parent = parent;
    ctx->rewrite_btn_cb = rewrite_btn_cb_1;

    type_write_to_label(content, res1, writer_done_cb, ctx);

    lv_timer_del(timer);
}

static void begin_writing_cb(lv_event_t *e) {
    lv_obj_t *btn_label = lv_obj_get_child(begin_btn, 0);
    lv_label_set_text(btn_label, "等待服务器响应...");

    lv_timer_create(begin_writing_timer_cb, 10000, e->user_data);
}

static void add_footer(lv_obj_t *parent, lv_event_cb_t rewrite_btn_cb);
static void writer_done_cb(void *user_data) {
    lv_label_set_text(title, "已完成：论国际合作与多边关系的重要性");

    write_done_cb_ctx_t *ctx = user_data;
    add_footer(ctx->parent, ctx->rewrite_btn_cb);
}

static char dropdown_selected[100];
static lv_obj_t *rewrite_btn;
static void dropdown_cb(lv_event_t *e);
static void save_btn_cb(lv_event_t *e);
static void add_footer(lv_obj_t *parent, lv_event_cb_t rewrite_btn_cb) {
    if(!footer) {
        footer = lv_obj_create(parent);
        lv_obj_set_size(footer, LV_PCT(100), LV_SIZE_CONTENT);
        lv_obj_set_layout(footer, LV_LAYOUT_FLEX);
        lv_obj_set_flex_flow(footer, LV_FLEX_FLOW_COLUMN);
    } else {
        lv_obj_clear_flag(footer, LV_OBJ_FLAG_HIDDEN);
        lv_obj_remove_event_cb(rewrite_btn, NULL);
        lv_obj_add_event_cb(rewrite_btn, rewrite_btn_cb, LV_EVENT_CLICKED, parent);
        lv_obj_t *rewrite_btn_label = lv_obj_get_child(rewrite_btn, 0);
        lv_label_set_text(rewrite_btn_label, "修改");
        return;
    }

    lv_obj_t *footer_label = lv_label_create(footer);
    lv_obj_set_size(footer_label, LV_PCT(100), LV_SIZE_CONTENT);
    lv_label_set_text(footer_label,
                      "你可以从下面的选项中选择一个预置命令让 AI "
                      "对文章进行修改(用户自行输入修改内容的功能正在制作中)\n"
                      "或点击保存将文章保存到历史记录中");

    lv_obj_t *dd = lv_dropdown_create(footer);
    lv_dropdown_set_options(dd, "将论点扩充为文章\n为论点增加示例\n增加字数\n减少字数");
    lv_obj_t *dd_list = lv_dropdown_get_list(dd);
    lv_obj_set_style_text_font(dd_list, &lv_font_han_sans_16_3500, 0);
    lv_obj_set_size(dd, LV_PCT(100), LV_SIZE_CONTENT);
    lv_obj_add_event_cb(dd, dropdown_cb, LV_EVENT_VALUE_CHANGED, NULL);

    lv_obj_t *btn_row = lv_obj_create(footer);
    lv_obj_remove_style_all(btn_row);
    lv_obj_set_size(btn_row, LV_PCT(100), LV_SIZE_CONTENT);
    lv_obj_set_flex_flow(btn_row, LV_FLEX_FLOW_ROW);
    lv_obj_set_style_pad_gap(btn_row, 10, 0);

    rewrite_btn = lv_btn_create(btn_row);
    lv_obj_set_size(rewrite_btn, LV_PCT(49), LV_SIZE_CONTENT);
    lv_obj_t *rewrite_btn_label = lv_label_create(rewrite_btn);
    lv_label_set_text(rewrite_btn_label, "修改");
    lv_obj_add_event_cb(rewrite_btn, rewrite_btn_cb, LV_EVENT_CLICKED, parent);

    lv_obj_t *save_btn = lv_btn_create(btn_row);
    lv_obj_set_size(save_btn, LV_PCT(48), LV_SIZE_CONTENT);
    lv_obj_t *save_btn_label = lv_label_create(save_btn);
    lv_label_set_text(save_btn_label, "保存");
    lv_obj_add_event_cb(save_btn, save_btn_cb, LV_EVENT_CLICKED, save_btn_label);
}

static void dropdown_cb(lv_event_t *e) {
    lv_obj_t *obj = lv_event_get_target(e);
    lv_dropdown_get_selected_str(obj, dropdown_selected, sizeof(dropdown_selected));
}

static void begin_rewrite_before_timer(void) {
    lv_obj_t *btn_label = lv_obj_get_child(rewrite_btn, 0);
    lv_label_set_text(btn_label, "等待服务器响应...");
}

static void begin_rewrite_in_timer(lv_obj_t *parent) {
    lv_obj_scroll_to_y(parent, 0, LV_ANIM_ON);
    lv_obj_add_flag(footer, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(title, "正在修改文章...");
    lv_label_set_text(content, "");
}

static void rewrite_btn_timer_cb_1(lv_timer_t *timer) {
    lv_obj_t *parent = timer->user_data;
    begin_rewrite_in_timer(parent);

    write_done_cb_ctx_t *ctx = malloc(sizeof(write_done_cb_ctx_t));

    ctx->parent = parent;
    ctx->rewrite_btn_cb = rewrite_btn_cb_2;

    type_write_to_label(content, res2, writer_done_cb, ctx);

    lv_timer_del(timer);
}

static void rewrite_btn_cb_1(lv_event_t *e) {
    begin_rewrite_before_timer();
    lv_timer_create(rewrite_btn_timer_cb_1, 10000, e->user_data);
}

static void rewrite_btn_timer_cb_2(lv_timer_t *timer) {
    lv_obj_t *parent = timer->user_data;
    begin_rewrite_in_timer(parent);

    write_done_cb_ctx_t *ctx = malloc(sizeof(write_done_cb_ctx_t));

    ctx->parent = parent;
    ctx->rewrite_btn_cb = rewrite_btn_cb_3;

    HistoryList *history_list = get_history_list();
    type_write_to_label(content, history_list->list[0].content, writer_done_cb, ctx);

    lv_timer_del(timer);
}

static void rewrite_btn_cb_2(lv_event_t *e) {
    begin_rewrite_before_timer();
    lv_timer_create(rewrite_btn_timer_cb_2, 10000, e->user_data);
}

static void rewrite_btn_cb_3(lv_event_t *e) {
    LV_UNUSED(e);
}

static void save_timer_cb(lv_timer_t *timer);
static void save_btn_cb(lv_event_t *e) {
    lv_obj_t *btn_label = lv_event_get_user_data(e);
    lv_label_set_text(btn_label, "正在保存...");

    lv_timer_create(save_timer_cb, 2000, btn_label);
}

static void save_timer_cb(lv_timer_t *timer) {
    lv_obj_t *btn_label = timer->user_data;
    lv_label_set_text(btn_label, "保存成功！");
    lv_tabview_set_act(tabview, 2, LV_ANIM_ON);
    lv_timer_del(timer);
}

static const char *res1 =
    "引言：\n"
    "在当今全球化日益加深的背景下，国际合作与多边关系成为国家间互动的核心。习近平主席2025年首次出访东南亚三国，签署多项"
    "合作协议，强调多边主义的重要性，正是这一趋势的体现。本文将探讨国际合作与多边关系在当前国际格局中的重要性。\n\n"
    "分论点一：国际合作促进全球经济发展\n"
    "通过与越南、马来西亚和柬埔寨签署多项合作备忘录，中国不仅加强了与东南亚国家的经济联系，也为区域经济增长注入新动力。"
    "这种合作有助于构建更加稳定和繁荣的全球经济体系。\n\n"
    "分论点二：多边关系有助于应对全球性挑战\n"
    "在气候变化、公共卫生等全球性问题面前，单边主义难以奏效。习近平主席强调维护以联合国为核心的国际体系，反对单边主"
    "义和保护主义，体现了多边合作在解决全球问题中的关键作用。\n\n"
    "分论点三：多边合作增强国家间的互信与和平\n"
    "通过建立自由贸易区和签署合作协议，国家间的互信得以增强，地区和平与稳定也因此得到保障。这种合作机制有助于减少冲"
    "突，促进共同发展。\n\n"
    "结论：\n"
    "国际合作与多边关系是实现全球和平与繁荣的基石。在当前复杂多变的国际环境中，各国应加强合作，共同应对挑战，推动构"
    "建人类命运共同体。";

static const char *res2 =
    "分论点一：国际合作促进全球经济发展\n"
    "补充示例：\n"
    "例如，中国与越南签署的《关于共建跨境经济合作区的谅解备忘录》，不仅推动了基础设施建设，还促进了两国边境贸易的便利化"
    "，带动了当地就业和经济发展。与此同时，中国与马来西亚在数字经济和绿色能源领域达成合作，马来西亚槟城的一家中马合资企"
    "业正投资建设太阳能组件工厂，为当地带来新的产业链和技术转移，提升了该国在可再生能源领域的竞争力。\n\n"
    "分论点二：多边关系有助于应对全球性挑战\n"
    "补充示例：\n"
    "2025年初，中国与柬埔寨共同发起“湄公河流域水资源管理合作倡议”，联合多国专家共同研究洪水控制和水资源分配问题，以应对"
    "日益严峻的气候变化带来的水患。此外，在应对新一轮传染病防控方面，中国与东盟国家联合设立“公共卫生应急中心”，推动疫苗"
    "共享、疫情信息互通和医疗物资调配，为区域公共卫生安全提供了有力保障。\n\n"
    "分论点三：多边合作增强国家间的互信与和平\n"
    "补充示例：\n"
    "例如，《中国—东盟自由贸易协定升级议定书》的签署，不仅降低了关税壁垒，也建立了更透明的贸易争端解决机制，使各国在经"
    "贸往来中更加安心与信任。中国与柬埔寨联合举办的“和平使者”军事联合演习，也展现了两国在安全领域的合作默契，进一步提升"
    "了地区防务合作水平，为维护东南亚和平稳定提供了积极助力。\n\n"
    "结尾小幅润色建议（可选）：\n"
    "国际合作与多边关系是实现全球和平与繁荣的基石。在当前复杂多变的国际环境中，各国唯有秉持合作共赢理念，深化多边协作，"
    "才能共同应对挑战，开创构建人类命运共同体的光明未来。";
