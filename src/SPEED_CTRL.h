#ifndef SPEED_CTRL_h
#define SPEED_CTRL_h

class SPEED_CTRL {
  public:
    int motor_ctrl(int ID,int SPEED);
    int start();
    int line();
};

#endif