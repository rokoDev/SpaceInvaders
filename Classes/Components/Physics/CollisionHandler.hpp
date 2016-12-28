//
//  CollisionHandler.hpp
//  SpaceInvaders
//
//  Created by roko on 12/19/16.
//
//

#ifndef CollisionHandler_hpp
#define CollisionHandler_hpp

#include "PhysicsDefinitions.hpp"

class CollisionHandler:
public PhysicsProtocol
{
private:
    struct Impl;
    std::unique_ptr<Impl> m_pImpl;
    
public:
    ~CollisionHandler();
    CollisionHandler();
    CollisionHandler(const CollisionHandler & other);
    CollisionHandler & operator=(const CollisionHandler & other);
    CollisionHandler(CollisionHandler && other);
    CollisionHandler & operator=(CollisionHandler && other);
    
    void setDelegate(CollisionHandlerProtocol * pDelegate);
    CollisionHandlerProtocol * getDelegate() const;
    
#pragma mark PhysicsProtocol
    bool processDeepHitCheck(PhysicsWorldComponent * sender, ColliderComponent * pCollider1, ColliderComponent * pCollider2) override;
    void processCollidersHit(PhysicsWorldComponent * sender, ColliderComponent * pCollider1, ColliderComponent * pCollider2) override;
    void processPhysicsStepEnded(PhysicsWorldComponent * sender) override;
};

#endif /* CollisionHandler_hpp */
