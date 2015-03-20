//
//  GameScene.cpp
//  EngryBird
//
//  Created by huangyibiao on 15/3/17.
//
//

#include "GameScene.h"
#include "BirdSprite.h"
#include "AppConstant.h"
#include "BackgroundLayer.h"
#include "AtlasLoader.h"
#include "SimpleAudioEngine.h"
#include "RecordTool.h"
#include "BackgroundLayer.h"
#include "StatusLayer.h"
#include "OptionLayer.h"

USING_NS_CC;

GameScene::GameScene() :
_currentScore(0),
_gameCurrentState(kGameStateReady) {
  
}

GameScene::~GameScene() {
  
}

bool GameScene::init() {
  if (!Layer::init()) {
    return false;
  }
  
  auto size = Director::getInstance()->getVisibleSize();
  auto origin = Director::getInstance()->getVisibleOrigin();
  
  // Add the bird
  auto bird = BirdSprite::getInstance();
  bird->createBird();
  auto body = PhysicsBody::create();
  body->addShape(PhysicsShapeCircle::create(kBirdRadius));
  body->setDynamic(true);
  body->setLinearDamping(0.0f);
  body->setGravityEnable(false);
  body->setCategoryBitmask(0x01);
  body->setCollisionBitmask(0x01);
  body->setContactTestBitmask(0x01);
  bird->setPhysicsBody(body);
  bird->setPosition(origin.x + size.width / 3 - 5, origin.y + size.height / 2 + 5);
  bird->setActionState(kActionStateIdle);
  this->addChild(bird);
  
  // Add the ground
  _groundNode = Node::create();
  auto groundBody = PhysicsBody::create();
  auto groundSize = Size(kDesignWidth, BackgroundLayer::getLandHeight());
  groundBody->addShape(PhysicsShapeBox::create(groundSize));
  groundBody->setDynamic(false);
  groundBody->setLinearDamping(0.0f);
  groundBody->setCategoryBitmask(0x01);
  groundBody->setContactTestBitmask(0x01);
  groundBody->setCollisionBitmask(0x01);
  _groundNode->setPhysicsBody(groundBody);
  _groundNode->setPosition(groundSize.width / 2, groundSize.height);
  this->addChild(_groundNode);
  
  // land
  // Add the land1 and land2
  _land1 = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrame("land"));
  _land1->setAnchorPoint(Vec2::ZERO);
  _land1->setPosition(Vec2::ZERO);
  this->addChild(_land1, 30);
  
  _land2 = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrame("land"));
  _land2->setAnchorPoint(Vec2::ZERO);
  _land2->setPosition(Vec2(_land1->getContentSize().width - 2.0f, 0));
  this->addChild(_land2, 30);
  
  // Add a timer to update the land
  _shiftLand = schedule_selector(GameScene::scrollLand);
  this->schedule(_shiftLand, 0.01f);
  
  // will call update(float delta) method
  this->scheduleUpdate();
  
  // Add contact listener
  //
  // If body->getCategoryBitmask() & groundBody->getContactTestBitmask() == 1
  // Then we can listen the physics touch event, otherwise not.
  //
  // If body->getCategoryBitmask() & groundBody->getCollisionBitmask() == 1
  // Then the bird and the ground can collide, otherwise not.
  auto listener = EventListenerPhysicsContact::create();
  listener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
  this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
  
  return true;
}

Scene* GameScene::createScene() {
  // create a scene with physics world
  auto scene = Scene::createWithPhysics();
  if (scene->getPhysicsWorld()) {
    scene->getPhysicsWorld()->setGravity(Vect(0, -900));
  } else {
    CCLOG("Error: Game scene get physics world, but it is nullptr");
  }
  
  // background layer
  auto backgroundLayer = BackgroundLayer::create();
  if (backgroundLayer) {
    scene->addChild(backgroundLayer);
  }
  
  // game layer
  auto gameLayer = GameScene::create();
  // status layer
  auto statusLayer = StatusLayer::create();
  
  if (gameLayer) {
    gameLayer->setPhysicsWorld(scene->getPhysicsWorld());
    gameLayer->setStatusDelegate(statusLayer);
    gameLayer->setTag(kGameLayerTag);
    scene->addChild(gameLayer);
  }
  if (statusLayer) {
    scene->addChild(statusLayer);
  }
  
  // option layer
  auto optionLayer = OptionLayer::create();
  if (optionLayer) {
    optionLayer->setOptionDelegate(gameLayer);
    scene->addChild(optionLayer);
  }
  
  return scene;
}

bool GameScene::onContactBegin(cocos2d::PhysicsContact &contact) {
  gameOver();
  
  return true;
}

void GameScene::scrollLand(float delta) {
  // Each delta, move 2.0f distance
  const float distance = 2.0f;
  _land1->setPositionX(_land1->getPositionX() - distance);
  _land2->setPositionX(_land1->getPositionX() + _land1->getContentSize().width - 2.0f);
  
  if (_land2->getPositionX() <= 0) {
    _land1->setPositionX(0);
  }
  
  // Move the pipes
  for (auto pipe : _pipes) {
    pipe->setPositionX(pipe->getPositionX() - distance);
    
    // When be reused, mark to be a new pipe
    if (pipe->getPositionX() < -kPipeWidth) {
      pipe->setTag(kPipeNewTag);
      
      auto size = Director::getInstance()->getVisibleSize();
      pipe->setPositionX(size.width);
      pipe->setPositionY(this->getRandomPipeHeight());
    }
  }
}

