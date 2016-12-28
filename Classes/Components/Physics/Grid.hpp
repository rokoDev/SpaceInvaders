//
//  Grid.hpp
//  SpaceInvaders
//
//  Created by roko on 12/9/16.
//
//

#ifndef Grid_hpp
#define Grid_hpp

#include "cocos2d.h"
#include <map>
#include <unordered_set>
#include "PhysicsDefinitions.hpp"
#include "TriangleBitMatrix.hpp"
#include <set>

class Grid {
    friend class PhysicsDebugNode;
private:
    using Cell = std::map<GroupIDType, std::set<ColliderComponent *>>;
    IntSize m_dim;
    cocos2d::Size m_cellSize;
    std::vector<std::vector<Cell>> m_cells;
    std::set<Cell *> m_cellsWithMoreThanOneGroups;
    std::unordered_set<ColliderComponent *> m_colliders;
    PhysicsWorldComponent * m_PW;
    TriangleBitMatrix m_bitMatrix;
    std::vector<size_t> m_freeIDs;
    std::unordered_set<size_t> m_busyIDs;
    bool m_isActiveStep;
    std::vector<ColliderComponent *> m_addedDuringActiveStep;
    std::vector<ColliderComponent *> m_remvoedDuringActiveStep;
    IntPos cellCoordForPos(const cocos2d::Vec2 & pos);
    void insertColliderComponent(ColliderComponent * pCollider, IntPos leftBottomCellCoord, IntPos topRightCellCoord);
    void removeColliderComponent(ColliderComponent * pCollider, IntPos leftBottomCellCoord, IntPos topRightCellCoord);
    void updateCellsForCollider(ColliderComponent * pCollider);
    bool giveIDTo(ColliderComponent * pCollider);
    void takeIDAwayFrom(ColliderComponent * pCollider);
    bool isCheckedColliders(ColliderComponent * pCollider1, ColliderComponent * pCollider2) const;
    void setCollidersAsChecked(ColliderComponent * pCollider1, ColliderComponent * pCollider2);
    void resetCheckedState();
    
    typedef void (Grid::*Insert_Remove)(ColliderComponent * pCollider);
    void postStepProcess(std::vector<ColliderComponent *> & vec, Insert_Remove callback);
public:
    Grid(const IntSize dim, const cocos2d::Size & cellSize, const size_t supposedColliderCount = 100);
    
    void setPhysicsWorldComponent(PhysicsWorldComponent * pWorld) { m_PW = pWorld; }
    PhysicsWorldComponent * getPhysicsWorldComponent() { return m_PW; }
    
    void insertColliderComponent(ColliderComponent * pCollider);
    void removeColliderComponent(ColliderComponent * pCollider);
    void updateCells(float dt);
    void collisionCheck();
    
    Grid() = delete;
    Grid(Grid const&) = delete;
    Grid(Grid&&) = delete;
    Grid& operator=(Grid const&) = delete;
    Grid& operator=(Grid &&) = delete;
};

#endif /* Grid_hpp */
