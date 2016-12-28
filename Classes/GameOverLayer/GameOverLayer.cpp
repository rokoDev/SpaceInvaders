//
//  GameOverLayer.cpp
//  SpaceInvaders
//
//  Created by roko on 12/8/16.
//
//

#include "RegisterCustomReaders.hpp"
#include "GameController.hpp"

#include "GameOverLayer.hpp"

USING_NS_CC;

using namespace cocos2d::ui;

#define ROOT_CLASS  GameOverLayer
#include "PROPERTY_MAP_MACRO.hpp"

GameOverLayer::~GameOverLayer()
{
    CCLOG("%d, %s", __LINE__, __FUNCTION__);
}

GameOverLayer::GameOverLayer():
#include "INITIALIZE_PROPERTIES.hpp"
unusedVar(false)
{
    
}

GameOverLayer * GameOverLayer::createDefault()
{
    static cocos2d::Data data;
    if (0 == data.getSize()) {
        const std::string fileName = MY_STRINGIFY(ROOT_CLASS)+std::string(".csb");
        data = FileUtils::getInstance()->getDataFromFile(fileName);
    }
    auto rootNode = static_cast<GameOverLayer*>(CSLoader::createNode(data, GameOverLayerReader::sm_nodeLoadCallback));
    
    rootNode->setContentSize(Director::getInstance()->getWinSize());
    ui::Helper::doLayout(rootNode);
    
    return (GameOverLayer*)rootNode;
}

#pragma mark WidgetCallBackHandlerProtocol methods

cocos2d::ui::Widget::ccWidgetClickCallback GameOverLayer::onLocateClickCallback(const std::string &callBackName)
{
    if (callBackName == "onRestart")
    {
        return CC_CALLBACK_1(GameOverLayer::onRestart, this);
    }
    else if (callBackName == "onExitToMenu")
    {
        return CC_CALLBACK_1(GameOverLayer::onExitToMenu, this);
    }
    return nullptr;
}

bool GameOverLayer::init()
{
    if (Layout::init()) {
        return true;
    }
    return false;
}

void GameOverLayer::onEnter()
{
    Layout::onEnter();
}

void GameOverLayer::onExit()
{
    Layout::onExit();
}

#pragma mark Button' callbacks

void GameOverLayer::onRestart(cocos2d::Ref * sender)
{
    CCLOG("GameOverLayer::onRestart");
    GameController::getInstance().startNewGame();
}

void GameOverLayer::onExitToMenu(cocos2d::Ref * sender)
{
    CCLOG("GameOverLayer::onExitToMenu");
    GameController::getInstance().exitToMenu();
}
