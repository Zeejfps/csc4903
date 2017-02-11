#if !defined RENDER_MANAGER
#define RENDER_MANAGER

#include "Ogre.h"
#include <tinyxml.h>

class GameManager;

class RenderManager : public Ogre::FrameListener
{
   private:
      Ogre::Root* root;
      Ogre::RenderWindow* window;
      Ogre::SceneManager* scene_manager;

      Ogre::Camera* camera;
      Ogre::Viewport* viewport;

      GameManager* game_manager;

      void init();
      bool frameRenderingQueued(const Ogre::FrameEvent&);
      size_t window_handle;
      Ogre::Real time_since_last_frame;

   public:
      RenderManager(GameManager* game_manager);
      virtual ~RenderManager();

      size_t getRenderWindowHandle();
      int getRenderWindowWidth();
      int getRenderWindowHeight();

      Ogre::RenderWindow* getRenderWindow();
      Ogre::SceneManager* getSceneManager();

      void startRendering();
      void stopRendering();
};

#endif
