//
//  ComponentDefinitions.hpp
//  SpaceInvaders
//
//  Created by roko on 12/12/16.
//
//

#ifndef ComponentDefinitions_hpp
#define ComponentDefinitions_hpp

#include <iosfwd>

#define CUSTOM_COMPONENT_IDS \
X(Velocity)\
X(Health)\
X(Behavior)\
X(Collider)\
X(PhysicsWorld)\
X(Damage)

#define X(a) extern const std::string k##a##KeyStr;
CUSTOM_COMPONENT_IDS
#undef X

#endif /* ComponentDefinitions_hpp */
