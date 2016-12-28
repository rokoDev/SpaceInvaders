//
//  CollisionHandler.cpp
//  SpaceInvaders
//
//  Created by roko on 12/19/16.
//
//

#include "CollisionHandler.hpp"
#include "MakeUnique.h"
#include <unordered_set>
#include "Helper.hpp"
#include "ColliderComponent.hpp"

USING_NS_CC;

#pragma mark Impl methods
struct CollisionHandler::Impl:
public PhysicsProtocol
{
private:
    CollisionHandlerProtocol * m_pDeletate;
    
public:
    Impl();
    
    void setDelegate(CollisionHandlerProtocol * pDelegate) { m_pDeletate = pDelegate; }
    CollisionHandlerProtocol * getDelegate() const { return m_pDeletate; }
    
    bool processDeepHitCheck(PhysicsWorldComponent * sender, ColliderComponent * pCollider1, ColliderComponent * pCollider2) override;
    void processCollidersHit(PhysicsWorldComponent * sender, ColliderComponent * pCollider1, ColliderComponent * pCollider2) override;
    void processPhysicsStepEnded(PhysicsWorldComponent * sender) override;
    
private:
    bool doesTmpContainCollider(ColliderComponent * pCollider) const;
    
    void invaderBullet_CollidedWith_ManGun(ColliderComponent * pBulletCollider, ColliderComponent * pManGunCollider);
    void manBullet_CollidedWith_InvaderShip(ColliderComponent * pBulletCollider, ColliderComponent * pInvaderShipCollider);
    void invaderShip_CollidedWith_ManGun(ColliderComponent * pInvaderShipCollider, ColliderComponent * pManGunCollider);
    
    typedef void (Impl::*HitCallback)(ColliderComponent * pCollider1, ColliderComponent * pCollider2);
    typedef void (*InvokerHitCallback)(Impl * pContext, HitCallback func, ColliderComponent * pCollider1, ColliderComponent * pCollider2);
    static void directCall(Impl * pContext, HitCallback func, ColliderComponent * pCollider1, ColliderComponent * pCollider2) {
        CALL_MEMBER_FN(pContext, func)(pCollider1, pCollider2);
    }
    
    static void swapCall(Impl * pContext, HitCallback func, ColliderComponent * pCollider1, ColliderComponent * pCollider2) {
        CALL_MEMBER_FN(pContext, func)(pCollider2, pCollider1);
    }
    
    struct HitCallbackObj {
        HitCallbackObj(Impl * pContext = nullptr, HitCallback callback = nullptr, InvokerHitCallback invoker = nullptr): m_pContext(pContext), m_callback(callback), m_invoker(invoker){};
        void operator()(ColliderComponent * pCollider1, ColliderComponent * pCollider2) {
            if (m_pContext && m_callback && m_invoker) {
                m_invoker(m_pContext, m_callback, pCollider1, pCollider2);
            }
        }
    private:
        Impl * m_pContext;
        HitCallback m_callback;
        InvokerHitCallback m_invoker;
        
    };
    
    HitCallbackObj m_hitCallbackMatrix[OBJECT_TAG_COUNT][OBJECT_TAG_COUNT];
};

CollisionHandler::Impl::Impl()
{
    
    m_hitCallbackMatrix[static_cast<int>(ObjectTag::InvaderBullet)][static_cast<int>(ObjectTag::ManGun)] = HitCallbackObj(this, &Impl::invaderBullet_CollidedWith_ManGun, &Impl::directCall);
    m_hitCallbackMatrix[static_cast<int>(ObjectTag::ManGun)][static_cast<int>(ObjectTag::InvaderBullet)] = HitCallbackObj(this, &Impl::invaderBullet_CollidedWith_ManGun, &Impl::swapCall);
    
    m_hitCallbackMatrix[static_cast<int>(ObjectTag::ManBullet)][static_cast<int>(ObjectTag::InvaderShip)] = HitCallbackObj(this, &Impl::manBullet_CollidedWith_InvaderShip, &Impl::directCall);
    m_hitCallbackMatrix[static_cast<int>(ObjectTag::InvaderShip)][static_cast<int>(ObjectTag::ManBullet)] = HitCallbackObj(this, &Impl::manBullet_CollidedWith_InvaderShip, &Impl::swapCall);
    
    m_hitCallbackMatrix[static_cast<int>(ObjectTag::InvaderShip)][static_cast<int>(ObjectTag::ManGun)] = HitCallbackObj(this, &Impl::invaderShip_CollidedWith_ManGun, &Impl::directCall);
    m_hitCallbackMatrix[static_cast<int>(ObjectTag::ManGun)][static_cast<int>(ObjectTag::InvaderShip)] = HitCallbackObj(this, &Impl::invaderShip_CollidedWith_ManGun, &Impl::swapCall);
}

