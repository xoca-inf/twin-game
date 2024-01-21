#include "W4Framework.h"
#include "Settings/Settings.h"
#include "AdsNetworkWrapper.h"
#include "Audio/AudioManager.h"
#include "Settings/ResourceLibary.h"
#include "FlowUi/Fov/AdaptiveFov.h"
#include "gameFsm.h"

#include "UiWindows/GameUi.h"
#include "UiWindows/WinDomUi.h"
#include "UiWindows/FailDomUi.h"

#include "Game/KitchenGame.h"

W4_USE_UNSTRICT_INTERFACE

float preloadingTime = 1.0f;

struct NextersKitchen : public IGame
{
    void onConfig() override
    {
        Game::Config.StopUpdateWhenFocusLoss = false;
        Game::Config.AutoUsePreloader = false;
    }
    void onStart() override{
        m_isPause = false;
        w4::network::ads::start();
        platform::Platform::showLoader();

        W4_LOG_DEBUG("onStart called");
        Settings::instance();       // settings initialization here
        ResourceLibary::instance(); // resource libary initialization here
        initializeFsm();            // FSM initialization here

        w4::network::ads::onVisibleChangeHandler(this, [](void *w4Self, bool result) {
            mute(!result);
            }
        );
        w4::network::ads::onAudioVolumeChangeHandler(this, [](void *w4Self, float volume) {
            auto selfTyped = reinterpret_cast<NextersKitchen *>(w4Self);
            Audio::setGlobalGain(volume);
            });

        m_camera = Render::getScreenCamera(); // this is main game camera
        Render::getRoot()->addChild(m_camera); // camera is not a scene tree part by default
        m_camera->setClearColor(Settings::instance().getVec4("CameraClearColor"));
        m_camera->setWorldTranslation(Settings::instance().getVec3("CameraTranslation"));
        m_camera->setWorldRotation(DEG2RAD * Settings::instance().getVec3("CameraRotation"));

        Render::getPass(0)->getDirectionalLight()->setColor(
            Settings::instance().getVec3("LightColor"));
        Render::getPass(0)->getDirectionalLight()->setDirection(
            Settings::instance().getVec3("LightDirection"));
        Render::getPass(0)->getDirectionalLight()->enableShadows(true);
        Render::getPass(0)->setDirectionalLightShadowMaxDistance(
            Settings::instance().getInt("ShadowMaxDistance"));
        Render::getPass(0)->setDirectionalLightShadowMapSize(
            Settings::instance().getInt("ShadowMapSize"));

        platform::Platform::showLoader();
    }

    void onResize(const math::size &newSize) override {
        Render::getScreenCamera()->setFov(games::benice::utils::AdaptiveFov::getAdaptiveFov(newSize));
        if (m_winMenuUi) m_winMenuUi->updateSize();
        if (m_failUi) m_failUi->updateSize();
        if (m_game) m_game->updateSize();
    }

    void onPause() override {
        mute(true);
        m_isPause = true;
    }

    void onResume() override {
        mute(false);
        m_isPause = false;
    }

    void onUpdate(float dt) override{
        m_fsm.update(dt); // in case you need to implement onUpdateFunc on some states
    }

    void initializeFsm(){
        m_fsm.state<FSM::States::Preloading>().onEnterFunc = [this](auto&, auto&, auto&){
            platform::Platform::showLoader();
            AudioManager::instance().playMusic();

            Timer::addTask(preloadingTime, [this]() {m_fsm.processEvent(FSM::Events::Initialize);  return true; });
        };

        m_fsm.state<FSM::States::Preloading>().onLeaveFunc = [this](auto&, auto&, auto&){
        };

        m_fsm.state<FSM::States::Game>().onEnterFunc = [this](auto&, auto&, auto&){
            m_game = make::sptr<KitchenGame>();

            platform::Platform::hideLoader();

            m_game->setOnWinCallback([this]() { m_fsm.processEvent(FSM::Events::Win); });
            m_game->setOnFailCallback([this]() { m_fsm.processEvent(FSM::Events::Fail); });
            m_game->onStart(m_camera);
        };

        m_fsm.state<FSM::States::Game>().onUpdateFunc = [this](auto &, float dt) {
            if (m_game) {
                m_game->onUpdate(dt);
            }
        };

        m_fsm.state<FSM::States::Game>().onLeaveFunc = [this](auto&, auto&, auto&){
            W4_LOG_INFO("Game onLeave invoked");
        };

        m_fsm.state<FSM::States::WinMenu>().onEnterFunc = [this](auto&, auto&, auto&){
            W4_LOG_INFO("WinMenu onEnter invoked");
            m_winMenuUi = make::sptr<WinDomUi>(0);
            m_winMenuUi->init(false);
            m_winMenuUi->setReturnToMenuCallback([this]() { m_fsm.processEvent(FSM::Events::Next); });
        };
        m_fsm.state<FSM::States::WinMenu>().onLeaveFunc = [this](auto&, auto&, auto&){
            W4_LOG_INFO("Win onLeave invoked");
            m_winMenuUi = nullptr; // destroying sptr content here
        };

        m_fsm.state<FSM::States::FailMenu>().onEnterFunc = [this](auto&, auto&, auto&){
            W4_LOG_INFO("Fail onEnter invoked");
            m_failUi = make::sptr<FailDomUi>(0);
            m_failUi->init(false);
            m_failUi->setReturnToMenuCallback([this]() { m_fsm.processEvent(FSM::Events::Next); });
        };
        m_fsm.state<FSM::States::FailMenu>().onLeaveFunc = [this](auto&, auto&, auto&){
            W4_LOG_INFO("Fail onLeave invoked");
            m_failUi = nullptr; // destroying sptr content here
        };

        //launching first state - need to fsm process start
        m_fsm.init<FSM::States::Preloading>(FSM::Events::Initialize);
        W4_LOG_DEBUG("FSM initialized");
    }

private:
    bool m_isPause;

    FSM::Type m_fsm;
    sptr<Camera> m_camera;

    sptr<KitchenGame> m_game;
    sptr<WinDomUi> m_winMenuUi;
    sptr<FailDomUi> m_failUi;

};

W4_RUN(NextersKitchen)
