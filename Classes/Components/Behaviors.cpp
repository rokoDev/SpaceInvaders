//
//  Behaviors.cpp
//  SpaceInvaders
//
//  Created by roko on 12/13/16.
//
//

#include "Behaviors.hpp"
#include "ComponentDefinitions.hpp"
#include "VelocityComponent.hpp"
#include "InvaderShip.hpp"
#include "ManGun.hpp"
#include "Bullet.hpp"
#include "GameController.hpp"
#include "Level.hpp"

USING_NS_CC;

void Behaviors::invaderShip(cocos2d::Node * pContext, const float dt)
{
    
    auto pVel = static_cast<VelocityComponent *>(pContext->getComponent(kVelocityKeyStr));
    if (pVel) {
        auto & GC = GAME_CONTROLLER;
        const auto kYOffset = GC.getLevel()->invaderYOffset;
        const auto xOffset = pVel->getVelocity().x*dt;
        auto yPos = pContext->getPositionY();
        auto xPos = pContext->getPositionX()+xOffset;
        const auto shipSize = Size(pContext->getContentSize().width*pContext->getScaleX(), pContext->getContentSize().height*pContext->getScaleY());
        const auto halfWidth = shipSize.width/2.f;
        const auto & scRect = SCREEN_RECT;
        if (xOffset > 0.f && xPos >= scRect.origin.x + scRect.size.width + halfWidth) {
            xPos = scRect.origin.x + scRect.size.width + halfWidth;
            yPos -= kYOffset;
            pVel->setVelocityX(-pVel->getVelocity().x);
        }
        else if (xOffset < 0.f && xPos <= -halfWidth + scRect.origin.x) {
            xPos = -halfWidth + scRect.origin.x;
            yPos -= kYOffset;
            pVel->setVelocityX(-pVel->getVelocity().x);
        }
        pContext->setPosition(Vec2(xPos, yPos));
        if (yPos - pContext->getAnchorPoint().y*shipSize.height <= GC.getLevel()->landHeight) {
            GC.objectHasReachedSurface(pContext);
        }
    }
}

void Behaviors::manGun(cocos2d::Node * pContext, const float dt)
{
    auto pVel = static_cast<VelocityComponent *>(pContext->getComponent(kVelocityKeyStr));
    if (pVel) {
        const auto xOffset = pVel->getVelocity().x*dt;
        auto xPos = pContext->getPositionX()+xOffset;
        const auto & scRect = SCREEN_RECT;
        xPos = clampf(xPos, scRect.origin.x, scRect.origin.x + scRect.size.width);
        pContext->setPositionX(xPos);
    }
}

void Behaviors::bullet(cocos2d::Node * pContext, const float dt)
{
    auto pVel = static_cast<VelocityComponent *>(pContext->getComponent(kVelocityKeyStr));
    if (pVel) {
        const auto offset = pVel->getVelocity()*dt;
        const auto newPos = pContext->getPosition()+offset;
        
        const auto & scRect = SCREEN_RECT;
        const auto halfSize = pContext->getContentSize()*pContext->getScale()/2.f;
        if (newPos.y < scRect.origin.y - halfSize.height ||
            newPos.y > scRect.origin.y + scRect.size.height + halfSize.height ||
            newPos.x < scRect.origin.x - halfSize.width ||
            newPos.x > scRect.origin.x + scRect.size.width + halfSize.width) {
            GAME_CONTROLLER.removeGameObject(pContext);
        }
        else {
            pContext->setPosition(newPos);
        }
    }
}
