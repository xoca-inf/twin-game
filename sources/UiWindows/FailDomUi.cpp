#include "FailDomUi.h"
#include "Settings/ResourceLibary.h"
#include "Settings/Settings.h"
#include "Audio/AudioManager.h"

void FailDomUi::initContent() {

    auto mainRect = getRect();

    createItem(mainRect, "Fail", Offset(-0.1, OffsetType::PERCENT, PivotAt::LEFT),
        Offset(-0.1, OffsetType::PERCENT, PivotAt::RIGHT),
        Offset(0.2, OffsetType::PERCENT, PivotAt::TOP),
        Offset(0.5, OffsetType::PERCENT, PivotAt::BOTTOM),
        ResourceLibary::instance().getTexturePath("Fail"), 6.0f);

    getItem("Fail")->getRect()->setFill(FillType::INSIDE, 412.0 / 143.0);

    createImageButton(mainRect, "TryAgain",
        Offset(0.38, OffsetType::PERCENT, PivotAt::LEFT),
        Offset(0.38, OffsetType::PERCENT, PivotAt::RIGHT),
        Offset(0.76, OffsetType::PERCENT, PivotAt::TOP),
        Offset(0.13, OffsetType::PERCENT, PivotAt::BOTTOM),
        ResourceLibary::instance().getTexturePath("TryAgain"),
        ResourceLibary::instance().getTexturePath("TryAgainPressed"),
        6.0f);


    getItem("TryAgain")->getRect()->setFill(FillType::INSIDE, 316.0 / 134.0);
    getItem("TryAgain")->setClickable(true);
    getItem("TryAgain")->setClickCallback([this]() {
        m_returnToMenuCallback();
        AudioManager::instance().playClickSound();
        });
    getItem("TryAgain")->getRect()->setAlign(HorizontalAlign::Center, VerticalAlign::Bottom);
}

void FailDomUi::setVisible(std::string id, bool flag) {
    auto item = getItem(id);
    if (item != nullptr) {
        item->getWidget()->setVisible(flag);
    }
    else {
        W4_LOG_ERROR("[GameDomUi] cant get item %s", id.c_str());
    }
}