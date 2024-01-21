#pragma once

#include "W4Framework.h"
#include "Components/RotateComponent.h"
#include "Components/InteractiveItem.h"
#include "UiWindows/GameDomUi.h"
#include "UiWindows/GameUi.h"

W4_USE_UNSTRICT_INTERFACE

void mute(bool off);
void callCTA();

class KitchenGame{
public:
    ~KitchenGame();

    void onStart(sptr<Camera> cum);
    void onUpdate(float dt);
    void onDestroy();
    void setOnWinCallback(std::function<void()> onWinCallback);
    void setOnFailCallback(std::function<void()> onFailCallback);
    void addItemsCount(bool win);
    void onFail();
    void updateSize();
private:
    void CreateGameUI();
    void CreateKitchen();
    void CreateBath();
    void CreateToilet();
    void CreateStand();
    void CreateChel();
    void CreateTutorialHand();

    void DisableTutorial();

    void callCTA();
private:

    void onWin();
    int winItemsCount = 0;
    int loseItemsCount = 0;
    bool gameStartedYes = false;
    std::function<void()> m_onWinCallback;
    std::function<void()> m_onFailCallback;
    std::string m_currButtonName;
    sptr<Node> m_currInteractiveItem;

    sptr<GameUi> m_gameUI = nullptr;
    sptr<GameDomUi> m_ui = nullptr;

    sptr<Node> m_root = nullptr;
    sptr<Node> m_kitchen = nullptr;
    sptr<Node> m_toilet = nullptr;
    sptr<Node> m_stand = nullptr;
    sptr<Node> m_bath = nullptr;
    sptr<Node> m_chel = nullptr;
    sptr<VisibleNode> m_hand = nullptr;

    sptr<Camera> m_camera = nullptr;

    enum class TutorialStates {
        InFocus,
        UnFocus,
        Help
    } toturial = TutorialStates::InFocus;
    float m_timeToTutorial = 3.0f;
    float m_tutorialTimeout = 3.0f;
    sptr<Node> m_nodeToFocus = nullptr;
    float m_fadeTime = 0.0f;
    sptr<Tween<float>> m_handFadeTween = nullptr;
    float m_fadeDuration = 0.7;
    sptr<Node> m_tutorialHand = nullptr;
    vec3 m_handOffset = vec3(0, 0, 0);

};