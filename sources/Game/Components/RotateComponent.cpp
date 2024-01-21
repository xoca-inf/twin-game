#include "RotateComponent.h"

void RotateComponent::initialize(const variant::Variant &data) {
    IComponent::initialize(data);

    initializeHandlers();
    m_initRotation = this->getOwner().getWorldRotation().euler();
    m_initLightRotation = Render::getPass(0)->getDirectionalLight()->getDirection();
}

void RotateComponent::update(float dt) {
    IComponent::update(dt);
}

void RotateComponent::finalize() {

    if (m_touchBeginHandler)
    {
        m_touchBeginHandler->unsubscribe();
        m_touchBeginHandler = nullptr;
    }
    if (m_touchEndHandler)
    {
        m_touchEndHandler->unsubscribe();
        m_touchEndHandler = nullptr;
    }
    if (m_touchMoveHandler)
    {
        m_touchMoveHandler->unsubscribe();
        m_touchMoveHandler = nullptr;
    }

    IComponent::finalize();
}

RotateComponent::~RotateComponent() {

}

void RotateComponent::setup() {

}


void RotateComponent::onTouchBegin(const Touch::Begin& evt)
{
    m_lastTouchPos = ivec2(evt.point.x, evt.point.y);
}

void RotateComponent::onTouchMove(const Touch::Move& evt)
{
    auto deltaAngle = -(evt.point.x - m_lastTouchPos.x) * m_sensitivity;
    auto currAngle = this->getOwner().getWorldRotation().euler().y;

    this->getOwner().setWorldRotation(vec3(0, std::clamp(currAngle + deltaAngle * DEG2RAD, m_minAngle * DEG2RAD, m_maxAngle * DEG2RAD),0));

    m_lastTouchPos = ivec2(evt.point.x, evt.point.y);
}

void RotateComponent::onTouchEnd(const Touch::End& evt)
{

}

void RotateComponent::initializeHandlers() {
    m_touchBeginHandler = Touch::Begin::subscribe(std::bind(&RotateComponent::onTouchBegin, this, std::placeholders::_1));
    m_touchEndHandler = Touch::End::subscribe(std::bind(&RotateComponent::onTouchEnd, this, std::placeholders::_1));
    m_touchMoveHandler = Touch::Move::subscribe(std::bind(&RotateComponent::onTouchMove, this, std::placeholders::_1));
}
