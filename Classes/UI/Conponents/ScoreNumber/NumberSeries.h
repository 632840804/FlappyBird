//
//  NumberSeries.h
//  EngryBird
//
//  Created by huangyibiao on 15/3/17.
//
//

#ifndef __EngryBird__NumberSeries__
#define __EngryBird__NumberSeries__

#include "cocos2d.h"

/**
 * This class is for ScoreNumber, and it will store a list of sprite frames.
 * With it, you can load number sprite with name format and get sprite frame
 * with index.
 */
class NumberSeries : public cocos2d::Ref {
public:
  /**
   * The default constructor
   */
  NumberSeries();
  
  /**
   * The default destructor
   */
  ~NumberSeries();
  
  /**
   * The init method, will init the super init method first
   *
   * @return true if succeeded, otherwise false
   */
  virtual bool init();
  
  CREATE_FUNC(NumberSeries);
  
  /**
   * Load sprite frame with a format name
   *
   * @param format The name format, eg. "number1_%d"
   * @param base The begin index
   */
  void loadNumber(const char *foramt, int base = 0);
  
  /**
   * Get sprite frame with an index
   *
   * @param index The index in the _numberVector
   *
   * @return a sprite frame object
   */
  cocos2d::SpriteFrame* at(int index);
  
private:
  /**
   * Store number sprite frames
   */
  cocos2d::Vector<cocos2d::SpriteFrame *> _numberVector;
};

#endif /* defined(__EngryBird__NumberSeries__) */
