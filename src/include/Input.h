#ifndef INPUT_H
#define INPUT_H

enum Axis {
     VERTICAL,
     HORIZONTAL,
     MOUSE_X,
     MOUSE_Y
};

enum Button {
     VK_ESC,
     JS_BUTTON_0,
     JS_BUTTON_1,
};

class Input {
public:
     virtual ~Input(){};
     virtual void update() = 0;
     virtual float getAxis(Axis) = 0;
     virtual bool getButton(Button) = 0;
};

#endif
