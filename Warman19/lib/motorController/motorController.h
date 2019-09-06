#ifndef motorController_H
#define motorController_H

#include <Arduino.h>
#include <L298N.h>

class motorController
{
public:
    void setSpeed(float speed);
    void move(int direction);
    void stop();
    void rotate(int direction);
    float *getMotorState(int motorNum);
    float **getMovementState();

private:
};

#endif