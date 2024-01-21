#pragma once
#include "W4Framework.h"
#include "Game/Interactive/InteractiveToilet.h"
#include "Game/Interactive/InteractiveBath.h"
#include "Game/Interactive/InteractiveStand.h"
#include "Game/KitchenGame.h"

W4_USE_UNSTRICT_INTERFACE

class InteractiveItem : public IComponent{
W4_COMPONENT(InteractiveItem, IComponent)
public:
    InteractiveItem(CloneTag, const InteractiveItem& from, Node& owner)
            : Super(CloneTag{}, from, owner)
    {
    }

    void initialize(const variant::Variant& data) override;
    void update(float dt) override;
    void finalize() override;
    ~InteractiveItem() override;

    void setup(sptr<IInteractive> animation, sptr<InteractiveArgs> args, sptr<Mesh> mesh, std::function<void(Node&)> onChooseItem);
    void setButtonNames(std::string winName, std::string fail1Name, std::string fail2Name);
    void onButtonClick(std::string name);
    void setWinCallback(std::function<void()> winCallback);
    void setFailCallback(std::function<void()> failCallback);
private:

    std::function<void()> m_winCallback;
    std::function<void()> m_failCallback;

    bool m_isClicked = false;

    void onWin();
    void onFail();
    void onFail2();
    std::string m_winName;
    std::string m_failName;
    std::string m_fail2Name;
    std::function<void(Node&)> m_onChooseItem;
    void setCollider(sptr<Mesh> mesh);
    sptr<IInteractive> m_interactiveAnimation;
};