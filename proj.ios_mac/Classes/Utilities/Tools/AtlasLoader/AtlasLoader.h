//
//  AtlasLoader.h
//  EngryBird
//
//  Created by huangyibiao on 15/3/16.
//
//

#ifndef __EngryBird__AtlasLoader__
#define __EngryBird__AtlasLoader__

#include "cocos2d.h"

/**
 * The struct of the atlas file
 */
typedef struct tag_atlas {
  char name[255];               // the image's name
  int width;                    // the image's width
  int height;                   // the image's height
  cocos2d::Vec2 startPosition;  // the image's start position
  cocos2d::Vec2 endPosition;    // the image's end position
} Atlas;

/**
 * The hepler class for loading the resources of atlas.png/atlas.txt
 *
 * @Note This is a global shared class, just call the getInstance class method
 * to get the object
 */
class AtlasLoader {
public:
  /**
   * Get the instance of AtlasLoader
   */
  static AtlasLoader* getInstance();
  
  /**
   * Destroy the instance of AtlasLoader,and will free all memory it takes
   */
  static void destroy();
  
  /**
   * Load with file name of an atlas and default load the atlas.png to texture
   *
   * @param filename the name of an atlas file
   *
   * @note This function load the images sync,so it will delay the main thread.
   * You can call like that: AtlasLoader::getInstance()->loadAtlas("filename");
   */
  void loadAtlas(std::string filename);
  
  /**
   * Load with file name of an atlas
   *
   * @param filename the name of an atlas file
   * @param texture the Texture2D object,using to create a sprite frame
   *
   * This function load the images sync,so it will delay the main thread.
   * You can call like that: AtlasLoader::getInstance()->loadAtlas("filename", texture);
   */
  void loadAtlas(std::string filename, cocos2d::Texture2D *texture);
  
  /**
   * Get the sprite frame with an image name
   *
   * @param imageName the name of image
   *
   * @return the sprite frame object related to an image
   */
  cocos2d::SpriteFrame* getSpriteFrame(std::string imageName);
  
protected:
  /**
   * The default constructor
   */
  AtlasLoader();
  
  /**
   * Initializes the instance of AtlasLoader
   *
   * @note When you are porting Cocos2d-x to a new platform, you may need to take care of
   * this method.
   *
   * @return true if succeeded, otherwise false
   */
  virtual bool init();
  
private:
  /**
   * The singleton pointer of AtlasLoader
   */
  static AtlasLoader* s_sharedAtlasLoader;
  
  /**
   * The container to store all the sprite frames that has already loaded
   */
  cocos2d::Map<std::string, cocos2d::SpriteFrame*> _spriteFrames;
};

#endif /* defined(__EngryBird__AtlasLoader__) */
