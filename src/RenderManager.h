#if !defined RENDER_MANAGER
#define RENDER_MANAGER

#include "Ogre.h"
#include "SimpleScene.h"
#include <tinyxml.h>

class GameManager;

class RenderManager : public Ogre::FrameListener
{
   private:
      Ogre::Root* root;
      Ogre::RenderWindow* window;

      GameManager* game_manager;

      SimpleScene* scene;

      void init();
      bool frameRenderingQueued(const Ogre::FrameEvent&);
      size_t window_handle;
      Ogre::Real time_since_last_frame;

   public:
      RenderManager(GameManager* game_manager);
      virtual ~RenderManager();

      size_t getRenderWindowHandle();

      Ogre::RenderWindow* getRenderWindow();

      void startRendering();
      void stopRendering();
};

#endif
