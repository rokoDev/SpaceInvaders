//
//  PhysicsDebugNode.cpp
//  SpaceInvaders
//
//  Created by roko on 12/17/16.
//
//

#include "PhysicsDebugNode.hpp"
#include "PhysicsWorldComponent.hpp"
#include "Grid.hpp"

USING_NS_CC;

PhysicsDebugNode::~PhysicsDebugNode()
{
    
}

PhysicsDebugNode::PhysicsDebugNode(int lineWidth):
DrawNode(lineWidth),
m_pPhysicsWorld(nullptr),
m_gridColor(Color4F::BLUE)
{
    
}

bool PhysicsDebugNode::init()
{
    if (DrawNode::init()) {
        return true;
    }
    return false;
}

PhysicsDebugNode * PhysicsDebugNode::create(int defaultLineWidth)
{
    PhysicsDebugNode* ret = new (std::nothrow) PhysicsDebugNode(defaultLineWidth);
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

void PhysicsDebugNode::setPhysicsWorldComponent(PhysicsWorldComponent * pComponent)
{
    m_pPhysicsWorld = pComponent;
    if (m_pPhysicsWorld) {
        updateGridLines();
    }
}

void PhysicsDebugNode::updateGridLines()
{
    auto gridDim = m_pPhysicsWorld->m_pGrid->m_dim;
    auto cellSize = m_pPhysicsWorld->m_pGrid->m_cellSize;
    cocos2d::Size gridSize(gridDim.w * cellSize.width, gridDim.h * cellSize.height);
    
    //horizontal lines
    for (int i = 0; i <= gridDim.h; ++i) {
        drawLine(Vec2(0.f, i * cellSize.height), Vec2(gridSize.width, i * cellSize.height), m_gridColor);
    }
    
    //vertical lines
    for (int i = 0; i <= gridDim.w; ++i) {
        drawLine(Vec2(i * cellSize.width, 0.f), Vec2(i * cellSize.width, gridSize.height), m_gridColor);
    }
}



