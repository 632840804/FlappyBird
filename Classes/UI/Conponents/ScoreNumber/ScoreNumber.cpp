//
//  ScoreNumber.cpp
//  EngryBird
//
//  Created by huangyibiao on 15/3/17.
//
//

#include "ScoreNumber.h"
#include "NumberSeries.h"

USING_NS_CC;

ScoreNumber* ScoreNumber::s_sharedScoreNumber = nullptr;

ScoreNumber* ScoreNumber::getInstance() {
  if (s_sharedScoreNumber == nullptr) {
    s_sharedScoreNumber = new ScoreNumber();
    
    if (!s_sharedScoreNumber->init()) {
      CC_SAFE_DELETE(s_sharedScoreNumber);
      
      CCLOG("Error: could not init s_sharedScoreNumber object");
    }
  }
  
  return s_sharedScoreNumber;
}

void ScoreNumber::destroy() {
  if (s_sharedScoreNumber) {
    CC_SAFE_DELETE(s_sharedScoreNumber);
  }
}

bool ScoreNumber::init() {
  return true;
}

bool ScoreNumber::loadNumber(const char *name, const char *format, int base) {
  auto series = NumberSeries::create();
  series->loadNumber(format, base);
  
  _numberContainer.insert(name, series);
  
  return true;
}

Node* ScoreNumber::convert(const char *name, int number, GravityDirection direction) {
  auto series = _numberContainer.at(name);
  auto zero = Sprite::createWithSpriteFrame(series->at(0));
  
  if (number == 0) {
    zero->setAnchorPoint(Vec2(0.5, 0));
    
    return zero;
  }
  
  // seperate the number and load number sprite into the node
  auto node = Node::create();
  float totalWidth = 0.0f;
  while (number) {
    int tmp = number % 10;
    auto sprite = Sprite::createWithSpriteFrame(series->at(tmp));
    
    totalWidth += sprite->getContentSize().width;
    node->addChild(sprite);
  }
  
  // set the content size of node
  node->setContentSize(Size(totalWidth, zero->getContentSize().height));
  
  // caculate the width of each number
  float perWidth = totalWidth / node->getChildrenCount();
  ssize_t index = 0;
  float anchorX = 0;
  bool isMinus = true;
  
  if (direction == kGravityDirectionCenter) {
    anchorX = 0.5f;
    index = node->getChildrenCount() / 2;
  } else if (direction == kGravityDirectionRight) {
    anchorX = 1.0f;
    index = node->getChildrenCount();
  } else if (direction == kGravityDirectionLeft) {
    anchorX = 0.0f;
    isMinus = false;
    index = 0;
  }
  
  for (auto child : node->getChildren()) {
    child->setAnchorPoint(Vec2(anchorX, 0));
    
    float posX = perWidth * (isMinus ? index-- : index++);
    child->setPositionX(posX);
  }
  
  return node;
}