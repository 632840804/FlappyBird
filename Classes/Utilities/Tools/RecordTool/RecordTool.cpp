//
//  RecordTool.cpp
//  EngryBird
//
//  Created by huangyibiao on 15/3/17.
//
//

#include "RecordTool.h"
#include "cocos2d.h"

USING_NS_CC;

int RecordTool::getBestScore() {
  return UserDefault::getInstance()->getIntegerForKey("kBestScoreKey");
}

void RecordTool::setBestScore(int bestScore) {
  UserDefault::getInstance()->setIntegerForKey("kBestScoreKey", bestScore);
}