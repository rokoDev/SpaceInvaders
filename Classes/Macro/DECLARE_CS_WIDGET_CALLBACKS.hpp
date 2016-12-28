//
//  DECLARE_CS_WIDGET_CALLBACKS.hpp
//  SpaceInvaders
//
//  Created by roko on 12/12/16.
//
//

#ifndef DECLARE_CS_WIDGET_CALLBACKS_hpp
#define DECLARE_CS_WIDGET_CALLBACKS_hpp

#ifdef TOUCH_HANDLERS_DECLARATION
#define X(methodName) void methodName(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type);
TOUCH_HANDLERS_DECLARATION
#undef X
#endif

#ifdef CLICK_HANDLERS_DECLARATION
#define X(methodName) void methodName(cocos2d::Ref * sender);
CLICK_HANDLERS_DECLARATION
#undef X
#endif

#ifdef EVENT_HANDLERS_DECLARATION
#define X(methodName) void methodName(cocos2d::Ref * sender, int eventType);
EVENT_HANDLERS_DECLARATION
#undef X
#endif

#endif /* DECLARE_CS_WIDGET_CALLBACKS_hpp */
