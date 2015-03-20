//
//  StatusLayer.h
//  EngryBird
//
//  Created by huangyibiao on 15/3/17.
//
//

#ifndef __EngryBird__StatusLayer__
#define __EngryBird__StatusLayer__

#include "cocos2d.h"
#include "GameScene.h"

/**
 *The status layer,showing the status information
 * in the game.
 */
class StatusLayer : public cocos2d::Layer, public GameStatusDelegate {
public:
  /**
   * The default constructor
   */
  StatusLayer();
  
  /**
   * The default destructor
   */
  ~StatusLayer();
  
  /**
   * The init method, will init the super init method first
   *
   * @return true if succeeded, otherwise false
   */
  virtual bool init();
  
  /**
   * Override from GameStatusDelegate
   *
   * @see GameStatusDelegate declaration.
   */
  void onGameStart(void);
  void onGamePlaying(int score);
  void onGameEnd(int currentScore, int historyBestScore);
  
  CREATE_FUNC(StatusLayer);
};

#endif /* defined(__EngryBird__StatusLayer__) */
