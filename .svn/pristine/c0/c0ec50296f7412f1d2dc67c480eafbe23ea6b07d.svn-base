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
  
private:
  /**
   * Show the current game state, according to the status parameter.
   * Only when status == kGameStateOver, currentScore and historyBestScore will be used.
   *
   * @param status The game current state
   * @param currentScore The player current game score value
   * @param historyBestScore The player had best score value in the history.
   */
  void showGameStatus(GameState status, int currentScore = 0, int historyBestScore = 0);
  
  /**
   * When game is over, it will jump to show the score panel of the user
   */
  void showScorePanel();
  
  /**
   * Create blink sprite
   */
  void setBlinkSprite();
  void onBlinkSpriteFinishedCallback();
  
  /**
   * Show restart button when game over
   */
  void showRestart();
  void menuRestartCallback(cocos2d::Ref *pSender);
  void refreshScoreCallback();
  void refreshScoreUpdate(float delta);
  
private:
  cocos2d::Sprite *_getReadySprite;
  cocos2d::Sprite *_tutorialSprite;
  cocos2d::Node *_scoreNode;
  cocos2d::Sprite *_blinkSprite;
  
  /**
   * Record the player's score and history best score of the current game
   */
  int _currentScore;
  int _bestScore;
  
  /**
   * Only temperaly use for refresh score
   */
  int _tmpScore;
  
  /**
   * Mark whether is a new record
   */
  bool _isNewRecord;
};

#endif /* defined(__EngryBird__StatusLayer__) */
