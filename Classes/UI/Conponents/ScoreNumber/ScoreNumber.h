//
//  ScoreNumber.h
//  EngryBird
//
//  Created by huangyibiao on 15/3/17.
//
//

#ifndef __EngryBird__ScoreNumber__
#define __EngryBird__ScoreNumber__

#include "cocos2d.h"

class NumberSeries;

/**
 * The gravity's direction
 */
typedef enum {
  kGravityDirectionCenter = 1,
  kGravityDirectionLeft,
  kGravityDirectionRight
} GravityDirection;

/**
 * This class is used to show player's score's special effect
 */
class ScoreNumber {
public:
  /**
   * Init variables
   *
   * @return true if succeeded, otherwise false.
   */
  virtual bool init();
  
  /**
   * The singleton, to Get the ScoreNumber object
   */
  static ScoreNumber* getInstance();
  
  /**
   * Destroy the resource of ScoreNumber object
   */
  static void destroy();
  
  /**
   * Load a score number
   *
   * @param name The file name
   * @param foramt The file name format like 'number_score_%2d'
   * @param base If the serious file name is not start with 0, you can set base to fix it
   *
   * @return true if succeeded, otherwise false.
   */
  virtual bool loadNumber(const char *name, const char *format, int base = 0);
  
  /**
   * Convert the integer number to Sprite present the number
   *
   * @param name The key to save the number sprite in the map
   * @param number The given number such as 4252
   * @param direction The gravity direction, default is center
   *
   * @return The node presenting the given number
   */
  cocos2d::Node* convert(const char *name,
                         int number,
                         GravityDirection direction = GravityDirection::kGravityDirectionCenter);
  
private:
  /**
   * Store numberSeries
   */
  cocos2d::Map<std::string, NumberSeries*> _numberContainer;
  
  /**
   * The global shared score number object
   */
  static ScoreNumber* s_sharedScoreNumber;
};

#endif /* defined(__EngryBird__ScoreNumber__) */
