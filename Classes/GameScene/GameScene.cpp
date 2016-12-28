//
//  GameScene.cpp
//  SpaceInvaders
//
//  Created by roko on 12/8/16.
//
//

#include "RegisterCustomReaders.hpp"
#include "ComponentDefinitions.hpp"
#include "GameObjectFactory.hpp"
#include "GameController.hpp"

#include "GameScene.hpp"

USING_NS_CC;

using namespace cocos2d::ui;

#define ROOT_CLASS  GameScene
#include "PROPERTY_MAP_MACRO.hpp"

GameScene::~GameScene()
{
    CCLOG("%d, %s", __LINE__, __FUNCTION__);
}

GameScene::GameScene():
#include "INITIALIZE_PROPERTIES.hpp"
unusedVar(false)
{
    CCLOG("%d, %s", __LINE__, __FUNCTION__);
}

GameScene * GameScene::createDefault()
{
    static cocos2d::Data data;
    if (0 == data.getSize()) {
        const std::string fileName = MY_STRINGIFY(ROOT_CLASS)+std::string(".csb");
        data = FileUtils::getInstance()->getDataFromFile(fileName);
    }
    auto rootNode = static_cast<GameScene*>(CSLoader::createNode(data, GameSceneReader::sm_nodeLoadCallback));
    
    rootNode->setContentSize(Director::getInstance()->getWinSize());
    ui::Helper::doLayout(rootNode);
    
    return (GameScene*)rootNode;
}

#pragma mark WidgetCallBackHandlerProtocol methods

cocos2d::ui::Widget::ccWidgetTouchCallback GameScene::onLocateTouchCallback(const std::string &callBackName)
{
    if ("onLeftTouch" == callBackName) {
        return CC_CALLBACK_2(GameScene::onLeftTouch, this);
    }
    if ("onRightTouch" == callBackName) {
        return CC_CALLBACK_2(GameScene::onRightTouch, this);
    }
    return nullptr;
}

bool GameScene::init()
{
    if (Layout::init()) {
        CCLOG("");
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
        auto eventListener = EventListenerKeyboard::create();
        
        Director::getInstance()->getOpenGLView()->setIMEKeyboardState(true);
        eventListener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event){
            // If a key already exists, do nothing as it will already have a time stamp
            // Otherwise, set's the timestamp to now
            
            MoveDirection direction = MoveDirection::None;
            switch(keyCode){
                case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
                case EventKeyboard::KeyCode::KEY_A:
                {
                    direction = MoveDirection::Left;
                    break;
                }
                case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
                case EventKeyboard::KeyCode::KEY_D:
                {
                    direction = MoveDirection::Right;
                    break;
                }
                    
                default:
                    break;
            }
            
            if (MoveDirection::None != direction) {
                keys.clear();
                keys[keyCode] = std::chrono::high_resolution_clock::now();
                GAME_CONTROLLER.moveManGun(this, direction);
            }
        };
        
        eventListener->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event* event){
            // remove the key.  std::map.erase() doesn't care if the key doesnt exist
            auto it = keys.find(keyCode);
            if(it != keys.end()) {
                GAME_CONTROLLER.moveManGun(this, MoveDirection::Idle);
                keys.erase(keyCode);
            }
        };
        
        this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener,this);
#endif
        
        return true;
    }
    return false;
}

void GameScene::onEnter()
{
    Layout::onEnter();
}

void GameScene::onExit()
{
    Layout::onExit();
}

#pragma mark Button' callbacks

void GameScene::onLeftTouch(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
    switch (type) {
        case Widget::TouchEventType::BEGAN:
        {
            GAME_CONTROLLER.moveManGun(this, MoveDirection::Left);
            break;
        }
        case Widget::TouchEventType::ENDED:
        {
            GAME_CONTROLLER.moveManGun(this, MoveDirection::Idle);
            break;
        }
        case Widget::TouchEventType::CANCELED:
        {
            GAME_CONTROLLER.moveManGun(this, MoveDirection::Idle);
            break;
        }
            
        default:
            break;
    }
}

void GameScene::onRightTouch(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
    switch (type) {
        case Widget::TouchEventType::BEGAN:
        {
            GAME_CONTROLLER.moveManGun(this, MoveDirection::Right);
            break;
        }
        case Widget::TouchEventType::ENDED:
        {
            GAME_CONTROLLER.moveManGun(this, MoveDirection::Idle);
            break;
        }
        case Widget::TouchEventType::CANCELED:
        {
            GAME_CONTROLLER.moveManGun(this, MoveDirection::Idle);
            break;
        }
            
        default:
            break;
    }
}
