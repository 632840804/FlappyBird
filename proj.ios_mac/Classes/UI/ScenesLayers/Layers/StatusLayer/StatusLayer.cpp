//
//  StatusLayer.cpp
//  EngryBird
//
//  Created by huangyibiao on 15/3/17.
//
//

#include "StatusLayer.h"
#include "ScoreNumber.h"
#include "AtlasLoader.h"
#include "SimpleAudioEngine.h"
#include "AppConstant.h"

USING_NS_CC;

const std::string kScoreNumberFont = "font";
const std::string kScoreNumberScore = "number_score";

StatusLayer::StatusLayer() :
_isNewRecord(false),
_bestScore(0),
_currentScore(0) {
  
}

StatusLayer::~StatusLayer() {
  
}

bool StatusLayer::init() {
  if (!Layer::init()) {
    return false;
  }
  
  // preload number sprite frames to memory
  ScoreNumber::getInstance()->loadNumber(kScoreNumberFont.c_str(), "font_0%02d", 48);
  ScoreNumber::getInstance()->loadNumber(kScoreNumberScore.c_str(), "number_score_%02d", 0);
  
  // At the first time, the game is ready to play
  this->showGameStatus(kGameStateReady);
  
  return true;
}

void StatusLayer::onGameStart() {
  this->showGameStatus(kGameStateStarted);
}

void StatusLayer::onGamePlaying(int score) {
  if (score <= 0) {
    return;
  }
  this->removeChild(_scoreNode);
  
  const char *scoreName = kScoreNumberFont.c_str();
  _scoreNode = (Sprite *)ScoreNumber::getInstance()->convert(scoreName, score);
  auto size = Director::getInstance()->getVisibleSize();
  auto origin = Director::getInstance()->getVisibleOrigin();
  _scoreNode->setPosition(origin.x + size.width / 2, origin.y + size.height * 5 / 6);
  this->addChild(_scoreNode);
}

void StatusLayer::onGameEnd(int currentScore, int historyBestScore) {
  this->showGameStatus(kGameStateOver, currentScore, historyBestScore);
}

void StatusLayer::showGameStatus(GameState status, int currentScore, int historyBestScore) {
  auto size = Director::getInstance()->getVisibleSize();
  auto origin = Director::getInstance()->getVisibleOrigin();
  
  switch (status) {
    case kGameStateReady: {
      const char *scoreName = kScoreNumberFont.c_str();
      _scoreNode = ScoreNumber::getInstance()->convert(scoreName, currentScore);
      _scoreNode->setPosition(origin.x + size.width / 2, origin.y + size.height * 5 / 6);
      this->addChild(_scoreNode);
      
      _getReadySprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrame("text_ready"));
      _getReadySprite->setPosition(origin.x + size.width / 2, origin.y + size.height * 2 / 3);
      this->addChild(_getReadySprite);
      
      _tutorialSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrame("tutorial"));
      _tutorialSprite->setPosition(origin.x + size.width / 2, origin.y + size.height * 1 / 2);
      this->addChild(_tutorialSprite);
    }
      break;
    case kGameStateStarted: {
      _getReadySprite->runAction(FadeOut::create(0.4f));
      _tutorialSprite->runAction(FadeOut::create(0.4f));
    }
      break;
    case kGameStateOver: {
      _currentScore = currentScore;
      _bestScore = historyBestScore;
      
      if (_currentScore > _bestScore) {
        _bestScore = _currentScore;
        _isNewRecord = true;
      } else {
        _isNewRecord = false;
      }
      
      this->removeChild(_scoreNode);
      
      // Game over
      auto overSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrame("text_game_over"));
      auto size = Director::getInstance()->getVisibleSize();
      auto origin = Director::getInstance()->getVisibleOrigin();
      
      overSprite->setPosition(origin.x + size.width / 2, origin.y + size.height * 2 / 3);
      this->addChild(overSprite);
      
      // Add animation
      auto fadein = FadeIn::create(0.5f);
      auto actionDone = CallFunc::create(std::bind(&StatusLayer::showScorePanel, this));
      auto sequence = Sequence::createWithTwoActions(fadein, actionDone);
      overSprite->stopAllActions();
      overSprite->runAction(sequence);
    }
      break;
    default:
      break;
  }
}

void StatusLayer::showScorePanel() {
  // score panel
  auto panel = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrame("score_panel"));
  auto size = Director::getInstance()->getVisibleSize();
  auto origin = Director::getInstance()->getVisibleOrigin();
  panel->setPosition(origin.x + size.width / 2, origin.y - panel->getContentSize().height);

  // Display the best score on the panel
  auto bestScoreSprite = static_cast<Sprite *>(ScoreNumber::getInstance()->convert(kScoreNumberScore.c_str(), _bestScore, kGravityDirectionRight));
  bestScoreSprite->setAnchorPoint(Vec2(1, 1));
  bestScoreSprite->setPosition(panel->getContentSize().width - 28, 50);
  panel->addChild(bestScoreSprite);
  
  this->setBlinkSprite();
  // Display the golden silver or bronze iron
  std::string medalsName = "";
  if (_currentScore < 20){ // iron medals
    medalsName = "medals_0";
  } else if (_currentScore >= 20 && _currentScore < 30) { // bronze medals
    medalsName = "medals_1";
  } else if (_currentScore >= 30 && _currentScore < 50){//silver medals
    medalsName = "medals_2";
  } else if (_currentScore >= 50){//golden medals
    medalsName = "medals_3";
  }
  
  if (medalsName != "") {
    auto medalSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrame(medalsName));
    medalSprite->addChild(_blinkSprite);
    medalSprite->setPosition(54, 58);
    panel->addChild(medalSprite);
  }
  
  // Tf the current score is higher than the best score.
  // the panel will appear a "new" tag.
  if (_isNewRecord) {
    auto newTagSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrame("new"));
    newTagSprite->setPosition(-16, 12);
    bestScoreSprite->addChild(newTagSprite);
  }
  
  // Start next game action
  auto moveTo = MoveTo::create(0.25f, Vec2(origin.x + size.width / 2, origin.y + size.height / 2 - 10.f));
  auto easeOut = EaseExponentialInOut::create(moveTo);
  auto actionDone = CallFunc::create(std::bind(&StatusLayer::showRestart, this));
  auto sequence = Sequence::createWithTwoActions(easeOut, actionDone);
  
  CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sfx_swooshing.ogg");
  panel->stopAllActions();
  panel->runAction(sequence);
  this->addChild(panel);
}

