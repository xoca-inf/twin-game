#include "KitchenGame.h"
#include "Settings/ResourceLibary.h"
#include "Settings/Settings.h"
#include "AdsNetworkWrapper.h"
#include "Audio/AudioManager.h"
#include <algorithm>
#include "Effects/Explosion.h"

KitchenGame::~KitchenGame() {
    Render::getRoot()->removeChild(m_root);
}

void KitchenGame::onStart(sptr<Camera> cum) {
    W4_LOG_DEBUG("on start");
    m_root = make::sptr<Node>();
    Render::getRoot()->addChild(m_root);

    m_camera = cum;

    m_gameUI = make::sptr<GameUi>(m_camera, m_camera, 2.f, 0.f);
    m_gameUI->init(false);

    CreateGameUI();

    winItemsCount = 0;
    CreateKitchen();
    CreateToilet();
    CreateStand();
    CreateBath();
    CreateChel();
    CreateTutorialHand();
    m_gameUI->setButtonPressedCallback([this](std::string name){
        if (m_currInteractiveItem && m_currInteractiveItem->getAllComponents<InteractiveItem>().size() > 0)
            m_currInteractiveItem->getFirstComponent<InteractiveItem>().onButtonClick(name);
    });

    ResetExplosionSystem();
    DisableTutorial();
}

void KitchenGame::onUpdate(float dt) {
    if (m_gameUI) {
        m_gameUI->onUpdate(dt);
    }
    ProcessExplosions();

    if (gameStartedYes) {
        if (toturial == TutorialStates::UnFocus) {
            m_timeToTutorial -= dt;
            if (m_timeToTutorial <= 0.0f) {
                toturial = TutorialStates::Help;
                if (m_bath->getAllComponents<InteractiveItem>().size() != 0) {
                    m_nodeToFocus = m_bath;
                    m_hand->setLocalScale(Settings::instance().getVec3("HandBathScale"));
                    m_handOffset = Settings::instance().getVec3("HandBathTranslation");
                }
                else if (m_toilet->getAllComponents<InteractiveItem>().size() != 0) {
                    m_nodeToFocus = m_toilet;
                    m_hand->setLocalScale(Settings::instance().getVec3("HandToiletScale"));
                    m_handOffset = Settings::instance().getVec3("HandToiletTranslation");
                }
                else if (m_stand->getAllComponents<InteractiveItem>().size() != 0) {
                    m_nodeToFocus = m_stand;
                    m_hand->setLocalScale(Settings::instance().getVec3("HandStandScale"));
                    m_handOffset = Settings::instance().getVec3("HandStandTranslation");
                }
                m_handFadeTween = make::sptr<Tween<float>>(0);
                m_handFadeTween->add(1, m_fadeDuration, Easing::Linear);
                m_handFadeTween->add(1, m_fadeDuration + 0.1, Easing::Linear);
                m_handFadeTween->add(0, 2 * m_fadeDuration + 0.1, Easing::Linear);

                m_hand->setEnabled(true);
                vec3 localScale = m_hand->getLocalScale();
            }
        }
        if (toturial == TutorialStates::Help) {
            vec2 pos = m_camera->getScreenNormalizedFromWorldPoint(m_nodeToFocus->getWorldTranslation());
            m_hand->setLocalTranslation(vec3(pos.x, pos.y, 1.1f) + m_handOffset);
            if (m_handFadeTween) {
                m_fadeTime += dt;
                m_hand->getMaterialInst()->setParam("color", vec4(1, 1, 1, m_handFadeTween->getValue(m_fadeTime)));
                if (m_fadeTime > m_handFadeTween->getDuration()) {
                    m_fadeTime = 0.0f;
                }
            }
        }
    }
}

void KitchenGame::DisableTutorial() {
    toturial = TutorialStates::InFocus;
    m_timeToTutorial = m_tutorialTimeout;
    m_hand->setEnabled(false);
    m_nodeToFocus = nullptr;
    m_handFadeTween = nullptr;
    m_tutorialHand = nullptr;
    m_fadeTime = 0.0f;
}

void KitchenGame::CreateTutorialHand() {
    m_hand = Mesh::create::plane(vec2(1, 1));
    auto mat = ResourceLibary::instance().getMaterial("Sprite")->createInstance();
    mat->setTexture(TextureId::TEXTURE_0, ResourceLibary::instance().getTexture("Hand"));
    m_hand->traversalTyped<VisibleNode>([&](cref<VisibleNode> node) {
        node->setMaterialInst(mat);
        });

    m_camera->addChild(m_hand);

    m_hand->setLocalRotation(Rotator(0, 0, 0));
    m_hand->setEnabled(false);
}

