#pragma once
#include "W4Framework.h"

W4_USE_UNSTRICT_INTERFACE

class RotateComponent : public IComponent{
W4_COMPONENT(RotateComponent, IComponent)
public:
    RotateComponent(CloneTag, const RotateComponent& from, Node& owner)
            : Super(CloneTag{}, from, owner)
    {
    }

    void initialize(const variant::Variant& data) override;
    void update(float dt) override;
    void finalize() override;
    ~RotateComponent() override;

    void setup();

private:

    float m_sensitivity = 0.1f;
    float m_minAngle = 0;
    float m_maxAngle = 90;
    vec3 m_initRotation;
    ivec2 m_startTouchPos;
    ivec2 m_lastTouchPos;
    vec3 m_initLightRotation;

    void initializeHandlers();
    void onTouchBegin(const Touch::Begin& evt);
    void onTouchEnd(const Touch::End& evt);
    void onTouchMove(const Touch::Move& evt);

    sptr<event::Touch::Begin::Handle> m_touchBeginHandler;
    sptr<event::Touch::End::Handle> m_touchEndHandler;
    sptr<event::Touch::Move::Handle> m_touchMoveHandler;

};