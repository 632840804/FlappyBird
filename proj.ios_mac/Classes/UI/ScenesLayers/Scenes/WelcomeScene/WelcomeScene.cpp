//
//  WelcomeScene.cpp
//  EngryBird
//
//  Created by huangyibiao on 15/3/16.
//
//

#include "WelcomeScene.h"
#include "BirdSprite.h"
#include "AtlasLoader.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"

USING_NS_CC;

WelcomeScene::WelcomeScene() {
  
}

WelcomeScene::~WelcomeScene() {
  
}

bool WelcomeScene::init() {
  if (!Layer::init()) {
    return false;
  }
  
  // Get the visible size of the screen and the origin point of the x-y axis
  auto size = Director::getInstance()->getVisibleSize();
  auto origin = Director::getInstance()->getVisibleOrigin();
  
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
  
  // Add the game title
  auto titleSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrame("title"));
  titleSprite->setPosition(Vec2(origin.x + size.width / 2, size.height * 5.0f / 7.0f));
  this->addChild(titleSprite);
  
  // Add the menu item "start"
  auto startSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrame("button_play"));
  auto startActiveSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrame("button_play"));
  startActiveSprite->setPositionY(5);
  
  auto startItem = MenuItemSprite::create(startSprite,
                                          startActiveSprite,
                                          CC_CALLBACK_1(WelcomeScene::menuStartCallback, this));
  startItem->setPosition(origin.x + size.width / 2, origin.y + size.height * 2.0f / 5.0f);
  
  auto menu = Menu::create(startItem, NULL);
  menu->setPosition(origin.x, origin.y);
  this->addChild(menu);
  
  // Create the bird and add to the layer
  auto bird = BirdSprite::getInstance();
  bird->createBird();
  bird->setPosition(Vec2(origin.x + size.width / 2.0f,
                         origin.y + size.height * 3.0f / 5.0f - 10.0f));
  bird->setActionState(kActionStateIdle);
  this->addChild(bird);
  
  // Add the land1 and land2
  _land1 = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrame("land"));
  _land1->setAnchorPoint(Vec2::ZERO);
  _land1->setPosition(Vec2::ZERO);
  this->addChild(_land1);
  
  _land2 = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrame("land"));
  _land2->setAnchorPoint(Vec2::ZERO);
  _land2->setPosition(Vec2(_land1->getContentSize().width - 2.0f, 0));
  this->addChild(_land2);

  // Add a timer to update the land
  this->schedule(schedule_selector(WelcomeScene::scrollLand), 0.01f);
  
  // Add copyright info
  auto copyrightSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrame("brand_copyright"));
  copyrightSprite->setPosition(Vec2(origin.x + size.width / 2.0f,
                                    origin.y + size.height / 6.0f));
  this->addChild(copyrightSprite);
  
  return true;
}

Scene* WelcomeScene::createScene() {
  auto scene = Scene::create();
  auto layer = WelcomeScene::create();
  
  scene->addChild(layer);
  
  return scene;
}

void WelcomeScene::scrollLand(float delta) {
  // Each delta, move 2.0f distance
  const float distance = 2.0f;
  _land1->setPositionX(_land1->getPositionX() - distance);
  _land2->setPositionX(_land1->getPositionX() + _land1->getContentSize().width - 2.0f);
  
  if (_land2->getPositionX() <= 0) {
    _land1->setPositionX(0);
  }
}

void WelcomeScene::menuStartCallback(cocos2d::Ref *pSender) {
  CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sfx_swooshing.ogg");
  this->removeChild(BirdSprite::getInstance());
  
  auto scene = GameScene::createScene();
  auto transitionScene = TransitionFade::create(1.0f, scene);
  Director::getInstance()->replaceScene(transitionScene);
}