#include "RenderManager.h"
#include "GameManager.h"
#include "SimpleScene.h"
//#include "SceneParser.h"
#include <OgreWindowEventUtilities.h>
#include <iostream>
using namespace std;

void RenderManager::init()
{
	root = NULL;
	window = NULL;
	scene = NULL;

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
	window->getCustomAttribute("WINDOW", &window_handle);
	root->addFrameListener(this);

	scene = new SimpleScene(root, window);
	if (!scene->load()) {
		cout << "Failed" << endl;
	}
}

RenderManager::RenderManager(GameManager* gm)
{
	game_manager = gm;
	init();
}

RenderManager::~RenderManager()
{
	game_manager = NULL;

	window->removeAllViewports();
	window->destroy();
	window = NULL;

	delete scene;
	scene = NULL;

	delete root;
	root = NULL;
}

size_t RenderManager::getRenderWindowHandle()
{
	return window_handle;
}


void RenderManager::startRendering()
{
	root->startRendering();
}

Ogre::RenderWindow* RenderManager::getRenderWindow()
{
	return window;
}

bool RenderManager::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	if(window->isClosed())
	return false;

	scene->update(evt.timeSinceLastFrame);

	//Need to capture/update each device
	//mKeyboard->capture();
	//mMouse->capture();

	//if(mKeyboard->isKeyDown(OIS::KC_ESCAPE))
	//return false;

	return true;
}
