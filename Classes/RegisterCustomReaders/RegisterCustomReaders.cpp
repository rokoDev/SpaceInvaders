//
//  RegisterCustomReaders.cpp
//  MightyClickers
//
//  Created by jam on 1/12/16.
//
//

#include "RegisterCustomReaders.hpp"

#include "StartScene.hpp"
#include "PauseLayer.hpp"
#include "GameOverLayer.hpp"
#include "GameScene.hpp"
#include "ManGun.hpp"
#include "InvaderShip.hpp"
#include "Bullet.hpp"

USING_NS_CC;

using namespace cocos2d::ui;

#define X(a) READER_DEFINITION_FOR(a);
READERTYPES
#undef X

#define REGISTER_READER(readerClassName)\
CSLoader::getInstance()->registReaderObject(#readerClassName,(ObjectFactory::Instance)readerClassName::getInstance);

void registerCustomReaders(void)
{
    CCLOG("%s, line:%d, func:%s", __FILE__, __LINE__, __FUNCTION__);
#define X(a) REGISTER_READER(a##Reader);
    READERTYPES
#undef X
}
