//
//  ManGun.cpp
//  SpaceInvaders
//
//  Created by roko on 12/13/16.
//
//

#include "RegisterCustomReaders.hpp"
#include "GameObjectFactory.hpp"
#include "GameController.hpp"
#include "Level.hpp"
#include "ColliderComponent.hpp"
#include "BinMacro.h"
#include "DamageComponent.hpp"

#include "ManGun.hpp"

USING_NS_CC;

using namespace cocos2d::ui;

#define ROOT_CLASS  ManGun
#include "PROPERTY_MAP_MACRO.hpp"

ManGun::~ManGun()
{
    CCLOG("%d, %s", __LINE__, __FUNCTION__);
}

ManGun::ManGun():
#include "INITIALIZE_PROPERTIES.hpp"
unusedVar(false)
{
    CCLOG("%d, %s", __LINE__, __FUNCTION__);
}

ManGun * ManGun::createDefault()
{
    static cocos2d::Data data;
    if (0 == data.getSize()) {
        const std::string fileName = MY_STRINGIFY(ROOT_CLASS)+std::string(".csb");
        data = FileUtils::getInstance()->getDataFromFile(fileName);
    }
    auto rootNode = static_cast<ManGun*>(CSLoader::createNode(data, ManGunReader::sm_nodeLoadCallback));
    
    //rootNode->setContentSize(Director::getInstance()->getWinSize());
    ui::Helper::doLayout(rootNode);
    
    rootNode->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
    
    rootNode->setTag(static_cast<int>(ObjectTag::ManGun));
    
    rootNode->getSpawnBulletPanel()->runAction(RepeatForever::create(Sequence::create(CallFunc::create([rootNode](){
        Vec2 spawnPos = rootNode->getPosition()+Vec2(0.f, rootNode->getSpawnBulletPanel()->getPosition().y/2);
        auto pBullet = GameObjectFactory::createObject(GameObjectFactory::ObjectType::kBullet, CUR_LEVEL->manBulletVelocity);
        pBullet->setTag(static_cast<int>(ObjectTag::ManBullet));
        pBullet->setPosition(spawnPos);
        pBullet->setLocalZOrder(CUR_LEVEL->kBulletZ);
        pBullet->addComponent(ColliderComponent::create(CUR_LEVEL->manBulletCollideMask, CUR_LEVEL->manBulletGroupID));
        pBullet->addComponent(DamageComponent::create(CUR_LEVEL->manBulletDamage));
        GAME_CONTROLLER.addGameObject(pBullet);
    }), DelayTime::create(CUR_LEVEL->manBulletSpawnDelay), NULL)));
    
    return (ManGun*)rootNode;
}

bool ManGun::init()
{
    if (Layout::init()) {
        return true;
    }
    return false;
}

