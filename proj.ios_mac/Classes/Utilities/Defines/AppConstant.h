//
//  AppConstant.h
//  EngryBird
//
//  Created by huangyibiao on 15/3/17.
//
//

#ifndef EngryBird_AppConstant_h
#define EngryBird_AppConstant_h

/**
 * The pipe has four state, using the following tag to mark.
 * > the state up
 * > the state down
 * > the state passed
 * > the state new created
 */
const int kPipeUpTag = 21;
const int kPipeDownTag = 12;
const int kPipePassedTag = 30;
const int kPipeNewTag = 31;

/**
 * > the pipe's height
 * > the pipe's width
 * > the speed of pipe moves
 * > the distance between the down pipe and up pipe
 * > the distance between the pipes vertical
 * > the number of pipe pairs display int the screen in the same time
 * > the distance that the pipe will display in the screen, for player to ready
 */
const int kPipeHeight = 320;
const int kPipeWidth = 52;
const float kPipeShiftSpeed = 80.0f;
const int kPipeUpDownDistance = 100;
const int kPipeInterval = 180;
const int kPipePairCount = 2;
const int kWaitDistance = 100;

/**
 * The radius of the bird
 */
const int kBirdRadius = 15;

/**
 * The width and height of the design resolution
 */
const int kDesignWidth = 288;
const int kDesignHeight = 512;

/**
 * The tag of game layer in the scene
 */
const int kGameLayerTag = 101;

#endif
