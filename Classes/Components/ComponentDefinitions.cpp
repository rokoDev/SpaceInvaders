//
//  ComponentDefinitions.cpp
//  SpaceInvaders
//
//  Created by roko on 12/12/16.
//
//

#include "ComponentDefinitions.hpp"
#include "Helper.hpp"

#define X(a) const std::string k##a##KeyStr = MY_STRINGIFY(k##a);
CUSTOM_COMPONENT_IDS
#undef X
