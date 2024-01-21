#include "WinDomUi.h"
#include "Settings/ResourceLibary.h"
#include "Settings/Settings.h"
#include "Audio/AudioManager.h"

void WinDomUi::initContent() {

    auto mainRect = getRect();

    createItem(mainRect, "Win", Offset(0.1, OffsetType::PERCENT, PivotAt::LEFT),
        Offset(0.1, OffsetType::PERCENT, PivotAt::RIGHT),
        Offset(0.2, OffsetType::PERCENT, PivotAt::TOP),
        Offset(0.5, OffsetType::PERCENT, PivotAt::BOTTOM),
        ResourceLibary::instance().getTexturePath("Win"), 6.0f);

    getItem("Win")->getRect()->setFill(FillType::INSIDE, 473 / 111.0);

    createImageButton(mainRect, "nextLevel",
        Offset(0.38, OffsetType::PERCENT, PivotAt::LEFT),
        Offset(0.38, OffsetType::PERCENT, PivotAt::RIGHT),
        Offset(0.87, OffsetType::PERCENT, PivotAt::TOP),
        Offset(0.015, OffsetType::PERCENT, PivotAt::BOTTOM),
        ResourceLibary::instance().getTexturePath("Play"),
        ResourceLibary::instance().getTexturePath("PlayPressed"),
        6.0f);


    getItem("nextLevel")->getRect()->setFill(FillType::INSIDE, 316.0 / 134.0);
    getItem("nextLevel")->setClickable(true);
    getItem("nextLevel")->setClickCallback([this]() {
        m_returnToMenuCallback();
        AudioManager::instance().playClickSound();
        });
}

void WinDomUi::setVisible(std::string id, bool flag) {
    auto item = getItem(id);
    if (item != nullptr) {
        item->getWidget()->setVisible(flag);
    }
    else {
        W4_LOG_ERROR("[GameDomUi] cant get item %s", id.c_str());
    }
}