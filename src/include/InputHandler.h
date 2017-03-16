#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

enum Axis {
     VERTICAL,
     HORIZONTAL,
     MOUSE_X,
     MOUSE_Y
};

enum Button {
     VK_ESC,
     VK_A,
     VK_S,
     VK_D,
     VK_W,
};

class InputHandler {
public:
     virtual ~InputHandler(){};
     virtual void update() = 0;
     virtual float getAxis(Axis) = 0;
     virtual bool isButtonDown(Button) = 0;
     virtual bool wasButtonPressed(Button) = 0;
     virtual bool wasButtonReleased(Button) = 0;
};

#endif /* INPUT_HANDLER_H */
