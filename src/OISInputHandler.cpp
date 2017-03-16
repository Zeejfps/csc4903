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
     if(mInputManager) {
          mInputManager->destroyInputObject(mMouse);
          mInputManager->destroyInputObject(mKeyboard);
          OIS::InputManager::destroyInputSystem(mInputManager);
          mInputManager = NULL;
     }
}

bool OISInputHandler::keyPressed(const OIS::KeyEvent &evt) {
     mKeysPressed[evt.key] = true;
     return true;
}

bool OISInputHandler::keyReleased(const OIS::KeyEvent &evt) {
     mKeysReleased[evt.key] = true;
     return true;
}

void OISInputHandler::update() {
     std::map<OIS::KeyCode, bool>::iterator it;

     for (it = mKeysPressed.begin(); it != mKeysPressed.end(); it++) {
          mKeysPressed[it->first]=false;
     }
     for (it = mKeysReleased.begin(); it != mKeysReleased.end(); it++) {
          mKeysReleased[it->first]=false;
     }

     mouseX = 0;
     mouseY = 0;
     mKeyboard->capture();
     mMouse->capture();
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

bool OISInputHandler::isButtonDown(Button button) {
     OIS::KeyCode code = mapButtonToKey(button);
     return mKeyboard->isKeyDown(code);
}

bool OISInputHandler::wasButtonPressed(Button button) {
     OIS::KeyCode code = mapButtonToKey(button);
     return mKeysPressed[code];
}

bool OISInputHandler::wasButtonReleased(Button button) {
     OIS::KeyCode code = mapButtonToKey(button);
     return mKeysReleased[code];
}

bool OISInputHandler::mouseMoved(const OIS::MouseEvent &evt) {
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

void OISInputHandler::windowClosed(Ogre::RenderWindow* rw) {}

OIS::KeyCode OISInputHandler::mapButtonToKey(Button button) {
     switch (button) {
          case VK_ESC:
               return OIS::KC_ESCAPE;
          case VK_A:
               return OIS::KC_A;
          case VK_S:
               return OIS::KC_S;
          case VK_D:
               return OIS::KC_D;
          case VK_W:
               return OIS::KC_W;
          default:
               return OIS::KC_UNASSIGNED;
     }
}
