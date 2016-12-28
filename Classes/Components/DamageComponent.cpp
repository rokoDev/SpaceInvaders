//
//  DamageComponent.cpp
//  SpaceInvaders
//
//  Created by roko on 12/19/16.
//
//

#include "DamageComponent.hpp"
#include "ComponentDefinitions.hpp"

USING_NS_CC;

DamageComponent::DamageComponent():
m_damage(0.f)
{
}

DamageComponent::~DamageComponent()
{
}

bool DamageComponent::init()
{
    this->setName(kDamageKeyStr);
    return true;
}

void DamageComponent::update(float delta)
{
}

DamageComponent* DamageComponent::create()
{
    DamageComponent * ret = new (std::nothrow) DamageComponent();
    
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

DamageComponent* DamageComponent::create(const float damage)
{
    DamageComponent * ret = DamageComponent::create();
    
    if (ret) {
        ret->setDamage(damage);
    }
    
    return ret;
}

void DamageComponent::setValue(cocos2d::Node * pComponentContainerNode, const float damage)
{
    if (pComponentContainerNode) {
        auto pComponent = static_cast<DamageComponent *>(pComponentContainerNode->getComponent(kDamageKeyStr));
        if (pComponent) {
            pComponent->setDamage(damage);
        }
    }
}

float DamageComponent::getValue(cocos2d::Node * pComponentContainerNode)
{
    float ret = 0.f;
    if (pComponentContainerNode) {
        auto pComponent = static_cast<DamageComponent *>(pComponentContainerNode->getComponent(kDamageKeyStr));
        if (pComponent) {
            ret = pComponent->getDamage();
        }
    }
    return ret;
}