void KitchenGame::CreateKitchen() {
    m_kitchen = make::sptr<Node>();

    auto mesh = ResourceLibary::instance().getModel("Scene")->getFirstRoot();
    auto mat = ResourceLibary::instance().getMaterial("Default")->createInstance();
    mat->setTexture(TextureId::TEXTURE_0, ResourceLibary::instance().getTexture("Scene"));
    mat->setParam("light_params", Settings::instance().getVec3("ShadowIntensity"));
    mat->setParam("shinessParam", Settings::instance().getFloat("LightShiness"));
    mesh->traversalTyped<VisibleNode>([&](cref<VisibleNode> node) {
        node->setMaterialInst(mat);
        });
    mesh->setWorldScale(vec3(1,1,1) * Settings::instance().getFloat("SceneScale"));
    mesh->setWorldRotation(DEG2RAD * Settings::instance().getVec3("SceneRotation"));
    mesh->setWorldTranslation(Settings::instance().getVec3("SceneTranslation") + vec3(0,
        Settings::instance().getFloat("CameraHeight"), Settings::instance().getFloat("CameraWidth")));

    m_kitchen->addChild(mesh);
    m_kitchen->template addComponent<RotateComponent>();
    m_root->addChild(m_kitchen);
}

void KitchenGame::CreateChel() {
    m_chel = make::sptr<Node>();

    auto mesh = ResourceLibary::instance().getModel("Chel")->getFirstRoot();
    auto mat = ResourceLibary::instance().getMaterial("Default")->createInstance();
    mat->setTexture(TextureId::TEXTURE_0, ResourceLibary::instance().getTexture("Chel"));
    W4_LOG_ERROR("here1");
    mat->setParam("light_params", Settings::instance().getVec3("ShadowIntensity"));
    mat->setParam("shinessParam", Settings::instance().getFloat("LightShiness"));
    mesh->traversalTyped<VisibleNode>([&](cref<VisibleNode> node) {
        node->setMaterialInst(mat);
        });
    mesh->setLocalScale(vec3(1, 1, 1) * Settings::instance().getFloat("ChelScale"));
    mesh->setLocalRotation(DEG2RAD * Settings::instance().getVec3("ChelRotation"));
    mesh->setLocalTranslation(Settings::instance().getVec3("ChelTranslation") + vec3(0,
        Settings::instance().getFloat("CameraHeight"), Settings::instance().getFloat("CameraWidth")));

    m_chel->addChild(mesh);

    m_kitchen->addChild(m_chel);
}

void KitchenGame::CreateToilet() {
    std::vector<std::string> buttonNames = {"Tros", "Otvertka", "Vantuz"};
    m_toilet = make::sptr<Node>();
    m_toilet->setName("Toilet");

    auto mesh = ResourceLibary::instance().getModel("Toilet_broken_1")->getFirstRoot();
    mesh->setName("Toilet");
    auto mat = ResourceLibary::instance().getMaterial("Default")->createInstance();
    mat->setTexture(TextureId::TEXTURE_0, ResourceLibary::instance().getTexture("Color_2"));
    mat->setParam("light_params", Settings::instance().getVec3("ShadowIntensity"));
    mat->setParam("shinessParam", Settings::instance().getFloat("LightShiness"));
    mesh->traversalTyped<VisibleNode>([&](cref<VisibleNode> node) {
        node->setMaterialInst(mat);
        });

    m_toilet->addChild(mesh);

    mesh->setLocalRotation(Rotator(0, 0, 0));
    mesh->setLocalTranslation(vec3(0, 0, 0));
    mesh->setLocalScale(vec3(1, 1, 1));

    m_kitchen->addChild(m_toilet);

    m_toilet->setLocalScale(vec3(1, 1, 1) * Settings::instance().getFloat("Toilet_broken_1_Scale"));
    m_toilet->setLocalRotation(DEG2RAD * Settings::instance().getVec3("Toilet_broken_1_Rotation"));
    m_toilet->setLocalTranslation(Settings::instance().getVec3("Toilet_broken_1_Translation") + vec3(0,
        Settings::instance().getFloat("CameraHeight"), Settings::instance().getFloat("CameraWidth")));

    auto toiletArgs = make::sptr<ToiletArgs>();
    toiletArgs->m_node = m_toilet;
    toiletArgs->m_mesh = Mesh::create::cube(vec3(1, 1, 1) * 300);
    auto& component = m_toilet->addComponent<InteractiveItem>();
    component.setup(make::sptr<InteractiveToilet>(), toiletArgs, toiletArgs->m_mesh, [this, buttonNames](Node& node){
        if (gameStartedYes) {
            W4_LOG_DEBUG("click !!!! %s", node.getName().c_str());
            DisableTutorial();
            m_currInteractiveItem = m_toilet;
            m_gameUI->changeButtons(buttonNames);
        }
    });
    component.setButtonNames("Vantuz", "Tros", "Otvertka");
    component.setFailCallback([this](){addItemsCount(false); m_toilet->removeAllComponents<InteractiveItem>(); });
    component.setWinCallback([this](){addItemsCount(true); m_toilet->removeAllComponents<InteractiveItem>(); });
}

