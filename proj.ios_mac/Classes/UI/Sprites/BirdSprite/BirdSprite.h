//
//  BirdSprite.h
//
//  Created by huangyibiao on 15/3/16.
//
//

#ifndef __EngryBird__BirdSprite__
#define __EngryBird__BirdSprite__

#include "cocos2d.h"

/**
 * The leading role, bird's three action state
 */
typedef enum {
  kActionStateIdle = 1, /* the idle state, wave wing but  gravity */
  kActionStateFly, /* the fly state, wave wing and be affected by gravity */
  kActionStateDie  /* the die state, the bird die in the ground */
} ActionState;

/**
 * The bird is the leading role in the EngryBird game,and the bird will have
 * three state,that is idle,fly and die.
 *
 * @note since the leading role is the only, and the BirdSprite will be designed to 
 * a singleton
 */
class BirdSprite : public cocos2d::Sprite {
public:
  /**
   * The default constructor
   */
  BirdSprite();
  
  /**
   * The default destructor
   */
  ~BirdSprite();
  
  /**
   * The singleton class method, call to get the instance of BirdSprite
   *
   * @return the instance of BirdSprite
   */
  static BirdSprite* getInstance();
  
  /**
   * Override the superclass's init method, to init BirdSprite object
   *
   * @return true if succeeded, otherwise false
   */
  bool virtual init();
  
  /**
   * Create bird sprite and init the bird sprite
   */
  bool createBird();
  
  /**
   * An important method, to update the bird action state
   *
   * @param state the bird new state
   */
  void setActionState(ActionState state);

  /**
   * An important method, to update the bird action state
   */
  CC_SYNTHESIZE_READONLY(ActionState, _actionState, ActionState);
  
private:
  /**
   * Create a frame animation
   *
   * @param foramt a format string, eg: "bird_%d"
   * @param count  the number of SpriteFrame in the created frame animation
   * @param fps    the duration of animation
   */
  static cocos2d::Animation* createAnimation(const char *format, int count, float fps);

private:
  /**
   * The singleton BirdSrpite object
   */
  static BirdSprite* s_sharedBirdSprite;
  
  /**
   * Two action to the state of ActionState
   */
  cocos2d::Action *_idleAction;
  cocos2d::Action *_wingAction;
};

#endif /* defined(__EngryBird__BirdSprite__) */
