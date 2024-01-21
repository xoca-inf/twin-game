#pragma once
#include "W4Framework.h"
#include "FlowUi/Ui/WorldUi.h"

using namespace games::benice::ui;

class GameUi : public WorldUi {
public:
    GameUi(sptr<Node> root, sptr<Camera> camera, float distance, float baseOrder)
    : WorldUi(root,camera,distance, baseOrder){};
    void setWinPressedCallback( std::function<void()> callback)    {m_winPressedCallback = callback;};
    void setFailPressedCallback( std::function<void()> callback)    {m_failPressedCallback = callback;};
    void setButtonPressedCallback(std::function<void(std::string)> callback){m_buttonCallback = callback;};
    void changeButtons(std::vector<std::string>);
    void changeTextures();
    void onUpdate(float dt);

    void initContent() override;
    void startFadeAnim(bool isRechoose);
    void startAwakeAnim();

    sptr<UiRect> contentRect;

private:
    void createButtons();
    std::function<void(std::string name)> m_buttonCallback;
    std::function<void()> m_winPressedCallback;
    std::function<void()> m_failPressedCallback;
    bool m_isCreated = false;

    sptr<Tween<float>> m_fadeTween;
    float m_fadeTweenTime = 0.4f;
    float m_fadeTweenDuration = 0.4f;
    bool m_isFade;

    sptr<Tween<float>> m_awakeTween;
    float m_awakeTweenTime = 0.0f;
    float m_awakeTweenDuration = 0.4f;

    std::vector<std::string> m_names;

    bool m_isRechoose = false;
};
