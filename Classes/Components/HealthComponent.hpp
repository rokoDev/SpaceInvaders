//
//  HealthComponent.hpp
//  SpaceInvaders
//
//  Created by roko on 12/12/16.
//
//

#ifndef HealthComponent_hpp
#define HealthComponent_hpp

#include "cocos2d.h"

class HealthComponent:
public cocos2d::Component {
private:
    float m_health;
    float m_maxHealth;
    
public:
    const float & getHealth() const { return m_health; }
    float setHealth(const float val);
    float addHealth(const float val);
    float subHealth(const float val);
    
    const float & getMaxHealth() const { return m_maxHealth; }
    void setMaxHealth(const float val);
    
    static HealthComponent* create();
    static HealthComponent* create(const float health, const float maxHealth);
    static void setValueAll(cocos2d::Node * pComponentContainerNode, const float health, const float maxHealth);
    static float setHealth(cocos2d::Node * pComponentContainerNode, const float health);
    static float addHealth(cocos2d::Node * pComponentContainerNode, const float health);
    static float subHealth(cocos2d::Node * pComponentContainerNode, const float health);
    static void setValueMaxHealth(cocos2d::Node * pComponentContainerNode, const float maxHealth);
    
    ~HealthComponent();
    
    bool init() override;
    
    void update(float delta) override;
    
CC_CONSTRUCTOR_ACCESS:
    HealthComponent();
};

#endif /* HealthComponent_hpp */
