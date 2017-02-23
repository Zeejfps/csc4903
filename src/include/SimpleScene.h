#ifndef SIMPLE_SCENE_H
#define SIMPLE_SCENE_H

#include "Scene.h"
#include <OgreSceneNode.h>
#include <OgreAnimationState.h>

class SimpleScene : public Scene {

public:
     SimpleScene(Ogre::Root*, Ogre::RenderWindow*);
     bool load();
     bool update(float);

private:
     Ogre::SceneNode *mPlatformNode;
     Ogre::AnimationState **mAnimations;
};

#endif //SIMPLE_SCENE_H
