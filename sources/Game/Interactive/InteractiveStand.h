#pragma once
#include "W4Framework.h"
#include "IInteractive.h"

W4_USE_UNSTRICT_INTERFACE

class StandArgs: public InteractiveArgs{
public:
    ~StandArgs(){};
};


class InteractiveStand: public IInteractive {
public:
    void setup(sptr<InteractiveArgs> args) override;
    void onFail2Animation() override;
    void onFailAnimation() override;
    void onWinAnimation() override;
    void onUpdateAnimation(float dt) override;
private:
    sptr<StandArgs> args;
};
