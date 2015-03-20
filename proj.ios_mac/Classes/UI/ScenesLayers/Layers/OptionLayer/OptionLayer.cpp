//
//  OptionLayer.cpp
//  EngryBird
//
//  Created by huangyibiao on 15/3/17.
//
//

#include "OptionLayer.h"

USING_NS_CC;

OptionLayer::OptionLayer() {
  
}

OptionLayer::~OptionLayer() {
  
}

bool OptionLayer::init() {
  if (!Layer::init()) {
    return false;
  }
  
  // Register touches began event
  auto listener = EventListenerTouchAllAtOnce::create();
  listener->onTouchesBegan = CC_CALLBACK_2(OptionLayer::onTouchesBegan, this);
  
//  // 这个是3.0后的新特性，这里就没有使用，主要还是想先了解旧方式，但新的方式也是需要知道的
//  listener->onTouchesBegan = [&](const std::vector<Touch *> &touches, Event *event) {
//    CCLOG("touches begin");
//    if (this->getOptionDelegate()) {
//      this->getOptionDelegate()->onTouch();
//    }
//  };
  auto dispatcher = Director::getInstance()->getEventDispatcher();
  dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
  
  return true;
}

void OptionLayer::onTouchesBegan(const std::vector<Touch *> &touches, Event *unused_event) {
  CCLOG("touches begin");
  if (this->getOptionDelegate()) {
    this->getOptionDelegate()->onTouch();
  }
}