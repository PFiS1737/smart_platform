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
static lv_pinyin_dict_t pinyin_dict[];
static void ta_event_cb(lv_event_t *e);
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
                      "你可以从下面的选项中选择一个预置命令让 AI 对文章进行修改\n"
                      "或在下方输入框中输入要求（优先使用）\n"
                      "或点击保存将文章保存到历史记录中");

    lv_obj_t *dd = lv_dropdown_create(footer);
    lv_dropdown_set_options(dd, "将论点扩充为文章\n为论点增加示例\n增加字数\n减少字数");
    lv_obj_t *dd_list = lv_dropdown_get_list(dd);
    lv_obj_set_style_text_font(dd_list, &lv_font_han_sans_16_3500, 0);
    lv_obj_set_size(dd, LV_PCT(100), LV_SIZE_CONTENT);
    lv_obj_add_event_cb(dd, dropdown_cb, LV_EVENT_VALUE_CHANGED, NULL);

    lv_obj_t *pinyin_ime = lv_ime_pinyin_create(lv_scr_act());
    lv_obj_set_style_text_font(pinyin_ime, &lv_font_han_sans_16_3500, 0);
    lv_ime_pinyin_set_dict(pinyin_ime, pinyin_dict);

    lv_obj_t *ta = lv_textarea_create(footer);
    lv_textarea_set_one_line(ta, true);
    lv_obj_set_style_text_font(ta, &lv_font_han_sans_16_3500, 0);
    lv_obj_set_size(ta, LV_PCT(100), LV_SIZE_CONTENT);

    lv_obj_t *kb = lv_keyboard_create(lv_scr_act());
    lv_ime_pinyin_set_keyboard(pinyin_ime, kb);
    lv_keyboard_set_textarea(kb, ta);
    lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_event_cb(ta, ta_event_cb, LV_EVENT_ALL, kb);

    lv_obj_t *cand_panel = lv_ime_pinyin_get_cand_panel(pinyin_ime);
    lv_obj_set_style_bg_opa(cand_panel, LV_OPA_100, 0);
    lv_obj_set_size(cand_panel, LV_PCT(100), LV_PCT(10));
    lv_obj_align_to(cand_panel, kb, LV_ALIGN_OUT_TOP_MID, 0, 0);

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

