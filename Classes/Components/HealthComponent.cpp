//
//  HealthComponent.cpp
//  SpaceInvaders
//
//  Created by roko on 12/12/16.
//
//

#include "HealthComponent.hpp"
#include "ComponentDefinitions.hpp"

USING_NS_CC;

HealthComponent::HealthComponent():
m_health(0.f),
m_maxHealth(100.f)
{
}

HealthComponent::~HealthComponent()
{
}

bool HealthComponent::init()
{
    this->setName(kHealthKeyStr);
    return true;
}

void HealthComponent::update(float delta)
{
}

float HealthComponent::setHealth(const float val)
{
    m_health = clampf(val, 0.f, m_maxHealth);
    return m_health;
}

float HealthComponent::addHealth(const float val)
{
    return setHealth(m_health + val);
}

float HealthComponent::subHealth(const float val)
{
    return setHealth(m_health - val);
}

void HealthComponent::setMaxHealth(const float val)
{
    if (val >= 0.f) {
        m_maxHealth = val;
    }
}

HealthComponent* HealthComponent::create()
{
    HealthComponent * ret = new (std::nothrow) HealthComponent();
    
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

HealthComponent* HealthComponent::create(const float health, const float maxHealth)
{
    HealthComponent * ret = HealthComponent::create();
    
    if (ret) {
        ret->setMaxHealth(maxHealth);
        ret->setHealth(health);
    }
    
    return ret;
}

void HealthComponent::setValueAll(cocos2d::Node * pComponentContainerNode, const float health, const float maxHealth)
{
    auto pComponent = static_cast<HealthComponent *>(pComponentContainerNode->getComponent(kHealthKeyStr));
    if (pComponent) {
        pComponent->setMaxHealth(maxHealth);
        pComponent->setHealth(health);
    }
}

float HealthComponent::setHealth(cocos2d::Node * pComponentContainerNode, const float health)
{
    float ret = 0.f;
    auto pComponent = static_cast<HealthComponent *>(pComponentContainerNode->getComponent(kHealthKeyStr));
    if (pComponent) {
        ret = pComponent->setHealth(health);
    }
    return ret;
}

float HealthComponent::addHealth(cocos2d::Node * pComponentContainerNode, const float health)
{
    float ret = 0.f;
    auto pComponent = static_cast<HealthComponent *>(pComponentContainerNode->getComponent(kHealthKeyStr));
    if (pComponent) {
        ret = pComponent->addHealth(health);
    }
    return ret;
}

float HealthComponent::subHealth(cocos2d::Node * pComponentContainerNode, const float health)
{
    float ret = 0.f;
    auto pComponent = static_cast<HealthComponent *>(pComponentContainerNode->getComponent(kHealthKeyStr));
    if (pComponent) {
        ret = pComponent->subHealth(health);
    }
    return ret;
}

void HealthComponent::setValueMaxHealth(cocos2d::Node * pComponentContainerNode, const float maxHealth)
{
    if (pComponentContainerNode) {
        auto pComponent = static_cast<HealthComponent *>(pComponentContainerNode->getComponent(kHealthKeyStr));
        if (pComponent) {
            pComponent->setMaxHealth(maxHealth);
        }
    }
}

