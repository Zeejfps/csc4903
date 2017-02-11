#include "RenderManager.h"
#include "GameManager.h"
#include "SceneParser.h"
#include <OgreWindowEventUtilities.h>
#include <iostream>
using namespace std;

Ogre::SceneNode* platformNode = NULL;
Ogre::AnimationState* state = NULL;
void RenderManager::init()
{
	root = NULL;
	window = NULL;
	scene_manager = NULL;

	root = OGRE_NEW Ogre::Root("","");  //resource/config files go here
	root->loadPlugin("RenderSystem_GL");  //prepares external dlls for later use

      Ogre::RenderSystem* render_system = root->getRenderSystemByName("OpenGL Rendering Subsystem"); //just returns a pointer to an uninialized render system
      if (!render_system)
      {
         //ASSERT_CRITICAL(false);
      }

      root->setRenderSystem(render_system);
      //manually set configuration options
      render_system->setConfigOption("Full Screen", "No");
      render_system->setConfigOption("Video Mode", "800 x 600 @ 32-bit colour");

      //initialize render system
      //automatically create the window and give it a title
      window = root->initialise(true, "Z's Awesome Game 9000");

      scene_manager = root->createSceneManager(Ogre::ST_GENERIC, "Default Scene Manager");
      window->getCustomAttribute("WINDOW", &window_handle);

	 scene_manager->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
	 scene_manager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

	 Ogre::ResourceGroupManager& rgm = Ogre::ResourceGroupManager::getSingleton();
	 Ogre::Log* logger = Ogre::LogManager::getSingleton().getDefaultLog();
	 logger->logMessage("Parsing scene...");
	 if (!parseScene("./assets/scenes/Simple.scene", scene_manager, rgm, logger)) {
		 logger->logMessage("Failed to parse scene");
		 return;
	 }

	 camera = scene_manager->getCamera("MainCamera");

      viewport = window->addViewport(camera, 0, 0.0, 0.0, 1.0, 1.0);  //assign a camera to a viewport (can have many cameras and viewports in a single window)
      viewport->setBackgroundColour(Ogre::ColourValue(0,0,0));

      float actual_width = Ogre::Real(viewport->getActualWidth());
      float actual_height = Ogre::Real(viewport->getActualHeight());
      float aspect_ratio = actual_width/actual_height;
      camera->setAspectRatio(aspect_ratio);

	 root->addFrameListener(this);

	 camera->setNearClipDistance(0.1);
	 camera->setFarClipDistance(100);

	 platformNode = scene_manager->getSceneNode("PlatformNode");
	 Ogre::SceneNode* squirrelNode = scene_manager->getSceneNode("Squirrel01");
	 Ogre::Entity* e = (Ogre::Entity*)squirrelNode->getAttachedObject("Squirrel01");
	 state = e->getAnimationState("my_animation");
	 state->setLoop(true);
	 state->setEnabled(true);
	 /*Ogre::AnimationStateSet* anims  = e->getAllAnimationStates();
	 Ogre::AnimationStateIterator iter = anims->getAnimationStateIterator();
	 while(iter.hasMoreElements()) {
	 	logger->logMessage(iter.getNext()->getAnimationName());
	}*/
}

RenderManager::RenderManager(GameManager* gm)
{
   game_manager = gm;
   init();
}

RenderManager::~RenderManager()
{
   game_manager = NULL;

   scene_manager->clearScene();
   scene_manager->destroyAllCameras();

   window->removeAllViewports();

   window->destroy();
   window = NULL;

   delete root;
   root = NULL;
}

size_t RenderManager::getRenderWindowHandle()
{
   return window_handle;
}

int RenderManager::getRenderWindowWidth()
{
   return viewport->getActualWidth();
}

int RenderManager::getRenderWindowHeight()
{
   return viewport->getActualHeight();
}

void RenderManager::startRendering()
{
   root->startRendering();
}

Ogre::RenderWindow* RenderManager::getRenderWindow()
{
   return window;
}

Ogre::SceneManager* RenderManager::getSceneManager()
{
   return scene_manager;
}

bool RenderManager::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    	if(window->isClosed())
        	return false;

    	platformNode->rotate(Ogre::Vector3::UNIT_Y, Ogre::Degree(25 * evt.timeSinceLastFrame));
	if (state != NULL) {
		state->addTime(evt.timeSinceLastFrame);
	}

    	//Need to capture/update each device
    	//mKeyboard->capture();
    	//mMouse->capture();

    	//if(mKeyboard->isKeyDown(OIS::KC_ESCAPE))
        //return false;

    	return true;
}