static void ta_event_cb(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *ta = lv_event_get_target(e);
    lv_obj_t *kb = lv_event_get_user_data(e);

    if(code == LV_EVENT_FOCUSED) {
        lv_keyboard_set_textarea(kb, ta);
        lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
    } else if(code == LV_EVENT_DEFOCUSED || code == LV_EVENT_READY) {
        lv_keyboard_set_textarea(kb, NULL);
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    } else if(code == LV_EVENT_CANCEL) {
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_state(ta, LV_STATE_FOCUSED);
        lv_indev_reset(NULL, ta);
    }
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

static lv_pinyin_dict_t pinyin_dict[] = {
    {"a", "啊"},
    {"ai", "爱"},
    {"an", "安暗案"},
    {"ba", "吧把爸八"},
    {"bai", "百白败"},
    {"ban", "半般办"},
    {"bang", "旁"},
    {"bao", "保薄包报"},
    {"bei", "被背悲北杯备"},
    {"ben", "本"},
    {"bi", "必比避鼻彼笔秘闭"},
    {"bian", "便边变变边"},
    {"biao", "表标"},
    {"bie", "别"},
    {"bing", "病并冰"},
    {"bo", "波薄泊"},
    {"bu", "不布步部捕补步"},
    {"ca", "察"},
    {"cai", "才材菜财采"},
    {"can", "参残参"},
    {"ce", "策侧"},
    {"ceng", "曾"},
    {"cha", "差查茶"},
    {"chai", "差"},
    {"chan", "产产单"},
    {"chang", "场厂"},
    {"chao", "超朝"},
    {"che", "车"},
    {"cheng", "成程乘"},
    {"chi", "尺吃持赤池迟齿"},
    {"chong", "充种重种"},
    {"chu", "出初楚触处处"},
    {"chuan", "川船传"},
    {"chuang", "创窗"},
    {"chun", "春"},
    {"ci", "此次辞差"},
    {"cong", "从从"},
    {"cu", "卒"},
    {"cun", "存村"},
    {"cuo", "错"},
    {"da", "大打答达"},
    {"dai", "代待带带贷"},
    {"dan", "但担担诞单单"},
    {"dang", "当党当党"},
    {"dao", "到道盗导岛边"},
    {"de", "的得"},
    {"dei", ""},
    {"deng", "等"},
    {"di", "地得低底弟第缔"},
    {"dian", "点电店点电"},
    {"diao", "调"},
    {"ding", "定町"},
    {"dong", "冬东动动冻"},
    {"du", "独度都渡读"},
    {"duan", "段断短断"},
    {"dui", "对对"},
    {"duo", "多驮"},
    {"e", "嗯恶"},
    {"en", "嗯"},
    {"er", "而耳二儿"},
    {"fa", "乏法发发发"},
    {"fan", "反返犯番假贩饭范払"},
    {"fang", "方放房坊访"},
    {"fei", "非飞费"},
    {"fen", "分份"},
    {"feng", "风丰"},
    {"fou", "否不"},
    {"fu", "父夫富服符付附府幅妇复复负払"},
    {"gai", "改概该"},
    {"gan", "甘感敢"},
    {"gang", "港刚"},
    {"gao", "告高"},
    {"ge", "各格歌革割个"},
    {"gei", "给"},
    {"gen", "跟根"},
    {"geng", "更"},
    {"gong", "工共供功公"},
    {"gou", "够构沟"},
    {"gu", "古故鼓"},
    {"guai", "挂"},
    {"guan", "官管惯馆观关关"},
    {"guang", "光广"},
    {"gui", "规归"},
    {"guo", "果国里果国过"},
    {"hai", "孩海害还"},
    {"han", "寒汉"},
    {"hang", "航行"},
    {"hao", "好号"},
    {"he", "合和喝何荷"},
    {"hei", "黑"},
    {"hen", "很"},
    {"heng", "行横"},
    {"hou", "厚喉候后"},
    {"hu", "乎呼湖护"},
    {"hua", "化画花话画划"},
    {"huai", "坏划"},
    {"huan", "缓环欢还换"},
    {"huang", "黄"},
    {"hui", "回会慧绘挥会"},
    {"hun", "混婚"},
    {"huo", "活或火获"},
    {"i", ""},
    {"ji", "己计及机既急季寄技即集基祭系奇纪积计记济几际极继绩机济"},
    {"jia", "家加价"},
    {"jian", "件建健肩见减间检简渐"},
    {"jiang", "降强讲将港"},
    {"jiao", "叫教交角觉觉较学"},
    {"jie", "介借接姐皆届界解结阶节价"},
    {"jin", "今近禁金仅进"},
    {"jing", "京境景静精经经"},
    {"jiu", "就久九酒究"},
    {"ju", "句具局居决举据举"},
    {"jue", "角觉觉"},
    {"jun", "均"},
    {"kai", "开"},
    {"kan", "看刊"},
    {"kang", "康"},
    {"kao", "考"},
    {"ke", "可刻科克客渴课"},
    {"ken", "肯"},
    {"kong", "空控"},
    {"kou", "口"},
    {"ku", "苦库"},
    {"kuai", "快块会会"},
    {"kuang", "况"},
    {"kun", "困"},
    {"kuo", "括扩适"},
    {"la", "拉啦落"},
    {"lai", "来来赖"},
    {"lao", "老络落"},
    {"le", "了乐乐"},
    {"lei", "类"},
    {"leng", "冷"},
    {"li", "力立利理例礼离丽里励历"},
    {"lian", "连练脸联"},
    {"liang", "良量凉两两"},
    {"liao", "料"},
    {"lie", "列"},
    {"lin", "林邻赁"},
    {"ling", "另令领"},
    {"liu", "六留流"},
    {"lu", "律路录绿陆履虑"},
    {"lv", "旅"},
    {"lun", "轮论"},
    {"luo", "落络"},
    {"ma", "妈吗嘛"},
    {"mai", "买卖"},
    {"man", "满"},
    {"mang", "忙"},
    {"mao", "毛猫贸"},
    {"me", "么"},
    {"mei", "美妹每没每媒"},
    {"men", "们"},
    {"mi", "米密秘"},
    {"mian", "免面勉眠"},
    {"miao", "描"},
    {"min", "民皿"},
    {"ming", "命明名"},
    {"mo", "末模么"},
    {"mou", "某"},
    {"mu", "母木目模"},
    {"na", "那哪拿内南"},
    {"nan", "男南难"},
    {"nao", "脑"},
    {"ne", "那哪呢"},
    {"nei", "内那哪内"},
    {"neng", "能"},
    {"ni", "你妳呢"},
    {"nian", "年念"},
    {"niang", "娘"},
    {"nin", "您"},
    {"ning", "凝"},
    {"niu", "牛"},
    {"nong", "农浓"},
    {"nu", "女努"},
    {"nuan", "暖"},
    {"o", ""},
    {"ou", "欧"},
    {"pan", "判盘盼"},
    {"pang", "旁胖"},
    {"pao", "跑炮泡"},
    {"pei", "陪配佩赔"},
    {"pen", "喷"},
    {"peng", "朋碰捧蓬"},
    {"pi", "皮批疲匹辟披脾"},
    {"pian", "片骗偏"},
    {"piao", "票漂飘"},
    {"pin", "品贫频拼"},
    {"ping", "平评瓶"},
    {"po", "破迫婆坡泊"},
    {"pu", "普铺朴仆谱"},
    {"qi", "其起七期器汽奇骑妻企旗齐弃气棋祈乞"},
    {"qia", "恰洽"},
    {"qian", "前千钱签浅迁欠潜牵"},
    {"qiang", "强枪抢墙"},
    {"qiao", "桥悄巧瞧敲乔侨"},
    {"qie", "切且窃"},
    {"qin", "亲勤秦琴侵钦"},
    {"qing", "情请青清轻庆"},
    {"qiong", "穷"},
    {"qiu", "求球秋仇囚"},
    {"qu", "去取曲区屈趋娶驱"},
    {"quan", "全权劝泉拳圈"},
    {"que", "却缺确雀"},
    {"qun", "群裙"},
    {"ran", "然燃染"},
    {"rang", "让嚷"},
    {"rao", "绕扰"},
    {"re", "热"},
    {"ren", "人任认忍仁"},
    {"reng", "仍扔"},
    {"ri", "日"},
    {"rong", "容荣融绒熔"},
    {"rou", "肉柔"},
    {"ru", "如入乳辱儒"},
    {"ruan", "软"},
    {"rui", "瑞锐"},
    {"run", "润"},
    {"ruo", "若弱"},
    {"sa", "撒洒萨"},
    {"sai", "赛塞"},
    {"san", "三散伞"},
    {"sang", "丧桑"},
    {"sao", "扫骚嫂"},
    {"se", "色涩瑟"},
    {"sen", "森"},
    {"sha", "沙杀啥傻煞"},
    {"shai", "晒"},
    {"shan", "山闪善衫删扇"},
    {"shang", "上商伤尚赏裳"},
    {"shao", "少烧稍勺哨"},
    {"she", "社设舍摄舌蛇射涉"},
    {"shen", "身神深审申甚渗"},
    {"sheng", "生声胜升省圣剩"},
    {"shi", "是时使事市式师诗失识史试石食十实室世势示氏释视始适饰尸拾释驶"},
    {"shou", "手受收首守寿授售兽瘦"},
    {"shu", "书树数属熟输术述舒鼠暑梳蜀赎"},
    {"shua", "刷耍"},
    {"shuai", "帅甩摔衰"},
    {"shuan", "栓拴"},
    {"shuang", "双霜爽"},
    {"shui", "水谁睡税"},
    {"shun", "顺舜"},
    {"shuo", "说硕朔烁"},
    {"si", "四思死斯似私寺丝司饲撕"},
    {"song", "送松颂宋讼"},
    {"sou", "搜艘嗽"},
    {"su", "素速诉俗苏肃"},
    {"suan", "酸算蒜"},
    {"sui", "随岁碎虽穗"},
    {"sun", "孙损"},
    {"suo", "所索锁缩梭嗦"},
    {"ta", "他她它踏塔塌"},
    {"tai", "台太态抬胎泰"},
    {"tan", "谈探坦贪叹碳摊弹"},
    {"tang", "唐汤堂糖躺烫趟"},
    {"tao", "讨套逃淘桃"},
    {"te", "特忑"},
    {"teng", "腾疼誊"},
    {"ti", "体提题替梯剃蹄啼踢惕"},
    {"tian", "天田添甜填"},
    {"tiao", "条跳挑调"},
    {"tie", "铁贴帖"},
    {"ting", "听停厅挺亭廷"},
    {"tong", "同通统痛铜童筒桶"},
    {"tou", "头投透偷"},
    {"tu", "土图突徒吐途涂屠"},
    {"tuan", "团湍"},
    {"tui", "推退腿蜕褪"},
    {"tun", "吞屯囤"},
    {"tuo", "脱拖托妥驼拓驮"},
    {"wa", "娃挖哇洼蛙瓦袜"},
    {"wai", "外歪"},
    {"wan", "晚完万玩湾弯腕碗挽"},
    {"wang", "往王望忘网亡旺"},
    {"wei", "为位未委围威维微味卫违喂唯伟尾伪慰苇魏惟韦炜"},
    {"wen", "问文温闻稳吻纹蚊"},
    {"weng", "翁瓮"},
    {"wo", "我握卧窝喔蜗涡"},
    {"wu", "无五务物误武午舞污屋吾吴伍悟雾巫毋勿"},
    {"xi", "西系习细喜希吸洗息戏席袭悉惜溪晰锡牺昔媳膝熄隙蟋熙栖犀徙"},
    {"xia", "下夏吓霞峡瞎狭匣辖暇厦"},
    {"xian", "现先线县限显险鲜献闲贤陷仙弦咸涎羡掀冼衔"},
    {"xiang", "想向象相香乡享详箱翔降祥响项像橡湘镶襄"},
    {"xiao", "小笑效校消销晓肖削孝硝萧哮嚣"},
    {"xie", "写些谢协斜鞋血泄械卸歇蝎邪胁偕"},
    {"xin", "心新信欣辛薪鑫衅馨忻"},
    {"xing", "行性星型形兴幸醒腥杏刑猩姓省"},
    {"xiong", "兄雄胸熊凶"},
    {"xiu", "修秀袖宿羞锈绣嗅朽休"},
    {"xu", "许需须序虚徐续绪畜旭叙蓄酗栩"},
    {"xuan", "选宣旋玄悬轩喧癣漩炫"},
    {"xue", "学雪血削靴穴薛谑"},
    {"xun", "寻训讯迅逊巡循熏殉驯汛"},
    {"ya", "亚压牙雅涯崖呀鸭押讶"},
    {"yan", "言严眼验演烟盐延燕炎掩研宴咽沿艳焰堰厌雁砚彦衍颜"},
    {"yang", "样养阳洋央杨扬痒秧殃仰鸯"},
    {"yao", "要药摇遥邀腰咬耀窑姚舀"},
    {"ye", "也业叶夜爷野液冶掖腋谒"},
    {"yi", "一以已义意依易议移医艺异益衣遗亦忆伊宜仪译蚁翼乙亿疑抑逸怡倚毅壹揖诣疫"},
    {"yin", "因音引银印阴饮隐吟殷尹荫瘾"},
    {"ying", "应影英营迎赢硬映鹰婴蝇颖荧莹萤缨"},
    {"yo", "哟唷"},
    {"yong", "用永勇涌拥庸佣咏雍踊甬"},
    {"you", "有又由优游右油友尤邮幼诱忧幽悠佑铀柚"},
    {"yu", "与于育鱼余雨玉语欲遇预愈宇羽域誉狱舆豫渝寓淤盂榆吁毓喻禹熨"},
    {"yuan", "原元愿远园员源圆缘冤援渊猿鸳垣"},
    {"yue", "月越约阅乐悦跃岳粤钥曰刖"},
    {"yun", "云运允孕匀韵酝耘郧陨蕴"},
    {"za", "杂砸咋咂匝"},
    {"zai", "在再载灾宰栽仔哉"},
    {"zan", "暂赞攒咱"},
    {"zang", "藏脏葬赃"},
    {"zao", "早造糟遭噪灶燥枣澡"},
    {"ze", "则责择泽仄"},
    {"zei", "贼"},
    {"zen", "怎谮"},
    {"zeng", "曾增赠憎"},
    {"zha", "扎炸乍渣诈闸札铡栅榨眨喳砟"},
    {"zhai", "宅窄债摘斋寨"},
    {"zhan", "展战占站粘盏斩沾栈湛绽蘸"},
    {"zhang", "张长章掌涨帐仗障彰丈胀杖樟"},
    {"zhao", "找照招赵朝召罩兆沼肇"},
    {"zhe", "这着者折哲浙蔗遮辙锗"},
    {"zhen", "真镇振针阵珍震诊侦贞枕桢"},
    {"zheng", "正政整争证征挣症蒸钲"},
    {"zhi", "之只知至制指直志治值质执植纸智致置职支脂汁肢滞吱帜旨痔挚轵"},
    {"zhong", "中种重终忠钟众肿仲衷冢盅"},
    {"zhou", "周州洲皱粥舟轴骤昼宙肘咒"},
    {"zhu", "主住注助著诸朱逐筑祝驻柱珠铸嘱贮猪煮竹蛛诛烛"},
    {"zhua", "抓"},
    {"zhuai", "拽"},
    {"zhuan", "转专砖赚撰篆"},
    {"zhuang", "装状庄壮撞幢桩妆"},
    {"zhui", "追坠缀锥赘"},
    {"zhun", "准谆"},
    {"zhuo", "捉着桌啄琢灼浊茁酌拙"},
    {"zi", "字自子资紫姿滋咨仔兹孜渍梓锱龇"},
    {"zong", "总宗踪综纵棕粽"},
    {"zou", "走奏揍"},
    {"zu", "组族足祖租阻卒诅俎"},
    {"zuan", "钻攥"},
    {"zui", "最罪嘴醉"},
    {"zun", "尊遵"},
    {"zuo", "做作坐左昨佐柞嘬阼"},
    {NULL, NULL}};
