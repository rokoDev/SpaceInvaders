//
//  GameOverLayer.hpp
//  SpaceInvaders
//
//  Created by roko on 12/8/16.
//
//

#ifndef GameOverLayer_hpp
#define GameOverLayer_hpp

#include "CSNodeIncludes.hpp"

#include "Helper.hpp"

class GameOverLayer :
public cocos2d::ui::Layout,
public cocostudio::WidgetCallBackHandlerProtocol {
    
    friend class GameOverLayerReader;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(GameOverLayer);
    
protected:
    GameOverLayer();
    virtual bool init() override;
    
    //synthesize properties from Cocos Studio 2
    ///////////////////////////////////////////
//public:
    //static const PropertyMap sm_properties;
    bool unusedVar;
    #define PROPERTY_TYPE_NAME \
    X(Text, FinishText)
    
    #include "SYNTHESIZE_PROPERTIES.hpp"
    ///////////////////////////////////////////
    
    //CC_SYNTHESIZE(cocos2d::ui::Text *, m_pFinishText, FinishText);
    
public:
    virtual ~GameOverLayer();
    
    CREATE_FUNC(GameOverLayer)
    
#pragma mark WidgetCallBackHandlerProtocol methods
    cocos2d::ui::Widget::ccWidgetClickCallback onLocateClickCallback(const std::string &callBackName) override;
    
    static GameOverLayer * createDefault();
    
    virtual void onEnter() override;
    virtual void onExit() override;
    
#pragma mark Button' callbacks
    void onRestart(cocos2d::Ref * sender);
    void onExitToMenu(cocos2d::Ref * sender);
};

#endif /* GameOverLayer_hpp */
