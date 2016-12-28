//
//  PhysicsWorldComponent.cpp
//  SpaceInvaders
//
//  Created by roko on 12/16/16.
//
//

#include "PhysicsWorldComponent.hpp"
#include "ComponentDefinitions.hpp"
#include "Grid.hpp"
#include "MakeUnique.h"
#include "PhysicsDebugNode.hpp"
#include "ColliderComponent.hpp"

USING_NS_CC;

PhysicsWorldComponent::PhysicsWorldComponent(const IntPos dim, const cocos2d::Size & cellSize, const size_t supposedColliderCount):
m_pGrid(std::make_unique<Grid>(dim, cellSize, supposedColliderCount)),
m_pDelegate(nullptr),
m_pDebugDrawNode(nullptr)
{
    m_pGrid->setPhysicsWorldComponent(this);
}

PhysicsWorldComponent::~PhysicsWorldComponent()
{
    if (m_pDebugDrawNode) {
        m_pDebugDrawNode->removeFromParent();
        setDebugDrawNode(nullptr);
    }
}

bool PhysicsWorldComponent::init()
{
    this->setName(kPhysicsWorldKeyStr);
    return true;
}

void PhysicsWorldComponent::update(float delta)
{
    m_pGrid->updateCells(delta);
    m_pGrid->collisionCheck();
}

void PhysicsWorldComponent::onEnter()
{
    addDebugDrawNodeAsChild();
}

void PhysicsWorldComponent::onExit()
{
    if (m_pDebugDrawNode) {
        m_pDebugDrawNode->removeFromParent();
    }
}

PhysicsWorldComponent* PhysicsWorldComponent::create(const IntPos dim, const cocos2d::Size & cellSize, const size_t supposedColliderCount)
{
    PhysicsWorldComponent * ret = new (std::nothrow) PhysicsWorldComponent(dim, cellSize, supposedColliderCount);
    
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

void PhysicsWorldComponent::objectsCollided(ColliderComponent * pCollider1, ColliderComponent * pCollider2)
{
    if (m_pDelegate) {
        m_pDelegate->processCollidersHit(this, pCollider1, pCollider2);
    }
}

void PhysicsWorldComponent::setDebugDrawNode(PhysicsDebugNode * pDebugNode)
{
    if (m_pDebugDrawNode != pDebugNode)
    {
        CC_SAFE_RETAIN(pDebugNode);
        CC_SAFE_RELEASE(m_pDebugDrawNode);
        m_pDebugDrawNode = pDebugNode;
    }
}

void PhysicsWorldComponent::addDebugDrawNodeAsChild()
{
    if (_owner && m_pDebugDrawNode && !m_pDebugDrawNode->getParent()) {
        m_pDebugDrawNode->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
        m_pDebugDrawNode->setContentSize(_owner->getContentSize());
        m_pDebugDrawNode->setPosition(Vec2::ZERO);
        _owner->addChild(m_pDebugDrawNode);
    }
}

void PhysicsWorldComponent::physicsStepCompleted()
{
    if (m_pDelegate) {
        m_pDelegate->processPhysicsStepEnded(this);
    }
}

void PhysicsWorldComponent::addCollider(ColliderComponent * pCollider)
{
    m_pGrid->insertColliderComponent(pCollider);
}

void PhysicsWorldComponent::removeCollider(ColliderComponent * pCollider)
{
    m_pGrid->removeColliderComponent(pCollider);
}

void PhysicsWorldComponent::setDebugDraw(bool isDebugMode)
{
    if (isDebugMode) {
        if (!m_pDebugDrawNode) {
            auto pDebugNode = PhysicsDebugNode::create();
            if (pDebugNode) {
                setDebugDrawNode(pDebugNode);
                m_pDebugDrawNode->setPhysicsWorldComponent(this);
                addDebugDrawNodeAsChild();
            }
        }
    }
    else {
        if (m_pDebugDrawNode) {
            m_pDebugDrawNode->removeFromParent();
            setDebugDrawNode(nullptr);
        }
    }
}

bool PhysicsWorldComponent::hitCheck(ColliderComponent * pCollider1, ColliderComponent * pCollider2)
{
    return (pCollider1->m_bitMask & pCollider2->m_bitMask) && (pCollider1->getRect().intersectsRect(pCollider2->getRect())) && m_pDelegate && m_pDelegate->processDeepHitCheck(this, pCollider1, pCollider2);
}

