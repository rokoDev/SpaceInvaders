//
//  StartScene.cpp
//  MultiRes
//
//  Created by roko on 8/27/16.
//
//

#include "RegisterCustomReaders.hpp"
#include "GameController.hpp"

#include "StartScene.hpp"
USING_NS_CC;

using namespace cocos2d::ui;

#define ROOT_CLASS  StartScene
#include "PROPERTY_MAP_MACRO.hpp"

StartScene::~StartScene()
{
    CCLOG("%d, %s", __LINE__, __FUNCTION__);
}

StartScene::StartScene()
{
    
}

StartScene * StartScene::createDefault(void)
{
    static cocos2d::Data data;
    if (0 == data.getSize()) {
        const std::string fileName = MY_STRINGIFY(ROOT_CLASS)+std::string(".csb");
        data = FileUtils::getInstance()->getDataFromFile(fileName);
    }
    auto rootNode = static_cast<StartScene*>(CSLoader::createNode(data, StartSceneReader::sm_nodeLoadCallback));
    
    rootNode->setContentSize(Director::getInstance()->getWinSize());
    ui::Helper::doLayout(rootNode);
    
    return (StartScene*)rootNode;
}

#pragma mark WidgetCallBackHandlerProtocol methods

Widget::ccWidgetTouchCallback StartScene::onLocateTouchCallback(const std::string &callBackName)
{
//    if (callBackName == "onPlay")
//    {
//        return CC_CALLBACK_2(StartScene::onPlay, this);
//    }
    
    return nullptr;
}

cocos2d::ui::Widget::ccWidgetClickCallback StartScene::onLocateClickCallback(const std::string &callBackName)
{
    if (callBackName == "onPlay")
    {
        return CC_CALLBACK_1(StartScene::onPlay, this);
    }
    return nullptr;
}

bool StartScene::init()
{
    if (Layout::init()) {
        return true;
    }
    return false;
}

void StartScene::onEnter()
{
    Layout::onEnter();
}

void StartScene::onExit()
{
    Layout::onExit();
}

#pragma mark Button' callbacks

void StartScene::onPlay(cocos2d::Ref * sender)
{
    CCLOG("StartScene::onPlay");
    GameController::getInstance().startNewGame();
}
