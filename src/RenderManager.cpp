#include "RenderManager.h"
#include "GameManager.h"
#include "SceneParser.h"
#include <OgreWindowEventUtilities.h>
#include <iostream>
using namespace std;

Ogre::SceneNode* platformNode = NULL;
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

      //the Ogre viewport corresponds to a clipping region into which the contents of the camera view will be rendered in the window on each frame
      //by default, the size of the viewport matches the size of the window, but the viewport can be cropped
      //the camera represents a view into an existing scene and the viewport represents a region into which an existing camera will render its contents
      camera = scene_manager->createCamera("Camera");

      //z-order, left, top, width, height
      viewport = window->addViewport(camera, 0, 0.0, 0.0, 1.0, 1.0);  //assign a camera to a viewport (can have many cameras and viewports in a single window)
      viewport->setBackgroundColour(Ogre::ColourValue(0,0,0));

      float actual_width = Ogre::Real(viewport->getActualWidth());
      float actual_height = Ogre::Real(viewport->getActualHeight());
      float aspect_ratio = actual_width/actual_height;
      camera->setAspectRatio(aspect_ratio);

	 root->addFrameListener(this);

	 Ogre::Light* light = scene_manager->createLight("MainLight");
	 light->setPosition(Ogre::Vector3(20, 80, 50));

	 camera->setPosition(Ogre::Vector3(0, 7.5, 14));
	 camera->lookAt(Ogre::Vector3(0, 0, 0));
	 camera->setNearClipDistance(0.1);
	 camera->setFarClipDistance(100);

	 scene_manager->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
	 scene_manager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

	 Ogre::ResourceGroupManager& rgm = Ogre::ResourceGroupManager::getSingleton();
	 Ogre::Log* logger = Ogre::LogManager::getSingleton().getDefaultLog();
	 logger->logMessage("Parsing scene...");
	 if (!parseScene("./assets/scenes/Simple.xml", scene_manager, rgm, logger)) {
		 logger->logMessage("Failed to parse scene");
		 return;
	 }

	 platformNode = scene_manager->getSceneNode("PlatformNode");
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

    //Need to capture/update each device
    //mKeyboard->capture();
    //mMouse->capture();

    //if(mKeyboard->isKeyDown(OIS::KC_ESCAPE))
        //return false;

    return true;
}

void RenderManager::buildSimpleScene() {
	/*Ogre::ResourceGroupManager& rgm = Ogre::ResourceGroupManager::getSingleton();
	rgm.addResourceLocation("./assets/models", "FileSystem", "Lvl1");
	rgm.addResourceLocation("./assets/materials", "FileSystem", "Lvl1");
	rgm.declareResource("Truck.mesh", "Mesh", "Lvl1");
	rgm.declareResource("Ground.mesh", "Mesh", "Lvl1");
	rgm.declareResource("Wheel.mesh", "Mesh", "Lvl1");
	rgm.declareResource("Platform.mesh", "Mesh", "Lvl1");
	rgm.declareResource("Monkey.mesh", "Mesh", "Lvl1");
	rgm.initialiseResourceGroup("Lvl1");
	rgm.loadResourceGroup("Lvl1", true, true);

	Ogre::Entity* groundEntity = scene_manager->createEntity("Ground.mesh");
	groundEntity->setMaterialName("Ground-Material");
	Ogre::SceneNode* groundNode = scene_manager->getRootSceneNode()->createChildSceneNode("Ground");
	groundNode->attachObject(groundEntity);

	Ogre::Entity* platformEntity = scene_manager->createEntity("Platform.mesh");
	platformEntity->setMaterialName("Default-Material");
	platformNode = groundNode->createChildSceneNode("Platform", Ogre::Vector3(0, 0.4, 0));
	platformNode->attachObject(platformEntity);

	Ogre::Entity* truckEntity = scene_manager->createEntity("Truck.mesh");
	truckEntity->setMaterialName("Default-Material");

	Ogre::SceneNode* truckNode = platformNode->createChildSceneNode("Truck", Ogre::Vector3(0, 1.68, 0));
	truckNode->attachObject(truckEntity);

	Ogre::Entity* monkeyEntity = scene_manager->createEntity("Monkey.mesh");
	monkeyEntity->setMaterialName("Monkey-Material");

	Ogre::SceneNode* monkeyNode = truckNode->createChildSceneNode("Monkey", Ogre::Vector3(-0.1, 0.4, -1.6));
	monkeyNode->attachObject(monkeyEntity);
	monkeyNode->rotate(Ogre::Vector3::UNIT_Y, Ogre::Degree(-56));
	monkeyNode->rotate(Ogre::Vector3::UNIT_X, Ogre::Degree(-46));
	monkeyNode->rotate(Ogre::Vector3::UNIT_Y, Ogre::Degree(25));

	Ogre::Entity* rightWheelEntity = scene_manager->createEntity("Wheel.mesh");
	rightWheelEntity->setMaterialName("Wheel-Material");
	Ogre::SceneNode* rightWheelNode = truckNode->
				createChildSceneNode("Right Wheel", Ogre::Vector3(-1.4, -0.69, 2.1));
	rightWheelNode->attachObject(rightWheelEntity);

	Ogre::Entity* leftWheelEntity = scene_manager->createEntity("Wheel.mesh");
	leftWheelEntity->setMaterialName("Wheel-Material");
	Ogre::SceneNode* leftWheelNode = truckNode->
				createChildSceneNode("Left Wheel", Ogre::Vector3(1.4, -0.69, 2.1), Ogre::Quaternion(Ogre::Degree(180), Ogre::Vector3::UNIT_Y));
	leftWheelNode->attachObject(leftWheelEntity);

	Ogre::Entity* leftBackWheelEntity = scene_manager->createEntity("Wheel.mesh");
	leftBackWheelEntity->setMaterialName("Wheel-Material");
	Ogre::SceneNode* leftBackWheelNode = truckNode->
				createChildSceneNode("Left Back Wheel", Ogre::Vector3(1.4, -0.69, -1.59), Ogre::Quaternion(Ogre::Degree(180), Ogre::Vector3::UNIT_Y));
	leftBackWheelNode->attachObject(leftBackWheelEntity);

	Ogre::Entity* rightBackWheelEntity = scene_manager->createEntity("Wheel.mesh");
	rightBackWheelEntity->setMaterialName("Wheel-Material");
	Ogre::SceneNode* rightBackWheelNode = truckNode->
				createChildSceneNode("Right Back Wheel", Ogre::Vector3(-1.4, -0.69, -1.59));
	rightBackWheelNode->attachObject(rightBackWheelEntity);

	Ogre::Light* light = scene_manager->createLight("MainLight");
	light->setPosition(20, 80, 50);*/
}
