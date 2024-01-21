#include "GameUi.h"
#include "Settings/ResourceLibary.h"
#include "Audio/AudioManager.h"

void GameUi::initContent() {
    auto mainRect = getRect();

    contentRect = make::sptr<UiRect>(Offset(0.0, OffsetType::PERCENT, PivotAt::LEFT),
                                          Offset(0.0, OffsetType::PERCENT, PivotAt::RIGHT),
                                          Offset(0.0, OffsetType::PERCENT, PivotAt::TOP),
                                          Offset(0.0, OffsetType::PERCENT, PivotAt::BOTTOM));
    mainRect->addChild(contentRect);
}

void GameUi::startFadeAnim(bool isRechoose) {
    m_isRechoose = isRechoose;
    m_awakeTween = nullptr;
    m_fadeTweenTime = m_awakeTweenDuration - m_awakeTweenTime;
    m_fadeTween = make::sptr<Tween<float>>(1.0f);
    m_fadeTween->add(0.0f, m_fadeTweenDuration, Easing::Linear);
}

void GameUi::startAwakeAnim() {
    m_fadeTween = nullptr;
    m_awakeTweenTime = m_fadeTweenDuration - m_fadeTweenTime;
    m_awakeTween = make::sptr<Tween<float>>(0.0f);
    m_awakeTween->add(1.0f, m_awakeTweenDuration, Easing::Linear);
}

void GameUi::createButtons() {
    float offset = 0.15f;
    m_isCreated = true;
    for(int i = 0; i < 3; i++){
        createItem(
                contentRect,
                "button" + std::to_string(i),
                Offset(0.3f + i * offset, OffsetType::PERCENT, PivotAt::LEFT),
                Offset(0.6f - i * offset, OffsetType::PERCENT, PivotAt::RIGHT),
                Offset(0.8f, OffsetType::PERCENT, PivotAt::TOP),
                Offset(0.2f, OffsetType::PERCENT, PivotAt::BOTTOM),
                ResourceLibary::instance().getTexturePath("Book"),
                1.0);
        auto rect = contentRect->findChild("button" + std::to_string(i));
        rect->setFill(FillType::FIT_HORIZONTAL, 1.0f/1.0f);
        auto item = getItem("button" + std::to_string(i));
        item->setClickCallback([this](){
            if(m_buttonCallback) m_buttonCallback("Book");
        });
        item->setClickable(true);
    }
    updateSize();
}

void GameUi::changeTextures() {
    for (int i = 0; i < 3; ++i) {
        auto rect = contentRect->findChild("button" + std::to_string(i));
        auto item = getItem("button" + std::to_string(i));
        item->getMaterial()->setTexture(w4::resources::TextureId::TEXTURE_0,
            Texture::get(ResourceLibary::instance().getTexturePath(m_names[i])
            ));
    }
}

void GameUi::changeButtons(std::vector<std::string> names) {
    if (m_names == names) {
        return;
    }

    m_names = names;

    if (!m_isCreated) {
        createButtons();
    }    

    if (!m_isRechoose) {
        changeTextures();
        startAwakeAnim();
    }
    else {
        if (m_awakeTween || (!m_awakeTween && !m_fadeTween))
            startFadeAnim(true);
    }

    m_isRechoose = true;

    for (int i = 0; i < 3; ++i) {
        auto rect = contentRect->findChild("button" + std::to_string(i));
        auto item = getItem("button" + std::to_string(i));
        item->setClickCallback([this, names, i](){
            if(m_buttonCallback) m_buttonCallback(names[i]);
        });
    }

    AudioManager::instance().playClickSound();
}

void GameUi::onUpdate(float dt) {
    if (m_fadeTween) {
        float result = 0.0;
        m_fadeTweenTime += dt;
        result = m_fadeTween->getValue(m_fadeTweenTime);

        for (int i = 0; i < 3; ++i) {
            auto rect = contentRect->findChild("button" + std::to_string(i));
            auto item = getItem("button" + std::to_string(i));
            item->getMaterial()->setParam("color", vec4(1, 1, 1, result));
        }

        if (m_fadeTweenTime >= m_fadeTween->getDuration()) {
            if (m_isRechoose) {
                changeTextures();
                startAwakeAnim();
            }
            m_fadeTween = nullptr;
        }
    }

    if (m_awakeTween) {
        float result = 0.0;
        m_awakeTweenTime += dt;
        result = m_awakeTween->getValue(m_awakeTweenTime);
        for (int i = 0; i < 3; ++i) {
            auto rect = contentRect->findChild("button" + std::to_string(i));
            auto item = getItem("button" + std::to_string(i));
            item->getMaterial()->setParam("color", vec4(1, 1, 1, result));
        }

        if (m_awakeTweenTime >= m_awakeTween->getDuration()) {
            m_awakeTween = nullptr;
        }
    }
}
