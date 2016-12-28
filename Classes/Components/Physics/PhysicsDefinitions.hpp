//
//  PhysicsDefinitions.hpp
//  SpaceInvaders
//
//  Created by roko on 12/17/16.
//
//

#ifndef PhysicsDefinitions_hpp
#define PhysicsDefinitions_hpp

#include <cstdint>
#include <cstddef>
#include <vector>

using BitMaskType = uint8_t;
using GroupIDType = uint8_t;

struct IntPos {
    union {
        size_t x;
        size_t w;
    };
    union {
        size_t y;
        size_t h;
    };
    
    IntPos(size_t x = 0, size_t y = 0):x(x),y(y){}
    IntPos(IntPos const&) = default;
    IntPos(IntPos&&) = default;
    IntPos& operator=(IntPos const&) = default;
    IntPos& operator=(IntPos &&) = default;
    friend bool operator==(const IntPos & v1, const IntPos & v2)
    {
        return v1.x == v2.x && v1.y == v2.y;
    };
};

class ColliderComponent;
class PhysicsWorldComponent;

struct HitData {
    ColliderComponent * m_pCollider;
    
};

using ColliderResult = std::vector<std::pair<ColliderComponent *, ColliderComponent *>>;

using IntSize = IntPos;

class PhysicsProtocol {
    
public:
    virtual bool processDeepHitCheck(PhysicsWorldComponent * sender, ColliderComponent * pCollider1, ColliderComponent * pCollider2) = 0;
    virtual void processCollidersHit(PhysicsWorldComponent * sender, ColliderComponent * pCollider1, ColliderComponent * pCollider2) = 0;
    virtual void processPhysicsStepEnded(PhysicsWorldComponent * sender) = 0;
};

class CollisionHandlerProtocol {
    
public:
    virtual void physicsStepDidFinish() = 0;
    virtual void invaderBullet_CollidedWith_ManGun(ColliderComponent * pBulletCollider, ColliderComponent * pManGunCollider) = 0;
    virtual void manBullet_CollidedWith_InvaderShip(ColliderComponent * pBulletCollider, ColliderComponent * pInvaderShipCollider) = 0;
    virtual void invaderShip_CollidedWith_ManGun(ColliderComponent * pInvaderShipCollider, ColliderComponent * pManGunCollider) = 0;
};

#endif /* PhysicsDefinitions_hpp */