void StatusLayer::setBlinkSprite() {
  _blinkSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrame("blink_00"));
  auto animation = Animation::create();
  animation->setDelayPerUnit(0.1f);
  
  for (int i = 0; i < 3; ++i) {
    char filename[20];
    sprintf(filename, "blink_%02d", i);
    
    auto frame = AtlasLoader::getInstance()->getSpriteFrame(filename);
    animation->addSpriteFrame(frame);
  }
  
  for (int i = 2; i >= 0; --i) {
    char filename[20];
    sprintf(filename, "blink_%02d", i);
    
    auto frame = AtlasLoader::getInstance()->getSpriteFrame(filename);
    animation->addSpriteFrame(frame);
  }
  
  auto animate = Animate::create(animation);
  auto actionDone = CallFunc::create(std::bind(&StatusLayer::onBlinkSpriteFinishedCallback, this));
  auto sequence = Sequence::createWithTwoActions(animate, actionDone);
  _blinkSprite->stopAllActions();
  _blinkSprite->runAction(sequence);
}

void StatusLayer::onBlinkSpriteFinishedCallback() {
  if (_blinkSprite && _blinkSprite->getParent()) {
    auto size = _blinkSprite->getParent()->getContentSize();
    _blinkSprite->setPosition(rand() % int(size.width),
                              rand() % int(size.height));
  }
}

void StatusLayer::showRestart() {
  auto tmpNode = Node::create();
  auto size = Director::getInstance()->getVisibleSize();
  auto origin = Director::getInstance()->getVisibleOrigin();
  this->addChild(tmpNode);
  
  // Play button
  auto restartSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrame("button_play"));
  auto activeRestartSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrame("button_play"));
  activeRestartSprite->setPositionY(-4);
  
  auto menuItem = MenuItemSprite::create(restartSprite, activeRestartSprite, CC_CALLBACK_1(StatusLayer::menuRestartCallback, this));
  auto menu = Menu::create(menuItem, NULL);
  menu->setPosition(origin.x + (size.width - restartSprite->getContentSize().width) / 2,
                    origin.y + size.height * 2 / 7 - 10.f);
  tmpNode->addChild(menu);
  
  // Rate button
  auto rateSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrame("button_score"));
  rateSprite->setPosition(origin.x + size.width / 2 + rateSprite->getContentSize().width / 2,
                          origin.y + size.height * 2 / 7 - 10.0f);
  tmpNode->addChild(rateSprite);
  
  // Fade int the two buttons
  auto fadein = FadeIn::create(0.1f);
  auto actionDone = CallFunc::create(std::bind(&StatusLayer::refreshScoreCallback, this));
  auto sequence = Sequence::createWithTwoActions(fadein, actionDone);
  tmpNode->stopAllActions();
  tmpNode->runAction(sequence);
}

void StatusLayer::refreshScoreCallback() {
  _tmpScore = 0;
  schedule(schedule_selector(StatusLayer::refreshScoreUpdate), 0.1f);
}

void StatusLayer::refreshScoreUpdate(float delta) {
  const int kCurrentSpriteTag = 100;
  if (this->getChildByTag(kCurrentSpriteTag)) {
    this->removeChildByTag(kCurrentSpriteTag);
  }
  
  const char *score = kScoreNumberScore.c_str();
  _scoreNode = ScoreNumber::getInstance()->convert(score, _tmpScore, kGravityDirectionRight);
  _scoreNode->setAnchorPoint(Vec2(1, 0));
  
  auto size = Director::getInstance()->getVisibleSize();
  auto origin = Director::getInstance()->getVisibleOrigin();
  _scoreNode->setPosition(origin.x + size.width * 3 / 4 + 4, origin.y + (size.height - _scoreNode->getContentSize().height) / 2 + 7);
  this->addChild(_scoreNode);
  ++_tmpScore;
  
  if (_tmpScore > _currentScore) {
    unschedule(schedule_selector(StatusLayer::refreshScoreUpdate));
  }
}

void StatusLayer::menuRestartCallback(cocos2d::Ref *pSender) {
  CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sfx_swooshing.ogg");
  
  // We can't add TransitionScene object, otherwise it can't receive any touch event.
  // I don't know why.
  // We should remove all children and clean up resources, otherwise it will crash at
  // some time in the future. In fact, I don't know why, when Director replace a new
  // scene, does it remove and clean up?
  auto scene = Director::getInstance()->getRunningScene();
  scene->removeAllChildrenWithCleanup(true);
  Director::getInstance()->replaceScene(GameScene::createScene());
}
