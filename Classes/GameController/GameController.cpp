//
//  GameController.cpp
//  SpaceInvaders
//
//  Created by roko on 12/14/16.
//
//

#include "GameController.hpp"
#include "MakeUnique.h"
#include "ManGun.hpp"
#include "PauseLayer.hpp"
#include "GameScene.hpp"
#include "StartScene.hpp"
#include "BehaviorComponent.hpp"
#include "HealthComponent.hpp"
#include "VelocityComponent.hpp"
#include "GameObjectFactory.hpp"
#include "Level.hpp"
#include "InvaderShip.hpp"
#include "PhysicsWorldComponent.hpp"
#include "ColliderComponent.hpp"
#include "BinMacro.h"
#include "GameOverLayer.hpp"
#include "CollisionHandler.hpp"
#include "ComponentDefinitions.hpp"
#include "DamageComponent.hpp"
#include <unordered_set>


USING_NS_CC;

using namespace cocos2d::ui;

struct GameController::Impl:
public CollisionHandlerProtocol
{
    Impl();
    bool m_isPaused;
    bool m_isGameOver;
    PauseLayer * m_pPauseLayer;
    GameScene * m_pGameScene;
    ManGun * m_pManGun;
    Level m_level;
    Rect m_screenRect;
    std::unordered_set<ColliderComponent *> m_hitList;
    size_t m_invaderShipDestroyedCount;
    CollisionHandler m_collisionHandler;
    
    void runStartMenu();
    void startNewGame();
    void pauseGame();
    void resumeGame();
    bool isGamePaused() const;
    void exitToMenu();
    
    void addGameObject(cocos2d::Node * pNode);
    void removeGameObject(cocos2d::Node * pNode);
    void moveManGun(cocos2d::Ref * sender, const MoveDirection direction);
    
    Level const * const getLevel() const;
    
    const cocos2d::Rect & getScreenRect() const;
    
private:
    static Scene * createSceneWithNode(Node * pNode);
    void resetGameVariables();
    void initGame();
    void increaseAllInvadersVelocity();
    
public:
    void physicsStepDidFinish() override;
    void invaderBullet_CollidedWith_ManGun(ColliderComponent * pBulletCollider, ColliderComponent * pManGunCollider) override;
    void manBullet_CollidedWith_InvaderShip(ColliderComponent * pBulletCollider, ColliderComponent * pInvaderShipCollider) override;
    void invaderShip_CollidedWith_ManGun(ColliderComponent * pInvaderShipCollider, ColliderComponent * pManGunCollider) override;
    
private:
    void removeCollidedObject(ColliderComponent * pCollider);
    bool didRemoved(ColliderComponent * pCollider);
    bool isDeadAfterHurt(ColliderComponent * pHunter, ColliderComponent * pVictim);
    void freezeGame();
    void unfreezeGame();
    
public:
    void gameLost();
    void gameWon();
    void objectHasReachedSurface(cocos2d::Node * pNode);
    
};

#pragma mark Impl methods

GameController::Impl::Impl():
m_pPauseLayer(nullptr),
m_pGameScene(nullptr),
m_pManGun(nullptr),
m_isPaused(false),
m_isGameOver(false),
m_invaderShipDestroyedCount(0)
{
    m_hitList.reserve(50);
}

void GameController::Impl::runStartMenu()
{
    auto pLayer = StartScene::createDefault();
    auto pScene = createSceneWithNode(pLayer);
    Director::getInstance()->runWithScene(pScene);
}

void GameController::Impl::startNewGame()
{
    initGame();
    auto pScene = createSceneWithNode(m_pGameScene);
    Director::getInstance()->replaceScene(pScene);
}

void GameController::Impl::pauseGame()
{
    if (!m_isPaused && !m_isGameOver) {
        if (m_pPauseLayer && !(m_pPauseLayer->getParent())) {
            m_pGameScene->addChild(m_pPauseLayer, m_level.kPauseLayerZ);
        }
        freezeGame();
        this->moveManGun(nullptr, MoveDirection::Idle);
        m_isPaused = true;
    }
}

