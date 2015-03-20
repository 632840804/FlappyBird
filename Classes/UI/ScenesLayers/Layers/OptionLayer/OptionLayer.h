//
//  OptionLayer.h
//  EngryBird
//
//  Created by huangyibiao on 15/3/17.
//
//

#ifndef __EngryBird__OptionLayer__
#define __EngryBird__OptionLayer__

#include "cocos2d.h"

class OptionDelegate;

/**
 * The game background,showing the background information
 * in the game.
 */
class OptionLayer : public cocos2d::Layer {
public:
  /**
   * The default constructor
   */
  OptionLayer();
  
  /**
   * The default destructor
   */
  ~OptionLayer();
  
  /**
   * The init method, will init the super init method first
   *
   * @return true if succeeded, otherwise false
   */
  virtual bool init();
  
  CREATE_FUNC(OptionLayer);
  
  /**
   * Override the multitouch method
   */
  virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches,
                              cocos2d::Event *unused_event);
  
  /**
   * The delegate 
   */
  CC_SYNTHESIZE(OptionDelegate*, _optionDelegate, OptionDelegate);
};

/**
 * The delegate between option layer and game layer
 */
class OptionDelegate {
public:
  /**
   * When touch the option layer, it will be called
   */
  virtual void onTouch() = 0;
};

#endif /* defined(__EngryBird__OptionLayer__) */
