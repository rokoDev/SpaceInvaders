//
//  RegisterCustomReaders.hpp
//  MightyClickers
//
//  Created by jam on 1/12/16.
//
//

#ifndef RegisterCustomReaders_hpp
#define RegisterCustomReaders_hpp

#include <stdio.h>
#include "editor-support/cocostudio/CocoStudio.h"
#include "editor-support/cocostudio/WidgetReader/NodeReader/NodeReader.h"

#define READER_HEADER_FOR(Class_Name) \
class Class_Name;\
class Class_Name##Reader : public cocostudio::NodeReader \
{ \
public:\
static Class_Name * sm_pTmpNode;\
static cocos2d::ccNodeLoadCallback sm_nodeLoadCallback;\
Class_Name##Reader() {};\
~Class_Name##Reader() {};\
static Class_Name##Reader* getInstance();\
static void purge();\
cocos2d::Node* createNodeWithFlatBuffers(const flatbuffers::Table* node##Class_Name);\
};

#define READER_DEFINITION_FOR(Class_Name) \
Class_Name * Class_Name##Reader::sm_pTmpNode = nullptr;\
cocos2d::ccNodeLoadCallback Class_Name##Reader::sm_nodeLoadCallback = [](cocos2d::Ref * pRef) {\
if (Class_Name##Reader::sm_pTmpNode) {\
    cocos2d::Node * pNode = dynamic_cast<cocos2d::Node *>(pRef);\
    if (!pNode) {\
        return;\
    }\
    \
    if (HelperFunctions::extractProperty(pNode, Class_Name##Reader::sm_pTmpNode, Class_Name::sm_properties)) {\
    }\
}\
};\
static Class_Name##Reader* _instance##Class_Name##Reader = nullptr;\
Class_Name##Reader* Class_Name##Reader::getInstance()\
\
{\
if (!_instance##Class_Name##Reader)\
{\
_instance##Class_Name##Reader = new Class_Name##Reader();\
}\
return _instance##Class_Name##Reader;\
}\
\
void Class_Name##Reader::purge()\
{\
CC_SAFE_DELETE(_instance##Class_Name##Reader);\
}\
\
Node* Class_Name##Reader::createNodeWithFlatBuffers(const flatbuffers::Table *node##Class_Name)\
{\
Class_Name* node = Class_Name::create();\
sm_pTmpNode = node;\
setPropsWithFlatBuffers(node, node##Class_Name);\
return node;\
}

#define READERTYPES  \
X(StartScene)     \
X(PauseLayer)     \
X(GameOverLayer)     \
X(GameScene)     \
X(ManGun)\
X(InvaderShip)\
X(Bullet)


#define X(a) READER_HEADER_FOR(a);
READERTYPES
#undef X

void registerCustomReaders(void);

#endif /* RegisterCustomReaders_hpp */
