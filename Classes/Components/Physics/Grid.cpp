//
//  Grid.cpp
//  SpaceInvaders
//
//  Created by roko on 12/9/16.
//
//

#include "Grid.hpp"
#include "ColliderComponent.hpp"
#include "PhysicsWorldComponent.hpp"
#include "Helper.hpp"

USING_NS_CC;

#pragma makr Grid methods

Grid::Grid(const IntSize dim, const cocos2d::Size & cellSize, const size_t supposedColliderCount):
m_dim(dim),
m_cellSize(cellSize),
m_cells(dim.w, std::vector<Cell>(dim.h)),
m_colliders(supposedColliderCount/2),
m_PW(nullptr),
m_bitMatrix(supposedColliderCount, supposedColliderCount),
m_freeIDs(supposedColliderCount),
m_busyIDs(supposedColliderCount),
m_isActiveStep(false)
{
    m_colliders.reserve(supposedColliderCount);
    for (int i = 1; i <= supposedColliderCount; ++i) {
        m_freeIDs.push_back(i);
    }
}

IntPos Grid::cellCoordForPos(const cocos2d::Vec2 & pos)
{
    size_t x = pos.x / m_cellSize.width;
    size_t y = pos.y / m_cellSize.height;
    return IntPos(x, y);
}

void Grid::insertColliderComponent(ColliderComponent * pCollider, IntPos leftBottomCellCoord, IntPos topRightCellCoord)
{
    for (auto i = leftBottomCellCoord.x; i <= topRightCellCoord.x; ++i) {
        for (auto j = leftBottomCellCoord.y; j <= topRightCellCoord.y; ++j) {
            auto & cell = m_cells[i][j];
            cell[pCollider->getGroupID()].insert(pCollider);
            if (cell.size() > 1) {
                m_cellsWithMoreThanOneGroups.insert(&cell);
            }
        }
    }
}

void Grid::removeColliderComponent(ColliderComponent * pCollider, IntPos leftBottomCellCoord, IntPos topRightCellCoord)
{
    for (auto i = leftBottomCellCoord.x; i <= topRightCellCoord.x; ++i) {
        for (auto j = leftBottomCellCoord.y; j <= topRightCellCoord.y; ++j) {
            auto & cell = m_cells[i][j];
            cell[pCollider->getGroupID()].erase(pCollider);
            if (!(cell.size() > 1)) {
                m_cellsWithMoreThanOneGroups.erase(&cell);
            }
        }
    }
}

void Grid::updateCellsForCollider(ColliderComponent * pCollider)
{
    auto old_LB = pCollider->m_leftBottomCellCoord;
    auto old_TR = pCollider->m_topRightCellCoord;
    
    Rect r = pCollider->getRect();
    auto new_LB = cellCoordForPos(r.origin);
    auto new_TR = cellCoordForPos(r.origin + r.size);
    
    removeColliderComponent(pCollider, old_LB, old_TR);
    insertColliderComponent(pCollider, new_LB, new_TR);
    
    pCollider->m_leftBottomCellCoord = std::move(new_LB);
    pCollider->m_topRightCellCoord = std::move(new_TR);
}

bool Grid::giveIDTo(ColliderComponent * pCollider)
{
    if (m_freeIDs.empty()) {
        return false;
    }
    
    pCollider->m_gridID = m_freeIDs.back();
    m_freeIDs.pop_back();
    m_busyIDs.insert(pCollider->m_gridID);
    
    return true;
}

void Grid::takeIDAwayFrom(ColliderComponent * pCollier)
{
    m_freeIDs.push_back(pCollier->m_gridID);
    m_busyIDs.erase(pCollier->m_gridID);
}

inline bool Grid::isCheckedColliders(ColliderComponent * pCollider1, ColliderComponent * pCollider2) const
{
    return m_bitMatrix.get(pCollider1->m_gridID, pCollider2->m_gridID);
}

inline void Grid::setCollidersAsChecked(ColliderComponent * pCollider1, ColliderComponent * pCollider2)
{
    m_bitMatrix.set(pCollider1->m_gridID, pCollider2->m_gridID, true);
}

inline void Grid::resetCheckedState()
{
    m_bitMatrix.resetAllBits();
}

void Grid::postStepProcess(std::vector<ColliderComponent *> & vec, Insert_Remove callback)
{
    for (auto pCollider : vec) {
        CALL_MEMBER_FN(this, callback)(pCollider);
    }
    vec.clear();
}

void Grid::insertColliderComponent(ColliderComponent * pCollider)
{
    if (m_isActiveStep) {
        m_addedDuringActiveStep.push_back(pCollider);
        return;
    }
    
    if (!giveIDTo(pCollider)) {
        CCLOG("Physics IDs are exhausted!");
        return;
    }
    
    pCollider->retain();
    
    Rect r = pCollider->getRect();
    auto leftBottomCellCoord = cellCoordForPos(r.origin);
    auto topRightCellCoord = cellCoordForPos(r.origin + r.size);
    
    insertColliderComponent(pCollider, leftBottomCellCoord, topRightCellCoord);
    
    pCollider->m_leftBottomCellCoord = std::move(leftBottomCellCoord);
    pCollider->m_topRightCellCoord = std::move(topRightCellCoord);
    
    m_colliders.insert(pCollider);
}

void Grid::removeColliderComponent(ColliderComponent * pCollider)
{
    if (m_isActiveStep) {
        m_remvoedDuringActiveStep.push_back(pCollider);
        return;
    }
    
    takeIDAwayFrom(pCollider);
    
    auto leftBottomCellCoord = pCollider->m_leftBottomCellCoord;
    auto topRightCellCoord = pCollider->m_topRightCellCoord;
    
    removeColliderComponent(pCollider, std::move(leftBottomCellCoord), std::move(topRightCellCoord));
    
    m_colliders.erase(pCollider);
    
    pCollider->release();
}

void Grid::updateCells(float dt)
{
    for (auto pCollider : m_colliders) {
        updateCellsForCollider(pCollider);
    }
}

void Grid::collisionCheck()
{
    if (!m_PW) {
        return;
    }
    
    m_isActiveStep = true;
    
    for (auto pCell : m_cellsWithMoreThanOneGroups) {
        for (auto it1 = pCell->cbegin(); it1 != --pCell->cend(); ++it1) {
            auto it2Begin = it1;
            ++it2Begin;
            for (auto it2 = it2Begin; it2 != pCell->cend(); ++it2) {
                const auto & set1 = it1->second;
                const auto & set2 = it2->second;
                for (auto pCollider1 : set1) {
                    for (auto pCollider2 : set2) {
                        if (!isCheckedColliders(pCollider1, pCollider2)) {
                            if (m_PW->hitCheck(pCollider1, pCollider2)) {
                                m_PW->objectsCollided(pCollider1, pCollider2);
                            }
                            setCollidersAsChecked(pCollider1, pCollider2);
                        }
                    }
                }
            }
        }
    }
    resetCheckedState();
    
    m_PW->physicsStepCompleted();
    
    m_isActiveStep = false;
    
    postStepProcess(m_remvoedDuringActiveStep, &Grid::removeColliderComponent);
    postStepProcess(m_addedDuringActiveStep, &Grid::insertColliderComponent);
}





