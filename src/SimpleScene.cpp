#include "SimpleScene.h"
#include "SceneParser.h"

SimpleScene::SimpleScene(Ogre::SceneManager* pSceneManager) {
     mSceneManager = pSceneManager;
}

void SimpleScene::load() {
     Ogre::ResourceGroupManager& rgm = Ogre::ResourceGroupManager::getSingleton();
     Ogre::Log* logger = Ogre::LogManager::getSingleton().getDefaultLog();
     parseScene("./assets/scenes/Simple.scene", mSceneManager, rgm, logger);

     mPlatformNode = mSceneManager->getSceneNode("PlatformNode");

     mAnimations = new Ogre::AnimationState*[2];

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
}

void SimpleScene::update(float dt) {
     mPlatformNode->rotate(Ogre::Vector3::UNIT_Y, Ogre::Degree(25 * dt));
     for (int i = 0; i < 2; i++) {
          mAnimations[i]->addTime(dt);
     }
}