void KitchenGame::CreateStand(){
    std::vector<std::string> buttonNames = {"Otvertka", "Izolenta", "Vantuz"};
    m_stand = make::sptr<Node>();
    m_stand->setName("Stand");

    auto mesh = ResourceLibary::instance().getModel("Stand_broken_1")->getFirstRoot();
    mesh->setName("Stand");
    auto mat = ResourceLibary::instance().getMaterial("Default")->createInstance();
    mat->setTexture(TextureId::TEXTURE_0, ResourceLibary::instance().getTexture("Color_2"));
    mat->setParam("light_params", Settings::instance().getVec3("ShadowIntensity"));
    mat->setParam("shinessParam", Settings::instance().getFloat("LightShiness"));
    mesh->traversalTyped<VisibleNode>([&](cref<VisibleNode> node) {
        node->setMaterialInst(mat);
        });

    m_stand->addChild(mesh);

    mesh->setLocalRotation(Rotator(0, 0, 0));
    mesh->setLocalTranslation(vec3(0, 0, 0));
    mesh->setLocalScale(vec3(1, 1, 1));

    m_kitchen->addChild(m_stand);

    m_stand->setLocalScale(vec3(1, 1, 1) * Settings::instance().getFloat("Stand_broken_1_Scale"));
    m_stand->setLocalRotation(DEG2RAD * Settings::instance().getVec3("Stand_broken_1_Rotation"));
    m_stand->setLocalTranslation(Settings::instance().getVec3("Stand_broken_1_Translation") + vec3(0,
        Settings::instance().getFloat("CameraHeight"), Settings::instance().getFloat("CameraWidth")));

    auto standArgs = make::sptr<StandArgs>();
    standArgs->m_node = m_stand;
    standArgs->m_mesh = Mesh::create::cube(vec3(1, 2, 1) * 300);
    auto& component = m_stand->addComponent<InteractiveItem>();
    component.setup(make::sptr<InteractiveStand>(), standArgs, standArgs->m_mesh,
        [this,buttonNames](Node& node){
            if (gameStartedYes) {
                W4_LOG_DEBUG("click !!!! %s", node.getName().c_str());
                DisableTutorial();
                m_currInteractiveItem = m_stand;
                m_gameUI->changeButtons(buttonNames);
            }
        });
    component.setFailCallback([this]() {addItemsCount(false); m_stand->removeAllComponents<InteractiveItem>(); });
    component.setWinCallback([this](){addItemsCount(true); m_stand->removeAllComponents<InteractiveItem>(); });
    component.setButtonNames("Otvertka", "Izolenta", "Vantuz");
}

void KitchenGame::CreateBath(){
    std::vector<std::string> buttonNames = {"Book", "Izolenta", "Molotok"};
    m_bath = make::sptr<Node>();
    m_bath->setName("Bath");
    
    auto mesh = ResourceLibary::instance().getModel("Bath_broken_1")->getFirstRoot();
    mesh->setName("Bath");
    
    auto mat = ResourceLibary::instance().getMaterial("Default")->createInstance();
    mat->setTexture(TextureId::TEXTURE_0, ResourceLibary::instance().getTexture("Color_2"));
    mat->setParam("light_params", Settings::instance().getVec3("ShadowIntensity"));
    mat->setParam("shinessParam", Settings::instance().getFloat("LightShiness"));
    mesh->traversalTyped<VisibleNode>([&](cref<VisibleNode> node) {
        node->setMaterialInst(mat);
        });

    toturial = TutorialStates::Help;

    m_bath->addChild(mesh);

    mesh->setLocalRotation(Rotator(0, 0, 0));
    mesh->setLocalTranslation(vec3(0, 0, 0));
    mesh->setLocalScale(vec3(1, 1, 1));

    m_kitchen->addChild(m_bath);

    m_bath->setLocalScale(vec3(1, 1, 1) * Settings::instance().getFloat("Bath_broken_1_Scale"));
    m_bath->setLocalRotation(DEG2RAD * Settings::instance().getVec3("Bath_broken_1_Rotation"));
    m_bath->setLocalTranslation(Settings::instance().getVec3("Bath_broken_1_Translation") + vec3(0,
        Settings::instance().getFloat("CameraHeight"), Settings::instance().getFloat("CameraWidth")));

    auto bathArgs = make::sptr<BathArgs>();
    bathArgs->m_node = m_bath;
    bathArgs->m_mesh = Mesh::create::cube(vec3(1, 1, 2) * 300);
    auto& component = m_bath->addComponent<InteractiveItem>();
    component.setup(make::sptr<InteractiveBath>(), bathArgs, bathArgs->m_mesh, [this,buttonNames](Node& node){
        if (gameStartedYes) {
            W4_LOG_DEBUG("click !!!! %s", node.getName().c_str());
            DisableTutorial();
            m_currInteractiveItem = m_bath;
            m_gameUI->changeButtons(buttonNames);
        }
    });
    component.setFailCallback([this]() {addItemsCount(false); m_bath->removeAllComponents<InteractiveItem>(); });
    component.setWinCallback([this](){addItemsCount(true); m_bath->removeAllComponents<InteractiveItem>(); });
    component.setButtonNames("Book", "Izolenta", "Molotok");
}

