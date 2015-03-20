//
//  LoadingScene.cpp
//  EngryBird
//
//  Created by huangyibiao on 15/3/17.
//
//

#include "LoadingScene.h"
#include "BackgroundLayer.h"
#include "WelcomeScene.h"
#include "AtlasLoader.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

LoadingScene::LoadingScene() {
  
}

LoadingScene::~LoadingScene() {
  
}

bool LoadingScene::init() {
  if (!Layer::init()) {
    return false;
  }
  
  return true;
}

Scene* LoadingScene::createScene() {
  auto scene = Scene::create();
  auto layer = LoadingScene::create();
  
  scene->addChild(layer);
  
  return scene;
}

void LoadingScene::onEnter() {
  Layer::onEnter();
  
  // Add the splash screen image
  auto background = Sprite::create("splash.png");
  auto size = Director::getInstance()->getVisibleSize();
  auto origin = Director::getInstance()->getVisibleOrigin();
  
  background->setPosition(origin.x + size.width / 2, origin.y + size.height / 2);
  this->addChild(background);
  
  // Start to load texture async
  auto texture = Director::getInstance()->getTextureCache();
  texture->addImageAsync("atlas.png",
                         CC_CALLBACK_1(LoadingScene::onLoadFinishedCallback, this));
}

void LoadingScene::onLoadFinishedCallback(cocos2d::Texture2D *texture) {
  // Load the atlas
  AtlasLoader::getInstance()->loadAtlas("atlas.txt", texture);
  
  // Preload effect music.
  // Here is not the best way to load all music files,
  // in real projects, you should find a better way to do.
  CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sfx_die.ogg");
  CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sfx_hit.ogg");
  CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sfx_point.ogg");
  CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sfx_swooshing.ogg");
  CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sfx_wing.ogg");
  
  // Now the task of the loading scene has finished,
  // auto enter into the welcome scene
  auto scene = TransitionFade::create(1.0f, WelcomeScene::createScene());
  Director::getInstance()->replaceScene(scene);
}