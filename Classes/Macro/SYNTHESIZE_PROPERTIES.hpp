//
//  SYNTHESIZE_PROPERTIES.hpp
//  SpaceInvaders
//
//  Created by roko on 12/12/16.
//
//

//#ifndef SYNTHESIZE_PROPERTIES_hpp
//#define SYNTHESIZE_PROPERTIES_hpp

#ifdef PROPERTY_TYPE_NAME

#define DECLARE_PROPERTY_MAP static const PropertyMap sm_properties;
DECLARE_PROPERTY_MAP
#undef DECLARE_PROPERTY_MAP

#define X(type, varName) CC_SYNTHESIZE(cocos2d::ui::type *, m_p##varName, varName);
PROPERTY_TYPE_NAME
#undef X

#endif

//#endif /* SYNTHESIZE_PROPERTIES_hpp */