void GameController::Impl::resumeGame()
{
    if (m_isPaused) {
        if (m_pPauseLayer && m_pPauseLayer->getParent()) {
            m_pPauseLayer->removeFromParent();
        }
        unfreezeGame();
        m_isPaused = false;
    }
}

bool GameController::Impl::isGamePaused() const
{
    return m_isPaused;
}

void GameController::Impl::exitToMenu()
{
    auto pLayer = StartScene::createDefault();
    auto pScene = createSceneWithNode(pLayer);
    Director::getInstance()->replaceScene(pScene);
}

void GameController::Impl::addGameObject(cocos2d::Node * pNode)
{
    m_pGameScene->getObjectPanel()->addChild(pNode);
}

void GameController::Impl::removeGameObject(cocos2d::Node * pNode)
{
    pNode->removeFromParent();
}

void GameController::Impl::moveManGun(cocos2d::Ref * sender, const MoveDirection direction)
{
    switch (direction) {
        case MoveDirection::Idle:
        {
            VelocityComponent::setValue(m_pManGun, Vec2::ZERO);
            break;
        }
        case MoveDirection::Left:
        {
            VelocityComponent::setValue(m_pManGun, Vec2(-m_level.manGunVelocity.x, m_level.manGunVelocity.y));
            break;
        }
        case MoveDirection::Right:
        {
            VelocityComponent::setValue(m_pManGun, Vec2(m_level.manGunVelocity.x, m_level.manGunVelocity.y));
            break;
        }
        default:
            break;
    }
}

Level const * const GameController::Impl::getLevel() const
{
    return &m_level;
}

const cocos2d::Rect & GameController::Impl::getScreenRect() const
{
    return m_screenRect;
}

Scene * GameController::Impl::createSceneWithNode(Node * pNode)
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // add layer as a child to scene
    scene->addChild(pNode);
    
    // return the scene
    return scene;
}

void GameController::Impl::resetGameVariables()
{
    m_isPaused = false;
    m_isGameOver = false;
    
    if (m_pPauseLayer) {
        m_pPauseLayer->release();
        m_pPauseLayer = nullptr;
    }
    
    m_pGameScene = nullptr;
    m_pManGun = nullptr;
    
    InvaderShip::resetCountCreatedDuringTheGame();
    m_invaderShipDestroyedCount = 0;
}

void GameController::Impl::initGame()
{
    resetGameVariables();
    
    m_level = Level();
    
    m_pPauseLayer = PauseLayer::createDefault();
    m_pPauseLayer->retain();
    
    m_pGameScene = GameScene::createDefault();
    
    auto wins = Director::getInstance()->getWinSize();
    m_screenRect = {m_pGameScene->getObjectPanel()->convertToNodeSpace(Vec2::ZERO), wins};
    
    //set up physics
    m_collisionHandler.setDelegate(&GAME_CONTROLLER);
    auto gridSize = m_pGameScene->getObjectPanel()->getContentSize();
    IntPos dim(20, 30);
    Size cellSize(gridSize.width/dim.w, gridSize.height/dim.h);
    auto physicWorld = PhysicsWorldComponent::create(std::move(dim), Size(cellSize.width, cellSize.height), 200);
    physicWorld->setDelegate(&m_collisionHandler);
    physicWorld->setDebugDraw(false);
    m_pGameScene->getObjectPanel()->addComponent(physicWorld);
    m_pGameScene->getObjectPanel()->unscheduleUpdate();
    m_pGameScene->getObjectPanel()->scheduleUpdateWithPriority(10);
    
    
    //set up ManGun
    m_pManGun = static_cast<ManGun *>(GameObjectFactory::createObject(GameObjectFactory::ObjectType::kManGun, Vec2::ZERO));
    auto manGunPos = m_pGameScene->getObjectPanel()->convertToNodeSpace(m_pGameScene->getInitHeroPlacePanel()->convertToWorldSpace(Vec2::ZERO));
    m_pManGun->setPosition(manGunPos);//(m_pGameScene->getInitHeroPlacePanel()->getPosition());
    m_pManGun->setLocalZOrder(m_level.kManGunZ);
    m_pManGun->addComponent(ColliderComponent::create(CUR_LEVEL->manGunCollideMask, CUR_LEVEL->manGunGroupID));
    GameController::getInstance().addGameObject(m_pManGun);
    
    m_level.landHeight = manGunPos.y;
    
    //set up invaders
    const int kActSpawnInvaderTag = 111;
    
    Action * invaderSpawnAct = RepeatForever::create(Sequence::create(CallFunc::create([kActSpawnInvaderTag, this](){
        if (InvaderShip::getCountCreatedDuringTheGame() < m_level.invaderCount) {
            auto pInvader = GameObjectFactory::createObject(GameObjectFactory::ObjectType::kInvaderShip, m_level.invaderVelocity);
            pInvader->setPosition(m_pGameScene->getInvaderSpawnerPanel()->getPosition());
            pInvader->setLocalZOrder(m_level.kInvaderZ);
            pInvader->addComponent(ColliderComponent::create(CUR_LEVEL->invaderCollideMask, CUR_LEVEL->invaderGroupID));
            GameController::getInstance().addGameObject(pInvader);
            if (InvaderShip::getCountCreatedDuringTheGame() >= m_level.invaderCount) {
                m_pGameScene->getInvaderSpawnerPanel()->stopActionByTag(kActSpawnInvaderTag);
            }
        }
    }), DelayTime::create(m_level.invaderSpawnDelay), NULL));
    
    invaderSpawnAct->setTag(kActSpawnInvaderTag);
    
    m_pGameScene->getInvaderSpawnerPanel()->runAction(invaderSpawnAct);
}

