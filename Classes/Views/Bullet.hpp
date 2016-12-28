//
//  Bullet.hpp
//  SpaceInvaders
//
//  Created by roko on 12/13/16.
//
//

#ifndef Bullet_hpp
#define Bullet_hpp

#include "CSNodeIncludes.hpp"

#include "Helper.hpp"

class Bullet:
public cocos2d::ui::Layout {
    
    friend class BulletReader;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(Bullet);
    
protected:
    Bullet();
    virtual bool init() override;
    
    //synthesize properties from Cocos Studio 2
    ///////////////////////////////////////////
    //static const PropertyMap sm_properties;
public:
    bool unusedVar;
#define PROPERTY_TYPE_NAME           \
X(ImageView, MainImage)\

#include "SYNTHESIZE_PROPERTIES.hpp"
    ///////////////////////////////////////////
    
public:
    virtual ~Bullet();
    
    CREATE_FUNC(Bullet)
    
    static Bullet * createDefault();
};

#endif /* Bullet_hpp */
