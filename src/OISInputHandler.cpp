#include <iostream>
#include <sstream>
#include <OISInputHandler.h>

OISInputHandler::OISInputHandler(Ogre::RenderWindow* pWindow) {
     OIS::ParamList pl;
     std::ostringstream windowHndStr;

     std::cout << "not null?\n";
     pWindow->getCustomAttribute("WINDOW", &mWindowHnd);
     windowHndStr << mWindowHnd;
     pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

     mInputManager = OIS::InputManager::createInputSystem(pl);

     mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, true));
     mKeyboard->setEventCallback(this);

     mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject(OIS::OISMouse, true));
     mMouse->setEventCallback(this);

     Ogre::WindowEventUtilities::addWindowEventListener(pWindow, this);
     windowResized(pWindow);
}

OISInputHandler::~OISInputHandler() {
     free();
}

bool OISInputHandler::keyPressed(const OIS::KeyEvent &evt) {
     std::cout << "Key Pressed?!\n";
     return true;
}

bool OISInputHandler::keyReleased(const OIS::KeyEvent &evt) {
     return true;
}

void OISInputHandler::update() {
     mKeyboard->capture();
     mMouse->capture();
}

void OISInputHandler::free() {
     if(mInputManager) {
          mInputManager->destroyInputObject(mMouse);
          mInputManager->destroyInputObject(mKeyboard);
          OIS::InputManager::destroyInputSystem(mInputManager);
          mInputManager = NULL;
     }
}

float OISInputHandler::getAxis(Axis axis) {
     switch (axis) {
          case MOUSE_X:
               return mouseX;
          case MOUSE_Y:
               return mouseY;
     }
     return false;
}

bool OISInputHandler::getButton(Button button) {
     switch (button) {
          case VK_ESC:
               return mKeyboard->isKeyDown(OIS::KC_ESCAPE);
     }
     return false;
}

bool OISInputHandler::mouseMoved(const OIS::MouseEvent &evt) {
     std::cout << "Mouse moved?\n";
     OIS::MouseState state = evt.state;
     mouseX = state.X.rel;
     mouseY = state.Y.rel;
     return true;
}

bool OISInputHandler::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
     std::cout << "Mouse button pressed?\n";
     return true;
}

bool OISInputHandler::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
     return true;
}

void OISInputHandler::windowResized(Ogre::RenderWindow* rw) {
     std::cout << "Resized\n";
     unsigned int width, height, depth;
     int left, top;
     rw->getMetrics(width, height, depth, left, top);

     const OIS::MouseState &ms = mMouse->getMouseState();
     std::cout << width << ", " << height << "\n";
     ms.width = width;
     ms.height = height;
}

void OISInputHandler::windowClosed(Ogre::RenderWindow* rw) {
     free();
}
