#ifndef SIMPLE_SCENE_H
#define SIMPLE_SCENE_H

#include "Ogre.h"
#include <tinyxml.h>

class SimpleScene {

public:
     SimpleScene(Ogre::Root*, Ogre::RenderWindow*);
     ~SimpleScene();
     void load();
     void update(float);

private:
     Ogre::RenderWindow *mRenderWindow;
     Ogre::SceneManager *mSceneManager;
     Ogre::SceneNode *mPlatformNode;
     Ogre::AnimationState **mAnimations;
};

#endif //SIMPLE_SCENE_H
