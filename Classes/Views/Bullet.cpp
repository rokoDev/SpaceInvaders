//
//  Bullet.cpp
//  SpaceInvaders
//
//  Created by roko on 12/13/16.
//
//

#include "RegisterCustomReaders.hpp"

#include "Bullet.hpp"

USING_NS_CC;

using namespace cocos2d::ui;

#define ROOT_CLASS  Bullet
#include "PROPERTY_MAP_MACRO.hpp"

Bullet::~Bullet()
{
    CCLOG("%d, %s", __LINE__, __FUNCTION__);
}

Bullet::Bullet():
#include "INITIALIZE_PROPERTIES.hpp"
unusedVar(false)
{
    CCLOG("%d, %s", __LINE__, __FUNCTION__);
}

Bullet * Bullet::createDefault()
{
    static cocos2d::Data data;
    if (0 == data.getSize()) {
        const std::string fileName = MY_STRINGIFY(ROOT_CLASS)+std::string(".csb");
        data = FileUtils::getInstance()->getDataFromFile(fileName);
    }
    auto rootNode = static_cast<Bullet*>(CSLoader::createNode(data, BulletReader::sm_nodeLoadCallback));
    rootNode->getMainImage()->ignoreContentAdaptWithSize(true);
    
    //rootNode->setContentSize(Director::getInstance()->getWinSize());
    ui::Helper::doLayout(rootNode);
    
    rootNode->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    
    return (Bullet*)rootNode;
}

bool Bullet::init()
{
    if (Layout::init()) {
        return true;
    }
    return false;
}