void GameController::Impl::increaseAllInvadersVelocity()
{
    m_level.invaderVelocity.x += m_level.invaderVelocityDelta;
    for (auto pInvader : InvaderShip::getActiveShips()) {
        VelocityComponent * pVel = static_cast<VelocityComponent*>(pInvader->getComponent(kVelocityKeyStr));
        if (pVel) {
            pVel->setVelocityX(copysignf(m_level.invaderVelocity.x, pVel->getVelocity().x));
        }
    }
}

void GameController::Impl::physicsStepDidFinish()
{
    m_hitList.clear();
}

void GameController::Impl::invaderBullet_CollidedWith_ManGun(ColliderComponent * pBulletCollider, ColliderComponent * pManGunCollider)
{
    CCLOG("bullet hit ManGun");
    if (!didRemoved(pBulletCollider) && !didRemoved(pManGunCollider)) {
        if (isDeadAfterHurt(pBulletCollider, pManGunCollider)) {
            gameLost();
        }
        removeCollidedObject(pBulletCollider);
    }
}

void GameController::Impl::manBullet_CollidedWith_InvaderShip(ColliderComponent * pBulletCollider, ColliderComponent * pInvaderShipCollider)
{
    CCLOG("bullet hit InvaderShip");
    if (!didRemoved(pBulletCollider) && !didRemoved(pInvaderShipCollider)) {
        if (isDeadAfterHurt(pBulletCollider, pInvaderShipCollider)) {
            removeCollidedObject(pInvaderShipCollider);
            ++m_invaderShipDestroyedCount;
            if (m_invaderShipDestroyedCount >= m_level.invaderCount) {
                gameWon();
            }
            increaseAllInvadersVelocity();
        }
        removeCollidedObject(pBulletCollider);
    }
}

void GameController::Impl::invaderShip_CollidedWith_ManGun(ColliderComponent * pInvaderShipCollider, ColliderComponent * pManGunCollider)
{
    CCLOG("InvaderShip hit ManGun");
    removeCollidedObject(pInvaderShipCollider);
    gameLost();
}

void GameController::Impl::removeCollidedObject(ColliderComponent * pCollider)
{
    if (!didRemoved(pCollider)) {
        pCollider->getOwner()->removeFromParent();
        m_hitList.insert(pCollider);
    }
}

bool GameController::Impl::didRemoved(ColliderComponent * pCollider)
{
    return m_hitList.end() != m_hitList.find(pCollider);
}

bool GameController::Impl::isDeadAfterHurt(ColliderComponent * pHunter, ColliderComponent * pVictim)
{
    return (HealthComponent::subHealth(pVictim->getOwner(), DamageComponent::getValue(pHunter->getOwner())) <= 0);
}

