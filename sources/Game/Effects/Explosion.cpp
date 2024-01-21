#include "Explosion.h"

using namespace std;

#include <vector>

unsigned int explosions_ID_Generator = 0;

void Explosion::Create(const vec3 &position, vec3 size, sptr<Texture> explosionTexture, sptr<Material> animatedMaterial, sptr<Node> rootNode) {

    this->ID = explosions_ID_Generator++;
    this->rootNode = rootNode;
    this->position = position;
    this->size = size;
    currentFrame = 0;
    complete = false;
          
    mesh = Mesh::create::plane(vec2(1,1));

    // Create Material Instance:

    mi = animatedMaterial->createInstance();
    mi->setBlendFunc(BlendFactor::SRC_ALPHA, BlendFactor::ONE_MINUS_SRC_ALPHA);
    mi->enableBlending(true);
    mi->setParam("texture0", explosionTexture);
    mi->setParam("countX", 6.0f);
    mi->setParam("countY", 6.0f);
    mi->setParam("frameNum", (float)currentFrame);
            
    mesh->setMaterialInst(mi);

    mesh->setRenderOrder(6);

    Render::getScreenCamera()->addChild(mesh);

    mesh->setLocalTranslation(position);
    mesh->setLocalScale(size);

    startTime = Render::getElapsedTime();
}

void Explosion::Animate() {

    if (mesh) {

        float dTime = (Render::getElapsedTime() - startTime) * 100.0f;
        currentFrame = (int)dTime;

        if (currentFrame > 35) {
            Destroy();
            complete = true;
        } else mi->setParam("frameNum", (float)currentFrame);
    }
}

void Explosion::Destroy() {
    if (mesh) {
        mesh->getParent()->removeChild(mesh);
        mesh = nullptr;
    }
    mi = nullptr;
}

sptr<Mesh> Explosion::getMesh() {return mesh;}

unsigned int Explosion::getID() {return ID;}

vec3 Explosion::getPosition() {return position;}

bool Explosion::isComplete() {return complete;}

// Explosions List Functional:

vector<Explosion> explosions;

void ResetExplosionSystem() {

    explosions_ID_Generator = 0;

    int numExplosions = (int)explosions.size();
    if (numExplosions > 0) {

        for (int i = 0; i < numExplosions; i++) {
            explosions[i].Destroy();
        }

        explosions.clear();
    }
}

void AddExplosion(const vec3 &position, vec3 size, sptr<Texture> explosionTexture, sptr<Material> animatedMaterial, sptr<Node> rootNode) {

    Explosion explosion;
    explosion.Create(position, size, explosionTexture, animatedMaterial, rootNode);
    explosions.push_back(explosion);
}

void ProcessExplosions() {

    int numExplosions = (int)explosions.size();
    if (numExplosions > 0) {

        vector<unsigned int> erasingIDs;

        for (int i = 0; i < numExplosions; i++) {

            Explosion *exp = &(explosions[i]);
            exp->Animate();

            if (exp->isComplete()) erasingIDs.push_back(exp->getID());

        }

        int numErasingIDs = (int)erasingIDs.size();
        if (numErasingIDs > 0) {

            for (int i = 0; i < numErasingIDs; i++) {

                unsigned int eID = erasingIDs[i];

                for (int j = 0; j < (int)explosions.size(); j++) {

                    Explosion *e = &(explosions[j]);

                    if (e->getID() == eID) {
                        explosions.erase(explosions.begin() + j);
                        break;
                    }

                }

            }

            erasingIDs.clear();

        }

    }

}
