//
//  DEFINE_CS_WIDGET_CALLBACKS.hpp
//  SpaceInvaders
//
//  Created by roko on 12/12/16.
//
//

#ifndef DEFINE_CS_WIDGET_CALLBACKS_hpp
#define DEFINE_CS_WIDGET_CALLBACKS_hpp

#if defined(TOUCH_HANDLERS_DECLARATION) && defined(ROOT_CLASS)

#define METHOD_DEFINITION_BEGIN cocos2d::ui::Widget::ccWidgetTouchCallback ROOT_CLASS::onLocateTouchCallback(const std::string &callBackName) {
METHOD_DEFINITION_BEGIN
#undef METHOD_DEFINITION_BEGIN

#define X(methodName) \
if (callBackName == #methodName) {\
return CC_CALLBACK_2(ROOT_CLASS::methodName, this);\
}
TOUCH_HANDLERS_DECLARATION
#undef X

#define METHOD_DEFINITION_END return nullptr; }
METHOD_DEFINITION_END
#undef METHOD_DEFINITION_END

#endif


#if defined(CLICK_HANDLERS_DECLARATION) && defined(ROOT_CLASS)

#define METHOD_DEFINITION_BEGIN cocos2d::ui::Widget::ccWidgetClickCallback ROOT_CLASS::onLocateClickCallback(const std::string &callBackName) {
METHOD_DEFINITION_BEGIN
#undef METHOD_DEFINITION_BEGIN

#define X(methodName) \
if (callBackName == #methodName) {\
return CC_CALLBACK_1(ROOT_CLASS::methodName, this);\
}
CLICK_HANDLERS_DECLARATION
#undef X

#define METHOD_DEFINITION_END return nullptr; }
METHOD_DEFINITION_END
#undef METHOD_DEFINITION_END

#endif


#if defined(EVENT_HANDLERS_DECLARATION) && defined(ROOT_CLASS)

#define METHOD_DEFINITION_BEGIN cocos2d::ui::Widget::ccWidgetEventCallback ROOT_CLASS::onLocateEventCallback(const std::string &callBackName) {
METHOD_DEFINITION_BEGIN
#undef METHOD_DEFINITION_BEGIN

#define X(methodName) \
if (callBackName == #methodName) {\
return CC_CALLBACK_2(ROOT_CLASS::methodName, this);\
}
TOUCH_HANDLERS_DECLARATION
#undef X

#define METHOD_DEFINITION_END return nullptr; }
METHOD_DEFINITION_END
#undef METHOD_DEFINITION_END

#endif

#endif /* DEFINE_CS_WIDGET_CALLBACKS_hpp */
