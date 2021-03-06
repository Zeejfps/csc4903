#ifndef SIMPLE_SCENE_H
#define SIMPLE_SCENE_H

#include "Scene.h"
#include "InputHandler.h"
#include <OgreSceneNode.h>
#include <OgreAnimationState.h>

class SimpleScene : public Scene {

public:
     SimpleScene(Ogre::Root*, Ogre::RenderWindow*);
     bool load();
     bool update(float);

private:
     InputHandler* mInput;
     Ogre::SceneNode *mPlatformNode;
     Ogre::SceneNode *mCameraNode;
     Ogre::AnimationState **mAnimations;
};

#endif //SIMPLE_SCENE_H
