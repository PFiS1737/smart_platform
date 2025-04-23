#include "hotpoints.h"

HotpointList *get_hotpoint_list() {
    HotpointList *out = malloc(sizeof(HotpointList));
    out->count = 5;
    out->list = malloc(sizeof(Hotpoint) * out->count);

    for(int i = 0; i < out->count; i++) {
        out->list[i].year = 2025;
        out->list[i].month = 4;
        out->list[i].day = 15 + i;

        out->list[i].stars = lv_rand(4, 5);

        for(int j = 0; j < 7; j++) {
            out->list[i].analysis[j] = malloc(sizeof(Analysis));
            out->list[i].analysis[j]->percentage = lv_rand(40, 90);
        }
    }

    out->list[0].stars = 5;
    out->list[0].title = "习近平今年首次出访重要成果";
    out->list[0].content =
        "2025年4月，习近平主席对越南、马来西亚和柬埔寨进行了国事访问，强调中国将与东南亚国家共同应对全球经济冲击，提出"
        "与东盟建立自由贸易区的倡议，并签署多项合作备忘录，涵盖贸易、服务和基础设施等领域。 "
        "在访问期间，习近平主席呼吁维护以联合国为核心的国际体系，反对单边主义和保护主义，强调多边合作的重要性。 "
        "此外，中国与越南签署了45项合作协议，与马来西亚签署了31项协议，涵盖基础设施、技术和供应链等关键领域，彰显了"
        "中国在区域合作中的积极角色。";

    out->list[1].title = "人工智能与伦理问题";
    out->list[1].content = "人工智能技术的迅速发展对就业和隐私保护提出了新的挑战。在2025年，全球范围内对AI伦理问题的"
                           "关注持续升温，强调在推动科技进步的同时，必须确保人类价值观的核心地位。中国在推动AI技术发"
                           "展的同时，也在加强对相关伦理问题的研究和规范，确保技术进步与人类本真的关系协调发展。";

    out->list[2].title = "文化传承与创新";
    out->list[2].content = "传统节日是中华文化的重要组成部分，近年来，通过现代科技和创新手段，传统节日焕发出新的活力。"
                           "例如，利用虚拟现实技术重现传统节日场景，或通过社交媒体平台推广传统文化习俗，使年轻一代更"
                           "容易接触和理解传统文化，实现创造性转化与创新性发展。";

    out->list[3].title = "青年的责任与家国情怀";
    out->list[3].content =
        "“炫家乡”现象在社交媒体上日益流行，体现了新时代青年对家乡文化的自豪感和文化自信。这种现象不仅展示了地方文化的独"
        "特魅力，也反映了青年一代在传承和弘扬中华文化方面的责任与担当。通过积极参与家乡建设和文化传播，青年人展现了"
        "强烈的家国情怀和社会责任感。";

    out->list[4].title = "气候变化与可持续发展";
    out->list[4].content = "气候变化是全球面临的重大挑战之一。2025年，各国在应对气候变化方面的合作愈加紧密，"
                           "中国在推动可再生能源和绿色技术方面取得了显著进展。通过国际合作和技术创新，中国致力于实现"
                           "碳中和目标，为全球可持续发展贡献力量。";

    return out;
}
