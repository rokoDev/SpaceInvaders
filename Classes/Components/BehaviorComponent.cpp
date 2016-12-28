//
//  BehaviorComponent.cpp
//  SpaceInvaders
//
//  Created by roko on 12/13/16.
//
//

#include "BehaviorComponent.hpp"
#include "ComponentDefinitions.hpp"

USING_NS_CC;

BehaviorComponent::BehaviorComponent():
m_behavior(nullptr)
{
}

BehaviorComponent::~BehaviorComponent()
{
}

bool BehaviorComponent::init()
{
    this->setName(kBehaviorKeyStr);
    return true;
}

void BehaviorComponent::update(float delta)
{
    if (_owner && m_behavior) {
        m_behavior(_owner, delta);
    }
}

BehaviorComponent* BehaviorComponent::create()
{
    BehaviorComponent * ret = new (std::nothrow) BehaviorComponent();
    
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

BehaviorComponent* BehaviorComponent::create(const BehaviorFunction behavior)
{
    BehaviorComponent * ret = BehaviorComponent::create();
    
    if (ret) {
        ret->setBehavior(behavior);
    }
    
    return ret;
}

void BehaviorComponent::setValue(cocos2d::Node * pComponentContainerNode, const BehaviorFunction behavior)
{
    if (pComponentContainerNode) {
        auto pComponent = static_cast<BehaviorComponent *>(pComponentContainerNode->getComponent(kBehaviorKeyStr));
        if (pComponent) {
            pComponent->setBehavior(behavior);
        }
    }
}

