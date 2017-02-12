#ifndef SIMPLE_SCENE_H
#define SIMPLE_SCENE_H

#include "Ogre.h"
#include <tinyxml.h>

class SimpleScene {

public:
     SimpleScene(Ogre::SceneManager*);
     ~SimpleScene();
     void load();
     void update(float);

private:
     Ogre::SceneManager* mSceneManager;
     Ogre::SceneNode* mPlatformNode;
     Ogre::AnimationState** mAnimations;
};

#endif //SIMPLE_SCENE_H
