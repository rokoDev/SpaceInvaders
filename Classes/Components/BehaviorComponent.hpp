//
//  BehaviorComponent.hpp
//  SpaceInvaders
//
//  Created by roko on 12/13/16.
//
//

#ifndef BehaviorComponent_hpp
#define BehaviorComponent_hpp

#include "Behaviors.hpp"

class BehaviorComponent:
public cocos2d::Component {
private:
    BehaviorFunction m_behavior;
    
public:
    BehaviorFunction getBehavior() const { return m_behavior; }
    void setBehavior(const BehaviorFunction val) { m_behavior = val; }
    
    static BehaviorComponent* create();
    static BehaviorComponent* create(const BehaviorFunction behavior);
    static void setValue(cocos2d::Node * pComponentContainerNode, const BehaviorFunction behavior);
    
    ~BehaviorComponent();
    
    bool init() override;
    
    void update(float delta) override;
    
CC_CONSTRUCTOR_ACCESS:
    BehaviorComponent();
};

#endif /* BehaviorComponent_hpp */
