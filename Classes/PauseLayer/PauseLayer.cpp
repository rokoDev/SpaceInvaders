//
//  PauseLayer.cpp
//  SpaceInvaders
//
//  Created by roko on 12/8/16.
//
//

#include "RegisterCustomReaders.hpp"
#include "GameController.hpp"

#include "PauseLayer.hpp"

USING_NS_CC;

using namespace cocos2d::ui;

#pragma mark PauseLayer class

#define ROOT_CLASS  PauseLayer
#include "PROPERTY_MAP_MACRO.hpp"

PauseLayer::~PauseLayer()
{
    CCLOG("%d, %s", __LINE__, __FUNCTION__);
}

PauseLayer::PauseLayer()
{
    CCLOG("%d, %s", __LINE__, __FUNCTION__);
}

PauseLayer * PauseLayer::createDefault(void)
{
    static cocos2d::Data data;
    if (0 == data.getSize()) {
        const std::string fileName = MY_STRINGIFY(ROOT_CLASS)+std::string(".csb");
        data = FileUtils::getInstance()->getDataFromFile(fileName);
    }
    auto rootNode = static_cast<PauseLayer*>(CSLoader::createNode(data, PauseLayerReader::sm_nodeLoadCallback));
    
    rootNode->setContentSize(Director::getInstance()->getWinSize());
    ui::Helper::doLayout(rootNode);
    
    return (PauseLayer*)rootNode;
}

#pragma mark WidgetCallBackHandlerProtocol methods

cocos2d::ui::Widget::ccWidgetClickCallback PauseLayer::onLocateClickCallback(const std::string &callBackName)
{
    if ("onResume" == callBackName) {
        return CC_CALLBACK_1(PauseLayer::onResume, this);
    }
    if ("onRestart" == callBackName) {
        return CC_CALLBACK_1(PauseLayer::onRestart, this);
    }
    if ("onExitToMenu" == callBackName) {
        return CC_CALLBACK_1(PauseLayer::onExitToMenu, this);
    }
    return nullptr;
}

bool PauseLayer::init()
{
    if (Layout::init()) {
        return true;
    }
    return false;
}

#pragma mark PauseLayer click callbacks
void PauseLayer::onResume(cocos2d::Ref * sender)
{
    GameController::getInstance().resumeGame();
}

void PauseLayer::onRestart(cocos2d::Ref * sender)
{
    GameController::getInstance().startNewGame();
}

void PauseLayer::onExitToMenu(cocos2d::Ref * sender)
{
    GameController::getInstance().exitToMenu();
}
