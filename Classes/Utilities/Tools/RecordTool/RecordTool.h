//
//  RecordTool.h
//  EngryBird
//
//  Created by huangyibiao on 15/3/17.
//
//

#ifndef __EngryBird__RecordTool__
#define __EngryBird__RecordTool__

#include <stdio.h>

/**
 * This is a help class, using to operate the user information conveniencely
 */
class RecordTool {
public:
  /**
   * Get the best score with a key, store in the UserDefault
   */
  static int getBestScore();
  
  /**
   * Update a new score in the local UserDefault
   *
   * @param bestScore The new value of score
   */
  static void setBestScore(int bestScore);
};

#endif /* defined(__EngryBird__RecordTool__) */
