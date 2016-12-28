//
//  ManGun.hpp
//  SpaceInvaders
//
//  Created by roko on 12/13/16.
//
//

#ifndef ManGun_hpp
#define ManGun_hpp

#include "CSNodeIncludes.hpp"

#include "Helper.hpp"

class ManGun:
public cocos2d::ui::Layout {
    
    friend class ManGunReader;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(ManGun);
    
protected:
    ManGun();
    virtual bool init() override;
    
    //synthesize properties from Cocos Studio 2
    ///////////////////////////////////////////
    //static const PropertyMap sm_properties;
public:
    bool unusedVar;
#define PROPERTY_TYPE_NAME           \
X(ImageView, MainImage)\
X(Layout, SpawnBulletPanel)
    
#include "SYNTHESIZE_PROPERTIES.hpp"
    ///////////////////////////////////////////
    
public:
    virtual ~ManGun();
    
    CREATE_FUNC(ManGun)
    
    static ManGun * createDefault();
};

#endif /* ManGun_hpp */
