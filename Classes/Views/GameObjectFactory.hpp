//
//  GameObjectFactory.hpp
//  SpaceInvaders
//
//  Created by roko on 12/13/16.
//
//

#ifndef GameObjectFactory_hpp
#define GameObjectFactory_hpp

#include "cocos2d.h"
#include <functional>

class GameObjectFactory {
    
private:
    using CreatorFunction = std::function<cocos2d::Node * (const cocos2d::Vec2 &)>;
    static const std::unordered_map<int, CreatorFunction> sm_creators;
    
public:
    enum class ObjectType
    {
        kInvaderShip,
        kManGun,
        kBullet
    };
    
    static cocos2d::Node * createObject(const ObjectType val, const cocos2d::Vec2 & velocity);
};

#endif /* GameObjectFactory_hpp */
