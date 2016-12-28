//
//  VelocityComponent.cpp
//  SpaceInvaders
//
//  Created by roko on 12/12/16.
//
//

#include "VelocityComponent.hpp"
#include "ComponentDefinitions.hpp"

USING_NS_CC;

VelocityComponent::VelocityComponent():
m_velocity(Vec2::ZERO)
{
}

VelocityComponent::~VelocityComponent()
{
}

bool VelocityComponent::init()
{
    this->setName(kVelocityKeyStr);
    return true;
}

void VelocityComponent::update(float delta)
{
}

VelocityComponent* VelocityComponent::create()
{
    VelocityComponent * ret = new (std::nothrow) VelocityComponent();
    
    if (ret && ret->init())
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    
    return ret;
}

VelocityComponent* VelocityComponent::create(const cocos2d::Vec2 & velocity)
{
    VelocityComponent * ret = VelocityComponent::create();
    
    if (ret) {
        ret->setVelocity(velocity);
    }
    
    return ret;
}

void VelocityComponent::setValue(cocos2d::Node * pComponentContainerNode, const cocos2d::Vec2 & velocity)
{
    if (pComponentContainerNode) {
        auto pComponent = static_cast<VelocityComponent *>(pComponentContainerNode->getComponent(kVelocityKeyStr));
        if (pComponent) {
            pComponent->setVelocity(velocity);
        }
    }
}


