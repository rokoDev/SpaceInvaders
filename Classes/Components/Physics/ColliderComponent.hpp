//
//  ColliderComponent.hpp
//  SpaceInvaders
//
//  Created by roko on 12/15/16.
//
//

#ifndef ColliderComponent_hpp
#define ColliderComponent_hpp

#include "PhysicsDefinitions.hpp"
#include "cocos2d.h"


class ColliderComponent:
public cocos2d::Component {
    friend class Grid;
    friend class PhysicsWorldComponent;
private:
    BitMaskType m_bitMask;
    GroupIDType m_groupID;
    IntPos m_leftBottomCellCoord;
    IntPos m_topRightCellCoord;
    size_t m_gridID;
    int m_ownerTag;
    
public:
    cocos2d::Rect getRect() const;
    BitMaskType getBitMask() const { return m_bitMask; }
    void setBitMask(const BitMaskType bitMask) { m_bitMask = bitMask; }
    GroupIDType getGroupID() const { return m_groupID; }
    void setGroupID(const GroupIDType groupID) { m_groupID = groupID; }
    int getOwnerTag() const { return m_ownerTag; }
    void setOwner(cocos2d::Node *owner) override { _owner = owner; if(owner) m_ownerTag = owner->getTag(); }
    
    static ColliderComponent* create();
    static ColliderComponent* create(const BitMaskType bitMask, const GroupIDType groupID);
    static void setValueAll(cocos2d::Node * pComponentContainerNode, const BitMaskType bitMask, const GroupIDType groupID);
    static void setValueBitMask(cocos2d::Node * pComponentContainerNode, const BitMaskType bitMask);
    static void setValueGroupID(cocos2d::Node * pComponentContainerNode, const GroupIDType groupID);
    
    ~ColliderComponent();
    
    bool init() override;
    
    void update(float delta) override;
    
    void onEnter() override;
    void onExit() override;
    
CC_CONSTRUCTOR_ACCESS:
    ColliderComponent();
};

#endif /* ColliderComponent_hpp */
