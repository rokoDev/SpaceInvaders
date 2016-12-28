//
//  StartScene.hpp
//  MultiRes
//
//  Created by roko on 8/27/16.
//
//

#ifndef StartScene_hpp
#define StartScene_hpp

#include "CSNodeIncludes.hpp"

#include "Helper.hpp"

class StartScene :
public cocos2d::ui::Layout,
public cocostudio::WidgetCallBackHandlerProtocol {
    
    friend class StartSceneReader;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(StartScene);
    
protected:
    StartScene();
    virtual bool init() override;
    
    //synthesize properties from Cocos Studio 2
    ///////////////////////////////////////////
//public:
    //static const PropertyMap sm_properties;
    #define PROPERTY_TYPE_NAME
    #include "SYNTHESIZE_PROPERTIES.hpp"
    ///////////////////////////////////////////
    
public:
    virtual ~StartScene();
    
    CREATE_FUNC(StartScene)
    
#pragma mark WidgetCallBackHandlerProtocol methods
    cocos2d::ui::Widget::ccWidgetTouchCallback onLocateTouchCallback(const std::string &callBackName) override;
    cocos2d::ui::Widget::ccWidgetClickCallback onLocateClickCallback(const std::string &callBackName) override;
    
    static StartScene * createDefault(void);
    
    virtual void onEnter() override;
    virtual void onExit() override;
    
#pragma mark Button' callbacks
    void onPlay(cocos2d::Ref * sender);
};

#endif /* StartScene_hpp */
