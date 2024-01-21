#include "GameDomUi.h"
#include "Settings/ResourceLibary.h"
#include "Settings/Settings.h"

void GameDomUi::initContent() {

    auto mainRect = getRect();

    createItem(mainRect, "logo", Offset(0.02, 
        OffsetType::PERCENT, PivotAt::LEFT), 
        Offset(0.22, OffsetType::PERCENT, PivotAt::LEFT),
        Offset(0.05, OffsetType::PERCENT, PivotAt::TOP), 
        Offset(0.2 + 0.05, OffsetType::PERCENT, PivotAt::TOP), 
        ResourceLibary::instance().getTexturePath("Logo"), 4.0f);
    getItem("logo")->getRect()->setFill(FillType::INSIDE, 270.0 / 230.0);
    getItem("logo")->getRect()->setAlign(HorizontalAlign::Left, VerticalAlign::Top);

    /* install */

    createImageButton(mainRect, "install", Offset(0.22 + 0.015, OffsetType::PERCENT, PivotAt::RIGHT),
        Offset(0.0 + 0.015, OffsetType::PERCENT, PivotAt::RIGHT),

        Offset(0.1 + 0.02, OffsetType::PERCENT, PivotAt::BOTTOM),
        Offset(0 + 0.02, OffsetType::PERCENT, PivotAt::BOTTOM),
        ResourceLibary::instance().getTexturePath("Install"),
        ResourceLibary::instance().getTexturePath("InstallPressed"), 4.0f);

    getItem("install")->getRect()->setFill(FillType::INSIDE, 316.0 / 134.0);
    getItem("install")->getRect()->setAlign(HorizontalAlign::Right, VerticalAlign::Bottom);

    createImageButton(mainRect, "soundOn"
        , Offset(0.02, OffsetType::PERCENT, PivotAt::LEFT)
        , Offset(0.24, OffsetType::PERCENT, PivotAt::LEFT)
        , Offset(0.1 + 0.02, OffsetType::PERCENT, PivotAt::BOTTOM)
        , Offset(0 + 0.02, OffsetType::PERCENT, PivotAt::BOTTOM)
        , ResourceLibary::instance().getTexturePath("SoundOn"), 
        ResourceLibary::instance().getTexturePath("SoundOnPressed"), 4.0f);

    getItem("soundOn")->getRect()->setFill(FillType::INSIDE, 316.0 / 134.0);
    getItem("soundOn")->getRect()->setAlign(HorizontalAlign::Left, VerticalAlign::Bottom);

    createImageButton(mainRect, "soundOff"
        , Offset(0.02, OffsetType::PERCENT, PivotAt::LEFT)
        , Offset(0.24, OffsetType::PERCENT, PivotAt::LEFT)
        , Offset(0.1 + 0.02, OffsetType::PERCENT, PivotAt::BOTTOM)
        , Offset(0 + 0.02, OffsetType::PERCENT, PivotAt::BOTTOM)
        , ResourceLibary::instance().getTexturePath("SoundOff"),
        ResourceLibary::instance().getTexturePath("SoundOffPressed"), 4.0f);

    getItem("soundOff")->getRect()->setFill(FillType::INSIDE, 316.0 / 134.0);
    getItem("soundOff")->getRect()->setAlign(HorizontalAlign::Left, VerticalAlign::Bottom);

    createImageButton(mainRect, "start", 
        Offset(0.4, OffsetType::PERCENT, PivotAt::LEFT),
        Offset(0.4, OffsetType::PERCENT, PivotAt::RIGHT),
        Offset(0.88, OffsetType::PERCENT, PivotAt::TOP),
        Offset(0.02, OffsetType::PERCENT, PivotAt::BOTTOM),
        ResourceLibary::instance().getTexturePath("Play"),
        ResourceLibary::instance().getTexturePath("PlayPressed"), 
        6.0f);


    getItem("start")->getRect()->setFill(FillType::INSIDE, 316.0 / 134.0);
}

void GameDomUi::finalMenu() {
    getItem("install")->getRect()->initialize(
        Offset(0.4, OffsetType::PERCENT, PivotAt::LEFT),
        Offset(0.4, OffsetType::PERCENT, PivotAt::RIGHT),
        Offset(0.88, OffsetType::PERCENT, PivotAt::TOP),
        Offset(0.02, OffsetType::PERCENT, PivotAt::BOTTOM));

    getItem("install")->getRect()->setAlign(HorizontalAlign::Center, VerticalAlign::Bottom);
}

void GameDomUi::setVisible(std::string id, bool flag) {
    auto item = getItem(id);
    if (item != nullptr) {
        item->getWidget()->setVisible(flag);
    }
    else {
        W4_LOG_ERROR("[GameDomUi] cant get item %s", id.c_str());
    }
}