void GameScene::onTouch() {
  if (_gameCurrentState == kGameStateOver) {
    return;
  }
  
  CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sfx_wing.ogg");
  
  if (_gameCurrentState == kGameStateStarted) {
    BirdSprite::getInstance()->getPhysicsBody()->setVelocity(Vect(0, 260));
  } else if (_gameCurrentState == kGameStateReady) {
    if (this->getStatusDelegate()) {
      this->getStatusDelegate()->onGameStart();
    }
    
    BirdSprite::getInstance()->setActionState(kActionStateFly);
    _gameCurrentState = kGameStateStarted;
    
    // when game starts, create pipes
    createPipes();
  }
}

void GameScene::rotateBird() {
  float verticalSpeed = BirdSprite::getInstance()->getPhysicsBody()->getVelocity().y;
  BirdSprite::getInstance()->setRotation(MIN(MAX(-90, verticalSpeed * 0.2 + 60), 30));
}

void GameScene::update(float delta) {
  if (_gameCurrentState == kGameStateStarted) {
    this->rotateBird();
    
    this->checkHit();
  }
}

void GameScene::createPipes() {
  // create pipes
  auto size = Director::getInstance()->getVisibleSize();
  for (int i = 0; i < kPipePairCount; ++i) {
    auto pipeUp = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrame("pipe_up"));
    //pipeUp->setPosition(0, <#float y#>)
    auto pipeDown = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrame("pipe_down"));
    pipeDown->setPosition(0, kPipeHeight + kPipeUpDownDistance);
    
    auto pipeNode = Node::create();
    pipeNode->setPosition(size.width + i * kPipeInterval + kWaitDistance,
                          getRandomPipeHeight());
    pipeNode->addChild(pipeDown, 0, kPipeDownTag);
    pipeNode->addChild(pipeUp, 0, kPipeUpTag);
    
    // Add physics to pipe
    auto body = PhysicsBody::create();
    auto box = PhysicsShapeBox::create(pipeDown->getContentSize(),
                                       PHYSICSSHAPE_MATERIAL_DEFAULT,
                                       Vec2(0, kPipeHeight + kPipeUpDownDistance));
    body->addShape(box);
    body->addShape(PhysicsShapeBox::create(pipeUp->getContentSize()));
    body->setDynamic(false);
    body->setCategoryBitmask(0x01);
    body->setContactTestBitmask(0x01);
    body->setCollisionBitmask(0x01);
    
    pipeNode->setPhysicsBody(body);
    pipeNode->setTag(kPipeNewTag);
    this->addChild(pipeNode);
    
    _pipes.pushBack(pipeNode);
  }
}

void GameScene::setPhysicsWorld(cocos2d::PhysicsWorld *world) {
  _world = world;
}

int GameScene::getRandomPipeHeight() {
  auto size = Director::getInstance()->getVisibleSize();
  
  return rand() % (int)(2 * kPipeHeight + kPipeUpDownDistance - size.height);
}

void GameScene::checkHit() {
  for (auto pipe : _pipes) {
    if (pipe->getTag() == kPipeNewTag) {
      // 通过一根
      if (pipe->getPositionX() < BirdSprite::getInstance()->getPositionX()) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sfx_point.ogg");
        
        ++_currentScore;
        
        if (this->getStatusDelegate()) {
          this->getStatusDelegate()->onGamePlaying(_currentScore);
        }
        
        pipe->setTag(kPipePassedTag);
      }
    }
  }
}

void GameScene::gameOver() {
  if (_gameCurrentState == kGameStateOver) {
    return;
  }
  
  CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sfx_hit.ogg");
  
  // Get the best score in the history
  int bestScore = RecordTool::getBestScore();
  if (_currentScore > bestScore) {
    RecordTool::setBestScore(_currentScore);
  }
  
  if (this->getStatusDelegate()) {
    this->getStatusDelegate()->onGameEnd(_currentScore, bestScore);
  }
  
  this->unschedule(_shiftLand);
  
  CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sfx_die.ogg");
  BirdSprite::getInstance()->setActionState(kActionStateDie);
  BirdSprite::getInstance()->setRotation(-90);
  this->birdFadeOut();
  
  _gameCurrentState = kGameStateOver;
}

void GameScene::birdFadeOut() {
  auto fadeout = FadeOut::create(1.5f);
  auto doneCallback = CallFunc::create(std::bind(&GameScene::birdRemove, this));
  auto sequence = Sequence::createWithTwoActions(fadeout, doneCallback);
  BirdSprite::getInstance()->stopAllActions();
  BirdSprite::getInstance()->runAction(sequence);
}

void GameScene::birdRemove() {
  BirdSprite::getInstance()->setRotation(0);
  this->removeChild(BirdSprite::getInstance());
}