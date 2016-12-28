//
//  GameScene.hpp
//  SpaceInvaders
//
//  Created by roko on 12/8/16.
//
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include "CSNodeIncludes.hpp"
#include "Helper.hpp"

class GameScene:
public cocos2d::ui::Layout,
public cocostudio::WidgetCallBackHandlerProtocol {
    
    friend class GameSceneReader;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(GameScene);
    
protected:
    GameScene();
    virtual bool init() override;
private:
    std::map<cocos2d::EventKeyboard::KeyCode,
    std::chrono::high_resolution_clock::time_point> keys;
    
    //synthesize properties from Cocos Studio 2
    ///////////////////////////////////////////
    //static const PropertyMap sm_properties;
public:
    bool unusedVar;
#define PROPERTY_TYPE_NAME           \
X(Layout, LeftPanel)              \
X(Layout, RightPanel)\
X(Layout, InitHeroPlacePanel)\
X(Layout, InvaderSpawnerPanel)\
X(Layout, ObjectPanel)\
X(Layout, ScreenPanel)
    
#include "SYNTHESIZE_PROPERTIES.hpp"
    ///////////////////////////////////////////
    
public:
    virtual ~GameScene();
    
    CREATE_FUNC(GameScene)
    
    static GameScene * createDefault();
    
    virtual void onEnter() override;
    virtual void onExit() override;
    
#pragma mark WidgetCallBackHandlerProtocol methods
    cocos2d::ui::Widget::ccWidgetTouchCallback onLocateTouchCallback(const std::string &callBackName) override;
    
#pragma mark Button' callbacks
    
    void onLeftTouch(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type);
    void onRightTouch(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type);
};

#endif /* GameScene_hpp */
