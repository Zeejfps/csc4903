#ifndef OIS_INPUT_HANDLER_H
#define OIS_INPUT_HANDLER_H

#include "InputHandler.h"

#include <map>
#include <OISMouse.h>
#include <OISKeyboard.h>
#include <OISInputManager.h>
#include <OgreRenderWindow.h>
#include <OgreWindowEventUtilities.h>

class OISInputHandler : public InputHandler, public OIS::KeyListener, public OIS::MouseListener, public Ogre::WindowEventListener {
public:
     OISInputHandler(Ogre::RenderWindow*);
     ~OISInputHandler();
     void update();
     float getAxis(Axis);
     bool isButtonDown(Button);
     bool wasButtonPressed(Button);
     bool wasButtonReleased(Button);
     bool keyPressed(const OIS::KeyEvent&);
     bool keyReleased(const OIS::KeyEvent&);
     bool mouseMoved(const OIS::MouseEvent&);
     bool mousePressed(const OIS::MouseEvent&, OIS::MouseButtonID);
     bool mouseReleased(const OIS::MouseEvent&, OIS::MouseButtonID);
     void windowResized(Ogre::RenderWindow* rw);
     void windowClosed(Ogre::RenderWindow* rw);
private:
     OIS::InputManager* mInputManager;
     OIS::Keyboard* mKeyboard;
     OIS::Mouse* mMouse;
     int mWindowHnd;
     float mouseX, mouseY;
     void free();
     OIS::KeyCode mapButtonToKey(Button);
     std::map<OIS::KeyCode, bool> mKeysPressed;
     std::map<OIS::KeyCode, bool> mKeysReleased;
};

#endif /* OIS_INPUT_HANDLER_H */
