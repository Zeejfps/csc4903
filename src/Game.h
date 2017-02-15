#ifndef GAME_H
#define GAME_H

#include "Ogre.h"
#include "OgreWindowEventUtilities.h"
#include "Scene.h"

class Game : public Ogre::FrameListener
{
public:
     Game();
     ~Game();
     void init(Scene*);
     bool frameStarted(const Ogre::FrameEvent&);
     bool frameRenderingQueued(const Ogre::FrameEvent&);
     bool frameEnded(const Ogre::FrameEvent&);
     Ogre::RenderWindow* Window();
     Ogre::Root* Root();

private:
     Ogre::Root* mRoot;
     Ogre::RenderWindow* mWindow;
     Scene* mScene;
};

#endif /* GAME_H */
