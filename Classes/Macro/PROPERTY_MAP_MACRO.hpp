//
//  PROPERTY_MAP_MACRO.hpp
//  SpaceInvaders
//
//  Created by roko on 12/12/16.
//
//

//#ifndef PROPERTY_MAP_MACRO_hpp
//#define PROPERTY_MAP_MACRO_hpp

//#if defined (PROPERTY_TYPE_NAME) && defined (ROOT_CLASS)
#if defined (ROOT_CLASS)

//#ifndef PROPERTY_TYPE_NAME
//#define PROPERTY_TYPE_NAME

#define X(type, varName) { #varName, [](cocos2d::Node * propertyVal, cocos2d::Node * rootNode) -> bool {\
cocos2d::ui::type * p##type = dynamic_cast<cocos2d::ui::type *>(propertyVal);\
if (p##type) {\
static_cast<ROOT_CLASS *>(rootNode)->set##varName(p##type);\
return true;\
}\
return false;\
} },

#define INIT_PROPERTY_MAP const PropertyMap ROOT_CLASS::sm_properties = { PROPERTY_TYPE_NAME };
INIT_PROPERTY_MAP
#undef DECLARE_PROPERTY_MAP
#undef X

#endif

//#endif

//#endif /* PROPERTY_MAP_MACRO_hpp */
