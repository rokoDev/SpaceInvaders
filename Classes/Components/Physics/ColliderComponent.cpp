//
//  ColliderComponent.cpp
//  SpaceInvaders
//
//  Created by roko on 12/15/16.
//
//

#include "ColliderComponent.hpp"
#include "ComponentDefinitions.hpp"
#include "PhysicsWorldComponent.hpp"

USING_NS_CC;

ColliderComponent::ColliderComponent():
m_bitMask(0),
m_groupID(0),
m_leftBottomCellCoord({0, 0}),
m_topRightCellCoord({0, 0}),
m_gridID(0),
m_ownerTag(-1)
{
}

ColliderComponent::~ColliderComponent()
{
}

cocos2d::Rect ColliderComponent::getRect() const
{
    if (_owner) {
        Size s = _owner->getContentSize();
        Vec2 p = _owner->getPosition()-Vec2(s.width*_owner->getAnchorPoint().x, s.height*_owner->getAnchorPoint().y);
        return cocos2d::Rect(p, s);
    }
    return Rect::ZERO;
}

bool ColliderComponent::init()
{
    this->setName(kColliderKeyStr);
    return true;
}

void ColliderComponent::update(float delta)
{
}

ColliderComponent* ColliderComponent::create()
{
    ColliderComponent * ret = new (std::nothrow) ColliderComponent();
    
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

ColliderComponent* ColliderComponent::create(const BitMaskType bitMask, const GroupIDType groupID)
{
    ColliderComponent * ret = ColliderComponent::create();
    
    if (ret) {
        ret->setBitMask(bitMask);
        ret->setGroupID(groupID);
    }
    
    return ret;
}

void ColliderComponent::setValueAll(cocos2d::Node * pComponentContainerNode, const BitMaskType bitMask, const GroupIDType groupID)
{
    auto pComponent = static_cast<ColliderComponent *>(pComponentContainerNode->getComponent(kColliderKeyStr));
    if (pComponent) {
        pComponent->setGroupID(groupID);
        pComponent->setBitMask(bitMask);
    }
}

void ColliderComponent::setValueBitMask(cocos2d::Node * pComponentContainerNode, const BitMaskType bitMask)
{
    auto pComponent = static_cast<ColliderComponent *>(pComponentContainerNode->getComponent(kColliderKeyStr));
    if (pComponent) {
        pComponent->setBitMask(bitMask);
    }
}

void ColliderComponent::setValueGroupID(cocos2d::Node * pComponentContainerNode, const GroupIDType groupID)
{
    auto pComponent = static_cast<ColliderComponent *>(pComponentContainerNode->getComponent(kColliderKeyStr));
    if (pComponent) {
        pComponent->setGroupID(groupID);
    }
}

void ColliderComponent::onEnter()
{
    Component::onEnter();
    auto physicsWorld = static_cast<PhysicsWorldComponent *>(_owner->getParent()->getComponent(kPhysicsWorldKeyStr));
    if (physicsWorld) {
        physicsWorld->addCollider(this);
    }
}

void ColliderComponent::onExit()
{
    Component::onExit();
    auto physicsWorld = static_cast<PhysicsWorldComponent *>(_owner->getParent()->getComponent(kPhysicsWorldKeyStr));
    if (physicsWorld) {
        physicsWorld->removeCollider(this);
    }
}

