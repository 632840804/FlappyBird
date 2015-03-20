//
//  NumberSeries.cpp
//  EngryBird
//
//  Created by huangyibiao on 15/3/17.
//
//

#include "NumberSeries.h"
#include "AtlasLoader.h"

// The max count of numbers
const int kMaxNumberCount = 10;

USING_NS_CC;

NumberSeries::NumberSeries() {
  
}

NumberSeries::~NumberSeries() {
  
}

bool NumberSeries::init() {
  _numberVector = cocos2d::Vector<SpriteFrame *>(kMaxNumberCount);
  
  return true;
}

void NumberSeries::loadNumber(const char *foramt, int base) {
  for (int i = base; i < kMaxNumberCount + base; ++i) {
    char name[20];
    sprintf(name, foramt, i);
    
    auto frame = AtlasLoader::getInstance()->getSpriteFrame(name);
    _numberVector.pushBack(frame);
  }
}

SpriteFrame* NumberSeries::at(int index) {
  if (index >= 0 && index < _numberVector.size()) {
    return _numberVector.at(index);
  }
  
  return NULL;
}

