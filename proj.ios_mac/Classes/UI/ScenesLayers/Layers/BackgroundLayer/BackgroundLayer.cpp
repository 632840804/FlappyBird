//
//  BackgroundLayer.cpp
//  EngryBird
//
//  Created by huangyibiao on 15/3/17.
//
//

#include "BackgroundLayer.h"
#include "AtlasLoader.h"

USING_NS_CC;

BackgroundLayer::BackgroundLayer() {
  
}

BackgroundLayer::~BackgroundLayer() {
  
}

bool BackgroundLayer::init() {
  if (!Layer::init()) {
    return false;
  }
  
  // Get the current time, judge whether now is day or night
  time_t t = time(NULL);
  tm *localTime = localtime(&t);
  int hour = localTime->tm_hour;
  
  std::string bgName;
  if (hour >= 6 && hour <= 17) {
    bgName = "bg_day";
  } else {
    bgName = "bg_night";
  }
  
  auto bgSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrame(bgName));
  bgSprite->setAnchorPoint(Vec2::ZERO);
  bgSprite->setPosition(Vec2::ZERO);
  this->addChild(bgSprite);
  
  return true;
}

float BackgroundLayer::getLandHeight() {
  auto spriteFrame = AtlasLoader::getInstance()->getSpriteFrame("land");
  auto land = Sprite::createWithSpriteFrame(spriteFrame);
  
  return land->getContentSize().height;
}