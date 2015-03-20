//
//  BirdSprite.cpp
//  EngryBird
//
//  Created by huangyibiao on 15/3/16.
//
//

#include "BirdSprite.h"
#include "AtlasLoader.h"

USING_NS_CC;

BirdSprite::BirdSprite() {
  
}

BirdSprite::~BirdSprite() {
  
}

BirdSprite* BirdSprite::s_sharedBirdSprite = nullptr;
BirdSprite* BirdSprite::getInstance() {
  if (s_sharedBirdSprite == NULL) {
    s_sharedBirdSprite = new BirdSprite();
    
    if (!s_sharedBirdSprite->init()) {
      CC_SAFE_DELETE(s_sharedBirdSprite);
      CCLOG("Error: could not init the s_sharedBirdSprite object");
    }
  }
  
  return s_sharedBirdSprite;
}

bool BirdSprite::init() {
  return true;
}

bool BirdSprite::createBird() {
  // Randomly generate a bird color
  srand((unsigned)time(NULL));
  int type = rand() % 3;
  char birdName[10];
  char birdNameFormat[10];
  sprintf(birdName, "bird%d_%d", type, type);
  sprintf(birdNameFormat, "bird%d_%%d", type);
  
  auto spriteFrame = AtlasLoader::getInstance()->getSpriteFrame(birdName);
  if (Sprite::initWithSpriteFrame(spriteFrame)) {
    // init idle status
    // create the bird idle animation
    auto animation = createAnimation(birdNameFormat, 3, 10);
    _idleAction = RepeatForever::create(Animate::create(animation));
    
    // create the bird waving wing animation
    auto upAction = MoveBy::create(0.4f, Vec2(0, 8));
    auto downAction = upAction->reverse();
    _wingAction = RepeatForever::create(Sequence::create(upAction, downAction, NULL));
    
    return true;
  }
  
  return false;
}

Animation* BirdSprite::createAnimation(const char *format, int count, float fps) {
  auto animation = Animation::create();
  animation->setDelayPerUnit(1.0f / fps);
  
  for (int i = 0; i < count; ++i) {
    char name[10];
    sprintf(name, format, i);
    
    auto spriteFrame = AtlasLoader::getInstance()->getSpriteFrame(name);
    animation->addSpriteFrame(spriteFrame);
  }
  
  return animation;
}

void BirdSprite::setActionState(ActionState state) {
  _actionState = state;
  
  switch (state) {
    case kActionStateIdle:
      // The idle state, the bird waves the wing and doesn't affect by gravity
      this->runAction(_idleAction);
      this->runAction(_wingAction);
      break;
    case kActionStateFly:
      // The fly state, the bird waves the wing, affected by gravity
      this->stopAction(_wingAction);
      this->getPhysicsBody()->setGravityEnable(true);
      break;
    case kActionStateDie:
      // Thd die state, the bird get down to the ground.
      this->stopAllActions();
      break;
    default:
      break;
  }
}