#ifndef OIS_INPUT_HANDLER_H
#define OIS_INPUT_HANDLER_H

#include "Input.h"

#include <OISMouse.h>
#include <OISKeyboard.h>
#include <OISInputManager.h>
#include <OgreRenderWindow.h>
#include <OgreWindowEventUtilities.h>

class OISInputHandler : public Input, public OIS::KeyListener, public OIS::MouseListener, public Ogre::WindowEventListener {
public:
     OISInputHandler(Ogre::RenderWindow*);
     ~OISInputHandler();
     void update();
     float getAxis(Axis);
     bool getButton(Button);
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
};

#endif /* OIS_INPUT_HANDLER_H */
