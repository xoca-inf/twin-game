#pragma once
#include "W4Framework.h"
#include "Audio/AudioManager.h"
#include "Game/Effects/Explosion.h"

W4_USE_UNSTRICT_INTERFACE

class InteractiveArgs{
public:
    sptr<Node> m_node;
    sptr<Mesh> m_mesh;
    virtual ~InteractiveArgs(){};
};

class IInteractive{
public:
    virtual void setup(sptr<InteractiveArgs> args) = 0;
    virtual void onWinAnimation() = 0;
    virtual void onFailAnimation() = 0;
    virtual void onFail2Animation() = 0;
    virtual void onUpdateAnimation(float dt) = 0;
};