#include "InteractiveBath.h"
#include "Settings/Settings.h"
#include "Settings/ResourceLibary.h"

void InteractiveBath::onFail2Animation() {
    args->m_node->removeChild("Bath");
    args->m_node->setLocalScale(vec3(1, 1, 1));

    auto mesh = ResourceLibary::instance().getModel("Bath_broken_2")->getFirstRoot();
    mesh->setName("Bath");
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

    args->m_node->setLocalScale(vec3(1, 1, 1) * Settings::instance().getFloat("Bath_broken_2_Scale"));
    args->m_node->setLocalRotation(DEG2RAD * Settings::instance().getVec3("Bath_broken_2_Rotation"));
    args->m_node->setLocalTranslation(Settings::instance().getVec3("Bath_broken_2_Translation") + vec3(0,
        Settings::instance().getFloat("CameraHeight"), Settings::instance().getFloat("CameraWidth")));

    AudioManager::instance().playRepairFailSound();

    auto cum = Render::getScreenCamera();

    vec2 pos = cum->getScreenNormalizedFromWorldPoint(args->m_node->getWorldTranslation());

    AddExplosion(vec3(pos.x, pos.y, 1.0f) + Settings::instance().getVec3("ExplosionBathTranslation"), Settings::instance().getVec3("ExplosionBathScale"), ResourceLibary::instance().getTexture("Explosion"),
        ResourceLibary::instance().getMaterial("Animated"), args->m_node->getParent());
}

void InteractiveBath::onFailAnimation() {
    auto mesh = ResourceLibary::instance().getModel("Duck")->getFirstRoot();
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

    mesh->setLocalScale(vec3(1, 1, 1) * Settings::instance().getFloat("DuckScale"));
    mesh->setLocalRotation(DEG2RAD * Settings::instance().getVec3("DuckRotation"));
    mesh->setLocalTranslation(Settings::instance().getVec3("DuckTranslation") + vec3(0,
        Settings::instance().getFloat("CameraHeight"), Settings::instance().getFloat("CameraWidth")));

    AudioManager::instance().playRepairFailSound();

    auto cum = Render::getScreenCamera();

    vec2 pos = cum->getScreenNormalizedFromWorldPoint(args->m_node->getWorldTranslation());

    AddExplosion(vec3(pos.x, pos.y, 1.0f) + Settings::instance().getVec3("ExplosionBathTranslation"), Settings::instance().getVec3("ExplosionBathScale"), ResourceLibary::instance().getTexture("Explosion"),
        ResourceLibary::instance().getMaterial("Animated"), args->m_node->getParent());
}

void InteractiveBath::onWinAnimation() {
    args->m_node->removeChild("Bath");
    args->m_node->setLocalScale(vec3(1, 1, 1));

    auto mesh = ResourceLibary::instance().getModel("Bath")->getFirstRoot();
    mesh->setName("Bath");
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

    mesh->setEnabled(true);

    args->m_node->setLocalScale(vec3(1, 1, 1) * Settings::instance().getFloat("BathScale"));
    args->m_node->setLocalRotation(DEG2RAD * Settings::instance().getVec3("BathRotation"));
    args->m_node->setLocalTranslation(Settings::instance().getVec3("BathTranslation") + vec3(0,
        Settings::instance().getFloat("CameraHeight"), Settings::instance().getFloat("CameraWidth")));
    //------------------------------
    auto bookMesh = ResourceLibary::instance().getModel("Books")->getFirstRoot();
    bookMesh->setName("Books");
    auto bookMat = ResourceLibary::instance().getMaterial("Default")->createInstance();
    bookMat->setTexture(TextureId::TEXTURE_0, ResourceLibary::instance().getTexture("Color_2"));
    bookMat->setParam("light_params", Settings::instance().getVec3("ShadowIntensity"));
    bookMat->setParam("shinessParam", Settings::instance().getFloat("LightShiness"));
    bookMesh->traversalTyped<VisibleNode>([&](cref<VisibleNode> node) {
        node->setMaterialInst(bookMat);
        });

    mesh->addChild(bookMesh);

    bookMesh->setLocalRotation(Rotator(0, 0, 0));
    bookMesh->setLocalTranslation(vec3(0, 0, 0));
    bookMesh->setLocalScale(vec3(1, 1, 1));

    bookMesh->setLocalScale(vec3(1, 1, 1) * Settings::instance().getFloat("BooksScale"));
    bookMesh->setLocalRotation(DEG2RAD * Settings::instance().getVec3("BooksRotation"));
    bookMesh->setLocalTranslation(Settings::instance().getVec3("BooksTranslation") + vec3(0,
        Settings::instance().getFloat("CameraHeight"), Settings::instance().getFloat("CameraWidth")));

    AudioManager::instance().playRepairSuccessSound();

    auto cum = Render::getScreenCamera();

    vec2 pos = cum->getScreenNormalizedFromWorldPoint(args->m_node->getWorldTranslation());

    AddExplosion(vec3(pos.x, pos.y, 1.0f) + Settings::instance().getVec3("ExplosionBathTranslation"), Settings::instance().getVec3("ExplosionBathScale"), ResourceLibary::instance().getTexture("Explosion"),
        ResourceLibary::instance().getMaterial("Animated"), args->m_node->getParent());
}

void InteractiveBath::onUpdateAnimation(float dt) {

}

void InteractiveBath::setup(sptr<InteractiveArgs> args) {
    this->args = std::dynamic_pointer_cast<BathArgs>(args);
}
