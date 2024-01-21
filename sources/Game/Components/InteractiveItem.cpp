#include "InteractiveItem.h"
#include "Audio/AudioManager.h"

void InteractiveItem::initialize(const variant::Variant &data) {
    IComponent::initialize(data);
}

void InteractiveItem::setup(sptr<IInteractive> animation, sptr<InteractiveArgs> args, sptr<Mesh> mesh, std::function<void(Node&)> onChoose) {
    m_interactiveAnimation = animation;
    m_interactiveAnimation->setup(args);
    m_onChooseItem = onChoose;
    setCollider(mesh);
}

void InteractiveItem::update(float dt) {
    IComponent::update(dt);
    if(m_interactiveAnimation)
        m_interactiveAnimation->onUpdateAnimation(dt);
}

void InteractiveItem::finalize() {
    m_interactiveAnimation = nullptr;
    m_winCallback = nullptr;
    m_failCallback = nullptr;
    this->getOwner().removeCollider("aboba");
    IComponent::finalize();
}

InteractiveItem::~InteractiveItem() {

}

void InteractiveItem::onWin() {
    W4_LOG_DEBUG("WIN!!!!");
    m_interactiveAnimation->onWinAnimation();
    //here should be some delay;
    if(m_winCallback){
        m_winCallback();
    }
}

void InteractiveItem::onFail() {
    W4_LOG_DEBUG("FAIL!!!");
    m_interactiveAnimation->onFailAnimation();
    //here should be some delay;
    if(m_failCallback){
        m_failCallback();
    }
}

void InteractiveItem::onFail2() {
    W4_LOG_DEBUG("FAIL2!!!");
    m_interactiveAnimation->onFail2Animation();
    //here should be some delay;
    if(m_failCallback){
        m_failCallback();
    }
}

void InteractiveItem::setCollider(sptr<Mesh> mesh) {
    auto ScreencastEvent = [this](const CollisionInfo& info)
    {
        if (!m_isClicked) {
            auto *node = info.target->getParent();
            W4_LOG_DEBUG(node->getName().c_str());
            if (m_onChooseItem) {
                m_onChooseItem(this->getOwner());
            }
        }
    };

    auto collider = this->getOwner().addCollider<core::AABB>("aboba", mesh);
    collider->setScreencastCallback(ScreencastEvent);
}

void InteractiveItem::setButtonNames(std::string winName, std::string fail1Name, std::string fail2Name) {
    m_winName = winName;
    m_failName = fail1Name;
    m_fail2Name = fail2Name;
}

void InteractiveItem::onButtonClick(std::string name) {

    if(m_isClicked)
        return;

    m_isClicked = true;
    if(name == m_winName){
        AudioManager::instance().playClickSound();
        onWin();
    }else if(name == m_failName){
        AudioManager::instance().playClickSound();
        onFail();
    }else if(name == m_fail2Name){
        AudioManager::instance().playClickSound();
        onFail2();
    }
}

void InteractiveItem::setFailCallback(std::function<void()> failCallback) {
    m_failCallback = failCallback;
}

void InteractiveItem::setWinCallback(std::function<void()> winCallback) {
    m_winCallback = winCallback;
}


