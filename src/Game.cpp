#include "Game.h"

Game::Game() {
     mRoot = OGRE_NEW Ogre::Root("","");
     mRoot->loadPlugin("RenderSystem_GL");

     Ogre::RenderSystem* renderSystem = mRoot->getRenderSystemByName("OpenGL Rendering Subsystem");
     if (!renderSystem){
          //ASSERT_CRITICAL(false);
     }
     mRoot->setRenderSystem(renderSystem);
     renderSystem->setConfigOption("Full Screen", "No");
     renderSystem->setConfigOption("Video Mode", "800 x 600 @ 32-bit colour");
     mWindow = mRoot->initialise(true, "Z's Awesome Game 9000");
     mRoot->addFrameListener(this);
}

void Game::init(Scene* pScene) {
     //mScene = pScene;
     //mScene->load();
     mRoot->startRendering();
}

bool Game::frameStarted(const Ogre::FrameEvent& evt){
     return true;
}

bool Game::frameRenderingQueued(const Ogre::FrameEvent& evt) {
     if(mWindow->isClosed())
		return false;
     return true;//mScene->update(evt.timeSinceLastFrame);
}

bool Game::frameEnded(const Ogre::FrameEvent& evt) {
     return true;
}

Ogre::RenderWindow* Game::Window() {
     return mWindow;
}

Ogre::Root* Game::Root() {
     return mRoot;
}

Game::~Game() {
     mWindow->removeAllViewports();
     mWindow->destroy();
     delete mScene;
     delete mRoot;
}
