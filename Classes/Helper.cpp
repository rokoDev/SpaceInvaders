//
//  Helper.cpp
//  SpaceInvaders
//
//  Created by roko on 12/8/16.
//
//

#include "Helper.hpp"

#pragma mark AppDelegateProtocol class
void AppDelegateProtocol::callApplicationWillResignActive()
{
    sm_delegateInvoker.callDelegate([](AppDelegateProtocol * pProtocol){
        pProtocol->applicationWillResignActive();
    });
}

void AppDelegateProtocol::callApplicationDidBecomeActive()
{
    sm_delegateInvoker.callDelegate([](AppDelegateProtocol * pProtocol){
        pProtocol->applicationDidBecomeActive();
    });
}

void AppDelegateProtocol::callApplicationDidEnterBackground()
{
    sm_delegateInvoker.callDelegate([](AppDelegateProtocol * pProtocol){
        pProtocol->applicationDidEnterBackground();
    });
}

void AppDelegateProtocol::callApplicationWillEnterForeground()
{
    sm_delegateInvoker.callDelegate([](AppDelegateProtocol * pProtocol){
        pProtocol->applicationWillEnterForeground();
    });
}

void AppDelegateProtocol::callApplicationWillTerminate()
{
    sm_delegateInvoker.callDelegate([](AppDelegateProtocol * pProtocol){
        pProtocol->applicationWillTerminate();
    });
}

#pragma mark HelperFunctions

bool HelperFunctions::extractProperty(cocos2d::Node * pNode, cocos2d::Node * rootNode, const PropertyMap & properties) {
    auto it = properties.find(pNode->getName());
    if (properties.end() != it) {
        return (it->second)(pNode, rootNode);
    }
    return false;
}

void HelperFunctions::pauseRecursive(cocos2d::Node* _node, bool _pause)
{
    if(_pause)
        _node->pause();
    else
        _node->resume();
    
    auto& children = _node->getChildren();
    for (size_t i = 0; i < children.size(); i++)
    {
        pauseRecursive(children.at(i), _pause);
    }
}
