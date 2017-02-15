#include "SimpleScene.h"
#include "SceneParser.h"

SimpleScene::SimpleScene(Ogre::Root *pRoot, Ogre::RenderWindow *pWindow) : Scene(pRoot, pWindow){
     mSceneManager->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
     mSceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
}

void SimpleScene::load() {
     Ogre::ResourceGroupManager& rgm = Ogre::ResourceGroupManager::getSingleton();
     Ogre::Log* logger = Ogre::LogManager::getSingleton().getDefaultLog();
     parseScene("./assets/scenes/Simple.scene", mSceneManager, rgm, logger);

     Ogre::Camera* camera = mSceneManager->getCamera("MainCamera");
     Ogre::Viewport* viewport = mWindow->addViewport(camera, 0, 0.0, 0.0, 1.0, 1.0);
     viewport->setBackgroundColour(Ogre::ColourValue(0,0,0));

     float actual_width = Ogre::Real(viewport->getActualWidth());
     float actual_height = Ogre::Real(viewport->getActualHeight());
     float aspect_ratio = actual_width/actual_height;
     camera->setAspectRatio(aspect_ratio);

     mPlatformNode = mSceneManager->getSceneNode("PlatformNode");

     mAnimations = new Ogre::AnimationState*[3];

     Ogre::SceneNode* node;
     Ogre::Entity* entity;

     node = mSceneManager->getSceneNode("Squirrel01");
     entity = (Ogre::Entity*)node->getAttachedObject("Squirrel01");
     mAnimations[0] = entity->getAnimationState("my_animation");
     mAnimations[0]->setLoop(true);
     mAnimations[0]->setEnabled(true);

     node = mSceneManager->getSceneNode("Squirrel02");
     entity = (Ogre::Entity*)node->getAttachedObject("Squirrel02");
     mAnimations[1] = entity->getAnimationState("my_animation");
     mAnimations[1]->setLoop(true);
     mAnimations[1]->setEnabled(true);
     
     mAnimations[2] = mSceneManager->getAnimationState("rotate");
     mAnimations[2]->setLoop(true);
     mAnimations[2]->setEnabled(true);
}

bool SimpleScene::update(float dt) {
     mPlatformNode->rotate(Ogre::Vector3::UNIT_Y, Ogre::Degree(25 * dt));
     for (int i = 0; i < 3; i++) {
          mAnimations[i]->addTime(dt);
     }
     return true;
}

void SimpleScene::unload() {

}
