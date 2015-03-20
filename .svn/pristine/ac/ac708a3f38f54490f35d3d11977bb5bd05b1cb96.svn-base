//
//  LoadingScene.h
//  EngryBird
//
//  Created by huangyibiao on 15/3/17.
//
//

#ifndef __EngryBird__LoadingScene__
#define __EngryBird__LoadingScene__

#include "cocos2d.h"

/**
 * The loading scene is just for the beginning of game, to loading
 * the scene
 */
class LoadingScene : public cocos2d::Layer {
public:
  /**
   * The default constructor
   */
  LoadingScene();
  
  /**
   * The default destructor
   */
  ~LoadingScene();
  
  /**
   * The init method, will init the super init method first
   *
   * @return true if succeeded, otherwise false
   */
  virtual bool init();
  
  /**
   * The designed scene create method, create a scene, and add loading layer
   * into it.
   *
   * @return a cocos2d scene object
   */
  static cocos2d::Scene* createScene();
  
  CREATE_FUNC(LoadingScene);
  
  /**
   * Override the method.
   * Event callback that is invoked every time when Node enters the 'stage'.
   * If the Node enters the 'stage' with a transition, this event is called 
   * when the transition starts.
   * 
   * @note During onEnter you can't access a "sister/brother" node.
   * If you override onEnter, you shall call its parent's one, e.g., Node::onEnter().
   */
  virtual void onEnter();
  
private:
  /**
   * Called when the texture (eg. atlas.png) has loaded finished.
   *
   * @param texture The texture that has loaded.
   */
  void onLoadFinishedCallback(cocos2d::Texture2D *texture);
};

#endif /* defined(__EngryBird__LoadingScene__) */
