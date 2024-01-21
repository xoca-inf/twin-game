#include "InteractiveToilet.h"
#include "Settings/Settings.h"
#include "Settings/ResourceLibary.h"

void InteractiveToilet::onFail2Animation() {
    args->m_node->removeChild("Toilet");
    args->m_node->setLocalScale(vec3(1, 1, 1));

    auto mesh = ResourceLibary::instance().getModel("Toilet_broken_2")->getFirstRoot();
    mesh->setName("Toilet");
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

    args->m_node->setLocalScale(Settings::instance().getVec3("Toilet_broken_2_Scale"));
    args->m_node->setLocalRotation(DEG2RAD * Settings::instance().getVec3("Toilet_broken_2_Rotation"));
    args->m_node->setLocalTranslation(Settings::instance().getVec3("Toilet_broken_2_Translation") + vec3(0,
        Settings::instance().getFloat("CameraHeight"), Settings::instance().getFloat("CameraWidth")));

    AudioManager::instance().playRepairFailSound();

    auto cum = Render::getScreenCamera();

    vec2 pos = cum->getScreenNormalizedFromWorldPoint(args->m_node->getWorldTranslation());

    AddExplosion(vec3(pos.x, pos.y, 1.0f) + Settings::instance().getVec3("ExplosionToiletTranslation"), Settings::instance().getVec3("ExplosionToiletScale"), ResourceLibary::instance().getTexture("Explosion"),
        ResourceLibary::instance().getMaterial("Animated"), args->m_node->getParent());
}

void InteractiveToilet::onFailAnimation() {
    AudioManager::instance().playDroppingSound();

    auto cum = Render::getScreenCamera();

    vec2 pos = cum->getScreenNormalizedFromWorldPoint(args->m_node->getWorldTranslation());

    AddExplosion(vec3(pos.x, pos.y, 1.0f) + Settings::instance().getVec3("ExplosionToiletTranslation"), Settings::instance().getVec3("ExplosionToiletScale"), ResourceLibary::instance().getTexture("Explosion"),
        ResourceLibary::instance().getMaterial("Animated"), args->m_node->getParent());
}

void InteractiveToilet::onWinAnimation() {
    args->m_node->removeChild("Toilet");
    args->m_node->setLocalScale(vec3(1, 1, 1));

    auto mesh = ResourceLibary::instance().getModel("Toilet")->getFirstRoot();
    mesh->setName("Toilet");
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

    args->m_node->setLocalScale(vec3(1, 1, 1) * Settings::instance().getFloat("ToiletScale"));
    args->m_node->setLocalRotation(DEG2RAD * Settings::instance().getVec3("ToiletRotation"));
    args->m_node->setLocalTranslation(Settings::instance().getVec3("ToiletTranslation") + vec3(0,
        Settings::instance().getFloat("CameraHeight"), Settings::instance().getFloat("CameraWidth")));

    auto cum = Render::getScreenCamera();

    vec2 pos = cum->getScreenNormalizedFromWorldPoint(args->m_node->getWorldTranslation());

    AddExplosion(vec3(pos.x, pos.y, 1.0f) + Settings::instance().getVec3("ExplosionToiletTranslation"), Settings::instance().getVec3("ExplosionToiletScale"), ResourceLibary::instance().getTexture("Explosion"),
        ResourceLibary::instance().getMaterial("Animated"), args->m_node->getParent());
}

void InteractiveToilet::onUpdateAnimation(float dt) {

}

void InteractiveToilet::setup(sptr<InteractiveArgs> args) {
    this->args = std::dynamic_pointer_cast<ToiletArgs>(args);
}
