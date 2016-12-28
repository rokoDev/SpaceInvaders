//
//  Helper.hpp
//  SpaceInvaders
//
//  Created by roko on 12/8/16.
//
//

#ifndef Helper_hpp
#define Helper_hpp

#include <stdio.h>
#include <set>
#include <unordered_map>
#include <functional>
#include "cocos2d.h"

#define MY_STRINGIFY(x) MY_DO_STRINGIFY(x)
#define MY_DO_STRINGIFY(x) #x

template <class PROTOCOL_T>
class DelegateInvoker {
protected:
    std::set<PROTOCOL_T *> m_delegates;
    
public:
    ~DelegateInvoker() {}
    DelegateInvoker(): m_delegates({}) {};
    void addDelegate(PROTOCOL_T * pDelegate) { m_delegates.insert(pDelegate); }
    void removeDelegate(PROTOCOL_T * pDelegate) { m_delegates.erase(pDelegate); }
    
    void callDelegate(const std::function<void(PROTOCOL_T * )> & func);
};

template <class PROTOCOL_T>
void DelegateInvoker<PROTOCOL_T>::callDelegate(const std::function<void(PROTOCOL_T *)> & func)
{
    for (auto it = m_delegates.begin(); it != m_delegates.end(); ++it) {
        if (func) {
            func(*it);
        }
    }
}

template <class PROTOCOL_T>
class BaseProtocol {
protected:
    static DelegateInvoker<PROTOCOL_T> sm_delegateInvoker;
public:
    static void subscribe(PROTOCOL_T * pTarget);
    static void unsubscribe(PROTOCOL_T * pTarget);
    
    virtual ~BaseProtocol() = 0;
    BaseProtocol();
};

template <class PROTOCOL_T>
DelegateInvoker<PROTOCOL_T> BaseProtocol<PROTOCOL_T>::sm_delegateInvoker;

template <class PROTOCOL_T>
void BaseProtocol<PROTOCOL_T>::subscribe(PROTOCOL_T * pTarget)
{
    sm_delegateInvoker.addDelegate(pTarget);
}

template <class PROTOCOL_T>
void BaseProtocol<PROTOCOL_T>::unsubscribe(PROTOCOL_T * pTarget)
{
    sm_delegateInvoker.removeDelegate(pTarget);
}

template <class PROTOCOL_T>
BaseProtocol<PROTOCOL_T>::~BaseProtocol()
{
    BaseProtocol<PROTOCOL_T>::unsubscribe(static_cast<PROTOCOL_T *>(this));
}

template <class PROTOCOL_T>
BaseProtocol<PROTOCOL_T>::BaseProtocol()
{
    BaseProtocol<PROTOCOL_T>::subscribe(static_cast<PROTOCOL_T *>(this));
}

#pragma mark AppDelegateProtocol class
class AppDelegateProtocol:
public BaseProtocol<AppDelegateProtocol> {
    
public:
    static void callApplicationWillResignActive();
    static void callApplicationDidBecomeActive();
    static void callApplicationDidEnterBackground();
    static void callApplicationWillEnterForeground();
    static void callApplicationWillTerminate();
    
    virtual void applicationWillResignActive(){}
    virtual void applicationDidBecomeActive(){}
    virtual void applicationDidEnterBackground(){}
    virtual void applicationWillEnterForeground(){}
    virtual void applicationWillTerminate(){}
    
};

#pragma mark HelperFunctions

using propertySetterCallback = std::function<bool(cocos2d::Node *, cocos2d::Node *)>;
using PropertyMap = std::unordered_map<std::string, propertySetterCallback>;

class HelperFunctions {
    
public:
    static bool extractProperty(cocos2d::Node * pNode, cocos2d::Node * rootNode, const PropertyMap & properties);
    static void pauseRecursive(cocos2d::Node* _node, bool _pause);
};

#define CALL_MEMBER_FN(object,ptrToMember)  ((object)->*(ptrToMember))

inline constexpr unsigned char operator "" _uchar( unsigned long long arg ) noexcept
{
    return static_cast< unsigned char >( arg );
}

enum class MoveDirection : int {
    None,
    Idle,
    Left,
    Right
};

enum class ObjectTag : int {
    ManGun,
    InvaderShip,
    ManBullet,
    InvaderBullet,
    TAG_COUNT
};

#define OBJECT_TAG_COUNT static_cast<int>(ObjectTag::TAG_COUNT)

#endif /* Helper_hpp */
