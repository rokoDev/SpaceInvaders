//
//  VelocityComponent.hpp
//  SpaceInvaders
//
//  Created by roko on 12/12/16.
//
//

#ifndef VelocityComponent_hpp
#define VelocityComponent_hpp

#include "cocos2d.h"

class VelocityComponent:
public cocos2d::Component {
private:
    cocos2d::Vec2 m_velocity;
    
public:
    const cocos2d::Vec2 & getVelocity() const { return m_velocity; }
    void setVelocity(const cocos2d::Vec2 & val) { m_velocity = val; }
    void setVelocityX(const float xVel) { m_velocity.x = xVel; }
    void setVelocityY(const float yVel) { m_velocity.y = yVel; }
    
    static VelocityComponent* create();
    static VelocityComponent* create(const cocos2d::Vec2 & velocity);
    static void setValue(cocos2d::Node * pComponentContainerNode, const cocos2d::Vec2 & velocity);
    
    ~VelocityComponent();
    
    bool init() override;
    
    void update(float delta) override;
    
CC_CONSTRUCTOR_ACCESS:
    VelocityComponent();
};

#endif /* VelocityComponent_hpp */
