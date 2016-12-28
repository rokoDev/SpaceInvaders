//
//  INITIALIZE_PROPERTIES.hpp
//  SpaceInvaders
//
//  Created by roko on 12/12/16.
//
//

//#ifndef INITIALIZE_PROPERTIES_hpp
//#define INITIALIZE_PROPERTIES_hpp

#ifdef PROPERTY_TYPE_NAME
#define X(type, varName) m_p##varName(nullptr),
PROPERTY_TYPE_NAME
#undef X
#endif

//#endif /* INITIALIZE_PROPERTIES_hpp */
