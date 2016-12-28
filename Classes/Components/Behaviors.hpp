//
//  Behaviors.hpp
//  SpaceInvaders
//
//  Created by roko on 12/13/16.
//
//

#ifndef Behaviors_hpp
#define Behaviors_hpp

#include "cocos2d.h"

using BehaviorFunction = void (*)(cocos2d::Node * pContext, const float dt);

class Behaviors {
    
public:
    static void invaderShip(cocos2d::Node * pContext, const float dt);
    static void manGun(cocos2d::Node * pContext, const float dt);
    static void bullet(cocos2d::Node * pContext, const float dt);
};

#endif /* Behaviors_hpp */
