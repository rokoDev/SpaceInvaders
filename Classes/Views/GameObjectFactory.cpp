//
//  GameObjectFactory.cpp
//  SpaceInvaders
//
//  Created by roko on 12/13/16.
//
//

#include "GameObjectFactory.hpp"

#include "BehaviorComponent.hpp"
#include "HealthComponent.hpp"
#include "VelocityComponent.hpp"

#include "InvaderShip.hpp"
#include "ManGun.hpp"
#include "Bullet.hpp"
#include "GameController.hpp"
#include "Level.hpp"

USING_NS_CC;

const std::unordered_map<int, GameObjectFactory::CreatorFunction> GameObjectFactory::sm_creators {
    {static_cast<int>(ObjectType::kInvaderShip), [](const cocos2d::Vec2 & velocity) -> Node * {
        auto ret = InvaderShip::createDefault();
        if (ret) {
            auto pBehavior = BehaviorComponent::create(&Behaviors::invaderShip);
            if (pBehavior)
                ret->addComponent(pBehavior);
                
                auto pHealth = HealthComponent::create(GAME_CONTROLLER.getLevel()->invaderHealth, GAME_CONTROLLER.getLevel()->invaderMaxHealth);
                if (pHealth)
                    ret->addComponent(pHealth);
                    
                    auto pVelocity = VelocityComponent::create(velocity);
                    if (pVelocity)
                        ret->addComponent(pVelocity);
                        }
        return ret;
    }},
    
    {static_cast<int>(ObjectType::kManGun), [](const cocos2d::Vec2 & velocity) -> Node * {
        auto ret = ManGun::createDefault();
        if (ret) {
            auto pBehavior = BehaviorComponent::create(&Behaviors::manGun);
            if (pBehavior)
                ret->addComponent(pBehavior);
                
                auto pHealth = HealthComponent::create(GAME_CONTROLLER.getLevel()->manGunHealth, GAME_CONTROLLER.getLevel()->manGunMaxHealth);
                if (pHealth)
                    ret->addComponent(pHealth);
                    
                    auto pVelocity = VelocityComponent::create(velocity);
                    if (pVelocity)
                        ret->addComponent(pVelocity);
                        pVelocity->setEnabled(false);
                        }
        return ret;
    }},
    
    {static_cast<int>(ObjectType::kBullet), [](const cocos2d::Vec2 & velocity) -> Node * {
        auto ret = Bullet::createDefault();
        if (ret) {
            auto pBehavior = BehaviorComponent::create(&Behaviors::bullet);
            if (pBehavior)
                ret->addComponent(pBehavior);
                
                auto pHealth = HealthComponent::create(100.f, 100.f);
                if (pHealth)
                    ret->addComponent(pHealth);
                    
                    auto pVelocity = VelocityComponent::create(velocity);
                    if (pVelocity) {
                        ret->addComponent(pVelocity);
                        if (velocity.y < 0.f) {
                            ret->getMainImage()->setFlippedY(true);
                        }
                    }
                        }
        return ret;
    }}
};

Node * GameObjectFactory::createObject(const GameObjectFactory::ObjectType val, const cocos2d::Vec2 & velocity)
{
    Node * ret = nullptr;
    auto it = sm_creators.find(static_cast<int>(val));
    if (sm_creators.end() != it) {
        ret = (it->second)(velocity);
    }
    
    return ret;
}
