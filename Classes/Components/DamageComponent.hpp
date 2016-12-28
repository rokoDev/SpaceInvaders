//
//  DamageComponent.hpp
//  SpaceInvaders
//
//  Created by roko on 12/19/16.
//
//

#ifndef DamageComponent_hpp
#define DamageComponent_hpp

#include "cocos2d.h"

class DamageComponent:
public cocos2d::Component {
private:
    float m_damage;
    
public:
    float getDamage() const { return m_damage; }
    void setDamage(const float val) { m_damage = val; }
    
    static DamageComponent* create();
    static DamageComponent* create(const float damage);
    static void setValue(cocos2d::Node * pComponentContainerNode, const float damage);
    static float getValue(cocos2d::Node * pComponentContainerNode);
    
    ~DamageComponent();
    
    bool init() override;
    
    void update(float delta) override;
    
CC_CONSTRUCTOR_ACCESS:
    DamageComponent();
};

#endif /* DamageComponent_hpp */