void KitchenGame::onDestroy() {
    m_bath->removeAllComponents<InteractiveItem>();
    m_toilet->removeAllComponents<InteractiveItem>();
    m_stand->removeAllComponents<InteractiveItem>();
    m_bath = nullptr;
    m_toilet = nullptr;
    m_stand = nullptr;
    m_gameUI = nullptr;
}

void KitchenGame::onWin() {
    if(m_onWinCallback){
        Timer::addTask(1, [this]() -> bool {
            onDestroy();
            AudioManager::instance().playWinSound();
            m_onWinCallback();
            return true;
            });
    }
}
void KitchenGame::onFail() {
    if(m_onFailCallback){
        Timer::addTask(1, [this]() -> bool {
            onDestroy();
            //AudioManager::instance().playFailSound();
            m_ui->finalMenu();
            m_ui->updateSize();
            m_onFailCallback();
            return true;
            });
    }
}

void KitchenGame::setOnWinCallback(std::function<void()> onWinCallback) {
    m_onWinCallback = onWinCallback;

}
void KitchenGame::setOnFailCallback(std::function<void()> onFailCallback){
    m_onFailCallback = onFailCallback;
}

void KitchenGame::addItemsCount(bool win) {
    win ? winItemsCount++ : loseItemsCount++;
    if (win) {
        AudioManager::instance().playMaleHappySound();
    }
    else {
        AudioManager::instance().playMaleSadSound();
    }

    if (winItemsCount >= 3){
        onWin();
    }
    else if (loseItemsCount > 0) {
        onFail();
    }
    toturial = TutorialStates::UnFocus;
    m_gameUI->startFadeAnim(false);
}

void KitchenGame::updateSize() {
    if (m_gameUI) {
        m_gameUI->updateSize();
    }

    if (m_ui) {
        m_ui->updateSize();
    }
}

void KitchenGame::CreateGameUI() {

    if (!m_ui) {
        m_ui = make::sptr<GameDomUi>(0);
        m_ui->init(true);
    }

    auto logoImage = m_ui->getItem("logo")->getWidget();
    logoImage->setVisible(true);
    logoImage->onTap([this]() {
        callCTA();
        AudioManager::instance().playClickSound();
        });

    auto installStaticButton = m_ui->getItem("install")->getWidget();
    installStaticButton->setVisible(true);
    installStaticButton->onTap([this]() {
        callCTA();
        AudioManager::instance().playClickSound();
        });


    auto nextButton = m_ui->getItem("start")->getWidget();

    auto soundOn = m_ui->getItem("soundOn");
    soundOn->setClickCallback([this]() {
        m_ui->setVisible("soundOff", true);
        m_ui->setVisible("soundOn", false);
        m_ui->getItem("soundOn")->setClickable(false);
        m_ui->getItem("soundOff")->setClickable(true);
        W4_LOG_ERROR("on");
        AudioManager::instance().playClickSound();
        mute(true);
        });

    auto soundOff = m_ui->getItem("soundOff");
    m_ui->setVisible("soundOff", false);
    soundOff->setClickable(false);
    soundOff->setClickCallback([this]() {
        m_ui->setVisible("soundOff", false);
        m_ui->setVisible("soundOn", true);
        m_ui->getItem("soundOn")->setClickable(true);
        m_ui->getItem("soundOff")->setClickable(false);
        mute(false);
        AudioManager::instance().playClickSound();
        });

    if (!gameStartedYes) {

        nextButton->setVisible(true);
        nextButton->onTap([this, nextButton]() {
            gameStartedYes = true;
            toturial = TutorialStates::UnFocus;
            nextButton->setVisible(false);
            AudioManager::instance().playClickSound();
            });

    }
    else {
        nextButton->setVisible(false);
    }
}

void KitchenGame::callCTA() {
    W4_LOG_DEBUG("CTA");
    w4::network::ads::CTA();
}