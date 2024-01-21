#include "InteractiveStand.h"
#include "Settings/Settings.h"
#include "Settings/ResourceLibary.h"

void InteractiveStand::onFail2Animation() {
    args->m_node->removeChild("Stand");
    args->m_node->setLocalScale(vec3(1, 1, 1));

    auto mesh = ResourceLibary::instance().getModel("Stand_broken_2")->getFirstRoot();
    mesh->setName("Stand");
    auto mat = ResourceLibary::instance().getMaterial("Default")->createInstance();
    mat->setTexture(TextureId::TEXTURE_0, ResourceLibary::instance().getTexture("Color_2"));
    mat->setParam("light_params", Settings::instance().getVec3("ShadowIntensity"));
    mat->setParam("shinessParam", Settings::instance().getFloat("LightShiness"));
    mesh->traversalTyped<VisibleNode>([&](cref<VisibleNode> node) {
        node->setMaterialInst(mat);
        });

    args->m_node->addChild(mesh);

    mesh->setLocalRotation(Rotator(0, 0, 0));
    mesh->setLocalTranslation(vec3(0, 0, 0));
    mesh->setLocalScale(vec3(1, 1, 1));

    args->m_node->setLocalScale(vec3(1, 1, 1) * Settings::instance().getFloat("Stand_broken_2_Scale"));
    args->m_node->setLocalRotation(DEG2RAD * Settings::instance().getVec3("Stand_broken_2_Rotation"));
    args->m_node->setLocalTranslation(Settings::instance().getVec3("Stand_broken_2_Translation") + vec3(0,
        Settings::instance().getFloat("CameraHeight"), Settings::instance().getFloat("CameraWidth")));

    AudioManager::instance().playRepairFailSound();

    auto cum = Render::getScreenCamera();

    vec2 pos = cum->getScreenNormalizedFromWorldPoint(args->m_node->getWorldTranslation());

    AddExplosion(vec3(pos.x, pos.y, 1.0f) + Settings::instance().getVec3("ExplosionStandTranslation"), Settings::instance().getVec3("ExplosionStandScale"), ResourceLibary::instance().getTexture("Explosion"),
        ResourceLibary::instance().getMaterial("Animated"), args->m_node->getParent());
}

void InteractiveStand::onFailAnimation() {
    auto mesh = ResourceLibary::instance().getModel("Vantuz")->getFirstRoot();
    mesh->setName("Stand");
    auto mat = ResourceLibary::instance().getMaterial("Default")->createInstance();
    mat->setTexture(TextureId::TEXTURE_0, ResourceLibary::instance().getTexture("Color_2"));
    mat->setParam("light_params", Settings::instance().getVec3("ShadowIntensity"));
    mat->setParam("shinessParam", Settings::instance().getFloat("LightShiness"));
    mesh->traversalTyped<VisibleNode>([&](cref<VisibleNode> node) {
        node->setMaterialInst(mat);
        });

    args->m_node->addChild(mesh);

    mesh->setLocalRotation(Rotator(0, 0, 0));
    mesh->setLocalTranslation(vec3(0, 0, 0));
    mesh->setLocalScale(vec3(1, 1, 1));

    mesh->setLocalScale(vec3(1, 1, 1) * Settings::instance().getFloat("VantuzScale"));
    mesh->setLocalRotation(DEG2RAD * Settings::instance().getVec3("VantuzRotation"));
    mesh->setLocalTranslation(Settings::instance().getVec3("VantuzTranslation") + vec3(0,
        Settings::instance().getFloat("CameraHeight"), Settings::instance().getFloat("CameraWidth")));


    AudioManager::instance().playRepairFailSound();

    auto cum = Render::getScreenCamera();

    vec2 pos = cum->getScreenNormalizedFromWorldPoint(args->m_node->getWorldTranslation());

    AddExplosion(vec3(pos.x, pos.y, 1.0f) + Settings::instance().getVec3("ExplosionStandTranslation"), Settings::instance().getVec3("ExplosionStandScale"), ResourceLibary::instance().getTexture("Explosion"),
        ResourceLibary::instance().getMaterial("Animated"), args->m_node->getParent());
}

void InteractiveStand::onWinAnimation() {
    args->m_node->removeChild("Stand");
    args->m_node->setLocalScale(vec3(1, 1, 1));

    auto mesh = ResourceLibary::instance().getModel("Stand")->getFirstRoot();
    mesh->setName("Stand");
    auto mat = ResourceLibary::instance().getMaterial("Default")->createInstance();
    mat->setTexture(TextureId::TEXTURE_0, ResourceLibary::instance().getTexture("Color_2"));
    mat->setParam("light_params", Settings::instance().getVec3("ShadowIntensity"));
    mat->setParam("shinessParam", Settings::instance().getFloat("LightShiness"));
    mesh->traversalTyped<VisibleNode>([&](cref<VisibleNode> node) {
        node->setMaterialInst(mat);
        });

    args->m_node->addChild(mesh);

    mesh->setLocalRotation(Rotator(0, 0, 0));
    mesh->setLocalTranslation(vec3(0, 0, 0));
    mesh->setLocalScale(vec3(1, 1, 1));

    args->m_node->setLocalScale(vec3(1, 1, 1) * Settings::instance().getFloat("StandScale"));
    args->m_node->setLocalRotation(DEG2RAD * Settings::instance().getVec3("StandRotation"));
    args->m_node->setLocalTranslation(Settings::instance().getVec3("StandTranslation") + vec3(0,
        Settings::instance().getFloat("CameraHeight"), Settings::instance().getFloat("CameraWidth")));

    AudioManager::instance().playRepairSuccessSound();

    auto cum = Render::getScreenCamera();

    vec2 pos = cum->getScreenNormalizedFromWorldPoint(args->m_node->getWorldTranslation());

    AddExplosion(vec3(pos.x, pos.y, 1.0f) + Settings::instance().getVec3("ExplosionStandTranslation"), Settings::instance().getVec3("ExplosionStandScale"), ResourceLibary::instance().getTexture("Explosion"),
        ResourceLibary::instance().getMaterial("Animated"), args->m_node->getParent());
}

void InteractiveStand::onUpdateAnimation(float dt) {

}

void InteractiveStand::setup(sptr<InteractiveArgs> args) {
    this->args = std::dynamic_pointer_cast<StandArgs>(args);
}
