#include "motorController.h"
#include <L298N.h>

/*********************************************** 
 * Fuck man, I'm glad we have heaps of pins lol
 * Motors are numbered as follows:
 * Motor1 - Front 
 * Motor2-  Right
 * Motor3 - Back
 * Motor4 - Left
 * 
 * If you get confused, its numbered clockwise starting at the front left.
 ***********************************************/
#define Motor1Pin1 0
#define Motor1Pin2 0
#define Motor1PinPWM 0
#define Motor2Pin1 0
#define Motor2Pin2 0
#define Motor2PinPWM 0
#define Motor3Pin1 0
#define Motor3Pin2 0
#define Motor3PinPWM 0
#define Motor4Pin1 0
#define Motor4Pin2 0
#define Motor4PinPWM 0

// Motor Declaration
L298N motor1(Motor1PinPWM, Motor1Pin1, Motor1Pin2);
L298N motor2(Motor2PinPWM, Motor2Pin1, Motor2Pin2);
L298N motor3(Motor3PinPWM, Motor3Pin1, Motor3Pin2);
L298N motor4(Motor4PinPWM, Motor4Pin1, Motor4Pin2);

// Sets the speed of the motors
void motorController::setSpeed(float speed)
{
    motor1.setSpeed(speed * 255);
    motor2.setSpeed(speed * 255);
    motor3.setSpeed(speed * 255);
    motor4.setSpeed(speed * 255);
}

/**********************************************
 * Directions are as follows
 *      1 > Forward
 *      2 > Backwards
 *      3 > Left
 *      4 > Right
 * *********************************************/
void motorController::move(int direction)
{
    switch (direction)
    {
    case 1:
        motor1.stop();
        motor2.forward();
        motor3.backward();
        motor4.stop();
        break;
    case 2:
        motor1.stop();
        motor2.backward();
        motor3.forward();
        motor4.stop();
        break;
    case 3:
        motor1.forward();
        motor2.stop();
        motor3.backward();
        motor4.stop();
        break;
    case 4:
        motor1.backward();
        motor2.stop();
        motor3.forward();
        motor4.stop();
        break;
    }
}

// Stops all motors. duh
void motorController::stop()
{
    motor1.stop();
    motor2.stop();
    motor3.stop();
    motor4.stop();
}

/**********************************************
 * Directions are as follows
 *      1 > Clockwise
 *      2 > Anticlockwise
 * *********************************************/
void motorController::rotate(int direction)
{
    switch (direction)
    {
    case 1:
        motor1.forward();
        motor2.forward();
        motor3.forward();
        motor4.forward();
        break;
    case 2:
        motor1.backward();
        motor2.backward();
        motor3.backward();
        motor4.backward();
    }
}

/**********************************************
 * Returns current state of the motor
 * Returns an array of floats with the following structure
 * [binary movement state][speed (if any)]
 * *********************************************/
float *motorController::getMotorState(int motorNum)
{
    float state[1] = {};
    switch (motorNum)
    {
    case 1:
        state[0] = motor1.isMoving();
        state[1] = motor1.getSpeed();
        break;
    case 2:
        state[0] = motor2.isMoving();
        state[1] = motor2.getSpeed();
        break;
    case 3:
        state[0] = motor3.isMoving();
        state[1] = motor3.getSpeed();
        break;
    case 4:
        state[0] = motor4.isMoving();
        state[1] = motor4.getSpeed();
        break;
    }
    return state;
}

// Performs same function as getMotorState, but for all motors. Results returned in 2D array
float **motorController::getMovementState()
{
    float **motors = 0;
    motors = new float *[3];
    for (int i = 0; i < 3; i++)
    {
        motors[i] = new float[1];
        float *state = getMotorState(i);
        motors[i][0] = state[0];
        motors[i][1] = state[1];
    }
    return motors;
}