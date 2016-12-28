//
//  InvaderShip.cpp
//  SpaceInvaders
//
//  Created by roko on 12/13/16.
//
//

#include "RegisterCustomReaders.hpp"
#include "GameObjectFactory.hpp"
#include "GameController.hpp"
#include "Bullet.hpp"
#include "Level.hpp"
#include "ColliderComponent.hpp"
#include "BinMacro.h"
#include "DamageComponent.hpp"

#include "InvaderShip.hpp"

USING_NS_CC;

using namespace cocos2d::ui;

ActiveShipT InvaderShip::sm_activeShips;

unsigned int InvaderShip::sm_countCreatedDuringTheGame = 0;

#define ROOT_CLASS  InvaderShip
#include "PROPERTY_MAP_MACRO.hpp"

InvaderShip::~InvaderShip()
{
    CCLOG("%d, %s", __LINE__, __FUNCTION__);
}

InvaderShip::InvaderShip():
#include "INITIALIZE_PROPERTIES.hpp"
unusedVar(false)
{
    CCLOG("%d, %s", __LINE__, __FUNCTION__);
    ++sm_countCreatedDuringTheGame;
}

InvaderShip * InvaderShip::createDefault()
{
    static cocos2d::Data data;
    if (0 == data.getSize()) {
        const std::string fileName = MY_STRINGIFY(ROOT_CLASS)+std::string(".csb");
        data = FileUtils::getInstance()->getDataFromFile(fileName);
    }
    auto rootNode = static_cast<InvaderShip*>(CSLoader::createNode(data, InvaderShipReader::sm_nodeLoadCallback));
    
    //rootNode->setContentSize(Director::getInstance()->getWinSize());
    ui::Helper::doLayout(rootNode);
    
    rootNode->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    
    rootNode->setTag(static_cast<int>(ObjectTag::InvaderShip));
    
    rootNode->getSpawnerBulletPanel()->runAction(RepeatForever::create(Sequence::create(CallFunc::create([rootNode](){
        Vec2 spawnPos = rootNode->getPosition()-Vec2(0.f, rootNode->getSpawnerBulletPanel()->getPosition().y/2);
        auto pBullet = static_cast<Bullet *>(GameObjectFactory::createObject(GameObjectFactory::ObjectType::kBullet, CUR_LEVEL->invaderBulletVelocity));
        pBullet->setTag(static_cast<int>(ObjectTag::InvaderBullet));
        pBullet->getMainImage()->loadTexture("objects/lasers/laserGreen_07.png", TextureResType::PLIST);
        pBullet->setContentSize(pBullet->getMainImage()->getContentSize());
        spawnPos.y -= pBullet->getContentSize().height/2;
        pBullet->setPosition(spawnPos);
        pBullet->setLocalZOrder(CUR_LEVEL->kBulletZ);
        pBullet->addComponent(ColliderComponent::create(CUR_LEVEL->invaderBulletCollideMask, CUR_LEVEL->invaderBulletGroupID));
        pBullet->addComponent(DamageComponent::create(CUR_LEVEL->invaderBulletDamage));
        GAME_CONTROLLER.addGameObject(pBullet);
    }), DelayTime::create(CUR_LEVEL->invaderBulletSpawnDelay), NULL)));
    
    sm_activeShips.insert(rootNode);
    
    return (InvaderShip*)rootNode;
}

bool InvaderShip::init()
{
    if (Layout::init()) {
        return true;
    }
    return false;
}

void InvaderShip::onExitTransitionDidStart()
{
    sm_activeShips.erase(this);
    CCLOG("erase ship");
}
