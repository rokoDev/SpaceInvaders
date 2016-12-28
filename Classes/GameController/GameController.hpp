//
//  GameController.hpp
//  SpaceInvaders
//
//  Created by roko on 12/14/16.
//
//

#ifndef GameController_hpp
#define GameController_hpp

#include "CSNodeIncludes.hpp"
#include "Helper.hpp"
#include "PhysicsDefinitions.hpp"

#define SCREEN_RECT GameController::getInstance().getScreenRect()
#define GAME_CONTROLLER GameController::getInstance()
#define CUR_LEVEL GameController::getInstance().getLevel()

class Level;

class GameController:
public AppDelegateProtocol,
public CollisionHandlerProtocol
{
public:
    static GameController & getInstance();
    
    GameController(GameController const&) = delete;
    GameController(GameController&&) = delete;
    GameController& operator=(GameController const&) = delete;
    GameController& operator=(GameController &&) = delete;
    
protected:
    GameController();
    ~GameController();
    
private:
    struct Impl;
    std::unique_ptr<Impl> m_pImpl;
    
public:
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
    void objectHasReachedSurface(cocos2d::Node * pNode);
    
#pragma mark CollisionHandlerProtocol
    void physicsStepDidFinish() override;
    void invaderBullet_CollidedWith_ManGun(ColliderComponent * pBulletCollider, ColliderComponent * pManGunCollider) override;
    void manBullet_CollidedWith_InvaderShip(ColliderComponent * pBulletCollider, ColliderComponent * pInvaderShipCollider) override;
    void invaderShip_CollidedWith_ManGun(ColliderComponent * pInvaderShipCollider, ColliderComponent * pManGunCollider) override;
    
#pragma mark AppDelegateProtocol
    void applicationWillResignActive() override;
};

#endif /* GameController_hpp */
