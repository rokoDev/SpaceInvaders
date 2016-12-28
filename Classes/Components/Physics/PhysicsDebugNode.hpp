//
//  PhysicsDebugNode.hpp
//  SpaceInvaders
//
//  Created by roko on 12/17/16.
//
//

#ifndef PhysicsDebugNode_hpp
#define PhysicsDebugNode_hpp

#include "cocos2d.h"

class PhysicsWorldComponent;

class PhysicsDebugNode: public cocos2d::DrawNode {
protected:
    PhysicsWorldComponent * m_pPhysicsWorld;
    cocos2d::Color4F m_gridColor;
    
    void updateGridLines();
public:
    static PhysicsDebugNode * create(int defaultLineWidth = cocos2d::DEFAULT_LINE_WIDTH);
    
    PhysicsWorldComponent * getPhysicsWorldComponent() const { return m_pPhysicsWorld; }
    void setPhysicsWorldComponent(PhysicsWorldComponent * pComponent);
    
    const cocos2d::Color4F & getGridColor() const { return m_gridColor; }
    void setGridColor(const cocos2d::Color4F & gridColor) { m_gridColor = gridColor; }
    
CC_CONSTRUCTOR_ACCESS:
    PhysicsDebugNode(int lineWidth = cocos2d::DEFAULT_LINE_WIDTH);
    ~PhysicsDebugNode();
    bool init() override;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(PhysicsDebugNode);
};

#endif /* PhysicsDebugNode_hpp */