bool CollisionHandler::Impl::processDeepHitCheck(PhysicsWorldComponent * sender, ColliderComponent * pCollider1, ColliderComponent * pCollider2)
{
    return true;
}

void CollisionHandler::Impl::processCollidersHit(PhysicsWorldComponent * sender, ColliderComponent * pCollider1, ColliderComponent * pCollider2)
{
    CCASSERT((pCollider1->getOwnerTag() >= 0) && (pCollider1->getOwnerTag() <= static_cast<int>(ObjectTag::TAG_COUNT)), "Invalid collider's owner tag!");
    CCASSERT((pCollider2->getOwnerTag() >= 0) && (pCollider2->getOwnerTag() <= static_cast<int>(ObjectTag::TAG_COUNT)), "Invalid collider's owner tag!");
    
    m_hitCallbackMatrix[pCollider1->getOwnerTag()][pCollider2->getOwnerTag()](pCollider1, pCollider2);
}

void CollisionHandler::Impl::processPhysicsStepEnded(PhysicsWorldComponent * sender)
{
    if (m_pDeletate) {
        m_pDeletate->physicsStepDidFinish();
    }
}

void CollisionHandler::Impl::invaderBullet_CollidedWith_ManGun(ColliderComponent * pBulletCollider, ColliderComponent * pManGunCollider)
{
    CCLOG("bullet hit ManGun");
    if (m_pDeletate) {
        m_pDeletate->invaderBullet_CollidedWith_ManGun(pBulletCollider, pManGunCollider);
    }
}

void CollisionHandler::Impl::manBullet_CollidedWith_InvaderShip(ColliderComponent * pBulletCollider, ColliderComponent * pInvaderShipCollider)
{
    CCLOG("bullet hit InvaderShip");
    if (m_pDeletate) {
        m_pDeletate->manBullet_CollidedWith_InvaderShip(pBulletCollider, pInvaderShipCollider);
    }
}

void CollisionHandler::Impl::invaderShip_CollidedWith_ManGun(ColliderComponent * pInvaderShipCollider, ColliderComponent * pManGunCollider)
{
    CCLOG("InvaderShip hit ManGun");
    if (m_pDeletate) {
        m_pDeletate->invaderShip_CollidedWith_ManGun(pInvaderShipCollider, pManGunCollider);
    }
}

#pragma mark CollisionHandler methods
CollisionHandler::~CollisionHandler() = default;

CollisionHandler::CollisionHandler():
m_pImpl(std::make_unique<Impl>())
{
    
}

CollisionHandler::CollisionHandler(const CollisionHandler & other):
m_pImpl(std::make_unique<Impl>(*other.m_pImpl))
{
    if (other.m_pImpl) {
        m_pImpl = std::make_unique<Impl>(*other.m_pImpl);
    }
}

CollisionHandler & CollisionHandler::operator=(const CollisionHandler & other)
{
    *m_pImpl = *other.m_pImpl;
    return *this;
}

CollisionHandler::CollisionHandler(CollisionHandler && other) = default;
CollisionHandler & CollisionHandler::operator=(CollisionHandler && other) = default;


void CollisionHandler::setDelegate(CollisionHandlerProtocol * pDelegate)
{
    m_pImpl->setDelegate(pDelegate);
}

CollisionHandlerProtocol * CollisionHandler::getDelegate() const
{
    return m_pImpl->getDelegate();
}

#pragma mark PhysicsProtocol
bool CollisionHandler::processDeepHitCheck(PhysicsWorldComponent * sender, ColliderComponent * pCollider1, ColliderComponent * pCollider2)
{
    return m_pImpl->processDeepHitCheck(sender, pCollider1, pCollider2);
}

void CollisionHandler::processCollidersHit(PhysicsWorldComponent * sender, ColliderComponent * pCollider1, ColliderComponent * pCollider2)
{
    m_pImpl->processCollidersHit(sender, pCollider1, pCollider2);
}

void CollisionHandler::processPhysicsStepEnded(PhysicsWorldComponent * sender)
{
    m_pImpl->processPhysicsStepEnded(sender);
}
