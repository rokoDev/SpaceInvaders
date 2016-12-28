//
//  PhysicsWorldComponent.hpp
//  SpaceInvaders
//
//  Created by roko on 12/16/16.
//
//

#ifndef PhysicsWorldComponent_hpp
#define PhysicsWorldComponent_hpp

#include "cocos2d.h"
#include "PhysicsDefinitions.hpp"

class ColliderComponent;
class Grid;
class PhysicsWorldComponent;
class PhysicsDebugNode;

class PhysicsWorldComponent:
public cocos2d::Component {
    friend class Grid;
    friend class PhysicsDebugNode;
private:
    std::unique_ptr<Grid> m_pGrid;
    PhysicsProtocol * m_pDelegate;
    PhysicsDebugNode * m_pDebugDrawNode;
    
    void objectsCollided(ColliderComponent * pCollider1, ColliderComponent * pCollider2);
    
    PhysicsDebugNode * getDebugDrawNode() const { return m_pDebugDrawNode; }
    void setDebugDrawNode(PhysicsDebugNode * pDebugNode);
    void addDebugDrawNodeAsChild();
    void physicsStepCompleted();
    
public:
    PhysicsProtocol * getDelegate() const { return m_pDelegate; }
    void setDelegate(PhysicsProtocol * pDelegate) { m_pDelegate = pDelegate; }
    static PhysicsWorldComponent* create(const IntPos dim, const cocos2d::Size & cellSize, const size_t supposedColliderCount = 100);
    
    ~PhysicsWorldComponent();
    
    bool init() override;
    
    void update(float delta) override;
    
    void onEnter() override;
    void onExit() override;
    
    void addCollider(ColliderComponent * pCollider);
    void removeCollider(ColliderComponent * pCollider);
    
    void setDebugDraw(bool isDebugMode);
    
    bool hitCheck(ColliderComponent * pCollider1, ColliderComponent * pCollider2);
    
CC_CONSTRUCTOR_ACCESS:
    PhysicsWorldComponent(const IntPos dim, const cocos2d::Size & cellSize, const size_t supposedColliderCount);
};

#endif /* PhysicsWorldComponent_hpp */
