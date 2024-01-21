#pragma once

#include "W4Framework.h"

W4_USE_UNSTRICT_INTERFACE

class Explosion {
    private:
        unsigned int ID;
        sptr<Mesh> mesh;
        sptr<w4::resources::MaterialInst> mi;
        vec3 position;
        vec3 size;
        int currentFrame;
        float startTime;
        bool complete;
        sptr<Node> rootNode;

    public:
        void Create(const vec3 &position, vec3 size, sptr<Texture> explosionTexture, sptr<Material> animatedMaterial, sptr<Node> rootNode);
        void Animate();
        void Destroy();
        sptr<Mesh> getMesh();
        vec3 getPosition();
        unsigned int getID();
        bool isComplete();
};

void ResetExplosionSystem();
void AddExplosion(const vec3 &position, vec3 size, sptr<Texture> explosionTexture, sptr<Material> animatedMaterial, sptr<Node> rootNode);
void ProcessExplosions();
