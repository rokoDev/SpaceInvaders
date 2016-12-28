//
//  Level.hpp
//  SpaceInvaders
//
//  Created by roko on 12/17/16.
//
//

#ifndef Level_hpp
#define Level_hpp

#include "cocos2d.h"
#include "PhysicsDefinitions.hpp"
#include "BinMacro.h"

struct Level {
    int kPauseLayerZ;
    int kManGunZ;
    int kInvaderZ;
    int kBulletZ;
    int kGameOverZ;
    
    cocos2d::Vec2 manGunVelocity;
    float manGunHealth;
    float manGunMaxHealth;
    cocos2d::Vec2 manBulletVelocity;
    float manBulletSpawnDelay;
    float manBulletDamage;
    
    cocos2d::Vec2 invaderVelocity;
    float invaderHealth;
    float invaderMaxHealth;
    cocos2d::Vec2 invaderBulletVelocity;
    float invaderSpawnDelay;
    float invaderBulletSpawnDelay;
    float invaderBulletDamage;
    int invaderCount;
    float invaderYOffset;
    float invaderVelocityDelta;
    
    BitMaskType manGunCollideMask;
    GroupIDType manGunGroupID;
    
    BitMaskType manBulletCollideMask;
    GroupIDType manBulletGroupID;
    
    BitMaskType invaderCollideMask;
    GroupIDType invaderGroupID;
    
    BitMaskType invaderBulletCollideMask;
    GroupIDType invaderBulletGroupID;
    
    float landHeight;
    
    Level():
    kPauseLayerZ(1000),
    kManGunZ(100),
    kInvaderZ(80),
    kBulletZ(50),
    kGameOverZ(2000),
    manGunVelocity(cocos2d::Vec2(350.f, 0.f)),
    manGunHealth(100.f),
    manGunMaxHealth(100.f),
    manBulletVelocity(cocos2d::Vec2(0.f, 500.f)),
    manBulletSpawnDelay(0.5f),
    manBulletDamage(100.f),
    invaderVelocity(cocos2d::Vec2(300.f, 0.f)),
    invaderHealth(100.f),
    invaderMaxHealth(100.f),
    invaderBulletVelocity(cocos2d::Vec2(0.f, -800.f)),
    invaderSpawnDelay(1.f),
    invaderBulletDamage(100.f),
    invaderBulletSpawnDelay(1.f),
    invaderCount(15),
    invaderYOffset(20.f),
    invaderVelocityDelta(25.f),
    manGunCollideMask(BIN8(00000001)),
    manGunGroupID(1),
    manBulletCollideMask(BIN8(00000010)),
    manBulletGroupID(1),
    invaderCollideMask(BIN8(00000011)),
    invaderGroupID(2),
    invaderBulletCollideMask(BIN8(00000001)),
    invaderBulletGroupID(2),
    landHeight(0.f)
    {
        
    }
};

#endif /* Level_hpp */
