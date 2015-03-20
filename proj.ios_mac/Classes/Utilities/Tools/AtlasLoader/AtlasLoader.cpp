//
//  AtlasLoader.cpp
//  EngryBird
//
//  Created by huangyibiao on 15/3/16.
//
//

#include "AtlasLoader.h"

USING_NS_CC;

// Initializes the shared object to be nullptr
AtlasLoader* AtlasLoader::s_sharedAtlasLoader = NULL;

AtlasLoader* AtlasLoader::getInstance() {
  if (s_sharedAtlasLoader == NULL) {
    s_sharedAtlasLoader = new AtlasLoader();
    
    if (!s_sharedAtlasLoader->init()) {
      delete s_sharedAtlasLoader;
      
      s_sharedAtlasLoader = NULL;
      CCLOG("Error: could not init s_sharedAtlasLoader object");
    }
  }
  
  return s_sharedAtlasLoader;
}

AtlasLoader::AtlasLoader() {
  
}

void AtlasLoader::destroy() {
  if (s_sharedAtlasLoader) {
    CC_SAFE_DELETE(s_sharedAtlasLoader);
  }
}

bool AtlasLoader::init() {
  return true;
}

void AtlasLoader::loadAtlas(std::string filename) {
  auto texture = Director::getInstance()->getTextureCache()->addImage("atlas.png");
  this->loadAtlas(filename, texture);
}

void AtlasLoader::loadAtlas(std::string filename, cocos2d::Texture2D *texture) {
  std::string data = FileUtils::getInstance()->getStringFromFile(filename);
  
  size_t pos = data.find_first_of("\n");
  std::string line = data.substr(0, pos);
  data = data.substr(pos + 1);
  Atlas atlas;
  while (line.length() > 0) {
    sscanf(line.c_str(), "%s %d %d %f %f %f %f",
           atlas.name,
           &atlas.width,
           &atlas.height,
           &atlas.startPosition.x,
           &atlas.startPosition.y,
           &atlas.endPosition.x,
           &atlas.endPosition.y);
    
    atlas.startPosition.x *= 1024;
    atlas.startPosition.y *= 1024;
    atlas.endPosition.x *= 1024;
    atlas.endPosition.y *= 1024;
    
    // 读取下一行
    pos = data.find_first_of("\n");
    line = data.substr(0, pos);
    data = data.substr(pos + 1);
    
    // fix 1px edge bug
    if (atlas.name == std::string("land")) {
      ++atlas.startPosition.x;
    }
    
    
    // use the data to create a sprite frame
    Rect rect = Rect(atlas.startPosition.x, atlas.startPosition.y, atlas.width, atlas.height);
    auto spriteFrame = SpriteFrame::createWithTexture(texture, rect);
    _spriteFrames.insert(std::string(atlas.name), spriteFrame);
  }
}

SpriteFrame* AtlasLoader::getSpriteFrame(std::string imageName) {
  if (imageName.length() <= 0) {
    return NULL;
  }
  
  return _spriteFrames.at(imageName);
}