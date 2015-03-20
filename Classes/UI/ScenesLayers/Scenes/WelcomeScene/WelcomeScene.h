//
//  WelcomeScene.h
//  EngryBird
//
//  Created by huangyibiao on 15/3/16.
//
//

#ifndef __EngryBird__WelcomeScene__
#define __EngryBird__WelcomeScene__

#include "cocos2d.h"

/**
 *  The Welcome layer class, showing the welcome information
 */
class WelcomeScene : public cocos2d::Layer {
public:
  /**
   * The default constructor
   */
  WelcomeScene();
  
  /**
   * The default destructor
   */
  ~WelcomeScene();
  
  /**
   * The init method, will init the super init method first
   *
   * @return true if succeeded, otherwise false
   */
  virtual bool init();
  
  /**
   * The designed scene create method
   *
   * @return a cocos2d scene object which has add the welcome layer to it
   */
  static cocos2d::Scene* createScene();
  
  CREATE_FUNC(WelcomeScene);
  
private:
  /**
   * The start menu button call back method, when called,
   * it will enter into the game scene
   */
  void menuStartCallback(Ref *pSender);
  
  /**
   * Make the land scroll with an animation
   *
   * @param delta The interval time to animate
   */
  void scrollLand(float delta);
  
private:
  /**
   * The first land
   */
  cocos2d::Sprite *_land1;
  
  /**
   * The second land
   */
  cocos2d::Sprite *_land2;
};

#endif /* defined(__EngryBird__WelcomeScene__) */
