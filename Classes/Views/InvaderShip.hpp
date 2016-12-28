//
//  InvaderShip.hpp
//  SpaceInvaders
//
//  Created by roko on 12/13/16.
//
//

#ifndef InvaderShip_hpp
#define InvaderShip_hpp

#include "CSNodeIncludes.hpp"

#include "Helper.hpp"

class InvaderShip;

using ActiveShipT = std::set<InvaderShip *>;

class InvaderShip:
public cocos2d::ui::Layout {
    
    friend class InvaderShipReader;
    
private:
    static ActiveShipT sm_activeShips;
    static unsigned int sm_countCreatedDuringTheGame;
    CC_DISALLOW_COPY_AND_ASSIGN(InvaderShip);
    
protected:
    InvaderShip();
    virtual bool init() override;
    
    //synthesize properties from Cocos Studio 2
    ///////////////////////////////////////////
    //static const PropertyMap sm_properties;
public:
    bool unusedVar;
#define PROPERTY_TYPE_NAME           \
X(ImageView, MainImage)\
X(Layout, SpawnerBulletPanel)

#include "SYNTHESIZE_PROPERTIES.hpp"
    ///////////////////////////////////////////
    
public:
    virtual ~InvaderShip();
    
    CREATE_FUNC(InvaderShip)
    
    static InvaderShip * createDefault();
    
    void onExitTransitionDidStart() override;
    
    static const ActiveShipT & getActiveShips() { return sm_activeShips; }
    static unsigned int getCountCreatedDuringTheGame() { return sm_countCreatedDuringTheGame; }
    static void resetCountCreatedDuringTheGame() { sm_countCreatedDuringTheGame = 0; }
};

#endif /* InvaderShip_hpp */
