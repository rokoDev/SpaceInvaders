//
//  PauseLayer.hpp
//  SpaceInvaders
//
//  Created by roko on 12/8/16.
//
//

#ifndef PauseLayer_hpp
#define PauseLayer_hpp

#include "CSNodeIncludes.hpp"

//#include "Helper.hpp"

class PauseLayer :
public cocos2d::ui::Layout,
public cocostudio::WidgetCallBackHandlerProtocol {
    
    friend class PauseLayerReader;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(PauseLayer);
    
protected:
    PauseLayer();
    virtual bool init() override;
    
    //synthesize properties from Cocos Studio 2
    ///////////////////////////////////////////
//public:
    //static const PropertyMap sm_properties;
    #define PROPERTY_TYPE_NAME
    #include "SYNTHESIZE_PROPERTIES.hpp"
    ///////////////////////////////////////////
    
public:
    virtual ~PauseLayer();
    
    CREATE_FUNC(PauseLayer)
    
#pragma mark WidgetCallBackHandlerProtocol methods
    cocos2d::ui::Widget::ccWidgetClickCallback onLocateClickCallback(const std::string &callBackName) override;
    
    static PauseLayer * createDefault(void);
    
#pragma PauseLayer click callbacks
    void onResume(cocos2d::Ref * sender);
    void onRestart(cocos2d::Ref * sender);
    void onExitToMenu(cocos2d::Ref * sender);
    
#include "DECLARE_CS_WIDGET_CALLBACKS.hpp"
};

#endif /* PauseLayer_hpp */