void GameController::Impl::freezeGame()
{
    m_pGameScene->getObjectPanel()->enumerateChildren("//[[:alnum:]]*", [this](Node * pNode) -> bool {
        pNode->pause();
        return false;
    });
}

void GameController::Impl::unfreezeGame()
{
    m_pGameScene->getObjectPanel()->enumerateChildren("//[[:alnum:]]*", [this](Node * pNode) -> bool {
        pNode->resume();
        return false;
    });
}

void GameController::Impl::gameLost()
{
    if (!m_isGameOver && !m_isPaused) {
        m_isGameOver = true;
        freezeGame();
        
        auto gameOverLayer = GameOverLayer::createDefault();
        gameOverLayer->getFinishText()->setString("YOU LOSE!");
        m_pGameScene->addChild(gameOverLayer, m_level.kGameOverZ);
    }
}

void GameController::Impl::gameWon()
{
    if (!m_isGameOver && !m_isPaused) {
        m_isGameOver = true;
        freezeGame();
        
        auto gameOverLayer = GameOverLayer::createDefault();
        gameOverLayer->getFinishText()->setString("YOU WON!");
        m_pGameScene->addChild(gameOverLayer, m_level.kGameOverZ);
    }
}

void GameController::Impl::objectHasReachedSurface(cocos2d::Node * pNode)
{
    auto pInvader = dynamic_cast<InvaderShip *>(pNode);
    if (pInvader) {
        this->gameLost();
    }
}

#pragma mark GameController methods

GameController & GameController::getInstance()
{
    static GameController s_instance;
    return s_instance;
}

GameController::GameController():
m_pImpl(std::make_unique<Impl>())
{
    
}

GameController::~GameController()
{
    
}

void GameController::runStartMenu()
{
    m_pImpl->runStartMenu();
}

void GameController::startNewGame()
{
    m_pImpl->startNewGame();
}

void GameController::pauseGame()
{
    m_pImpl->pauseGame();
}

void GameController::resumeGame()
{
    m_pImpl->resumeGame();
}

bool GameController::isGamePaused() const
{
    return m_pImpl->isGamePaused();
}

void GameController::exitToMenu()
{
    m_pImpl->exitToMenu();
}

void GameController::addGameObject(cocos2d::Node * pNode)
{
    m_pImpl->addGameObject(pNode);
}

void GameController::removeGameObject(cocos2d::Node * pNode)
{
    m_pImpl->removeGameObject(pNode);
}

void GameController::moveManGun(cocos2d::Ref * sender, const MoveDirection direction)
{
    m_pImpl->moveManGun(sender, direction);
}

Level const * const GameController::getLevel() const
{
    return m_pImpl->getLevel();
}

const cocos2d::Rect & GameController::getScreenRect() const
{
    return m_pImpl->getScreenRect();
}

void GameController::objectHasReachedSurface(cocos2d::Node * pNode)
{
    m_pImpl->objectHasReachedSurface(pNode);
}

#pragma CollisionHandlerProtocol
void GameController::physicsStepDidFinish()
{
    m_pImpl->physicsStepDidFinish();
}

void GameController::invaderBullet_CollidedWith_ManGun(ColliderComponent * pBulletCollider, ColliderComponent * pManGunCollider)
{
    m_pImpl->invaderBullet_CollidedWith_ManGun(pBulletCollider, pManGunCollider);
}

void GameController::manBullet_CollidedWith_InvaderShip(ColliderComponent * pBulletCollider, ColliderComponent * pInvaderShipCollider)
{
    m_pImpl->manBullet_CollidedWith_InvaderShip(pBulletCollider, pInvaderShipCollider);
}

void GameController::invaderShip_CollidedWith_ManGun(ColliderComponent * pInvaderShipCollider, ColliderComponent * pManGunCollider)
{
    m_pImpl->invaderShip_CollidedWith_ManGun(pInvaderShipCollider, pManGunCollider);
}

#pragma mark AppDelegateProtocol
void GameController::applicationWillResignActive()
{
    CCLOG("applicationWillResignActive");
    this->pauseGame();
}
