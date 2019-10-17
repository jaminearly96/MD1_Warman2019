#include <Arduino.h>
#include <L298N.h>
#include <Stepper.h>

int speed = 0.5;

#define Motor1Pin1 11
#define Motor1Pin2 12
#define Motor1PinPWM 10
#define Motor2Pin1 8
#define Motor2Pin2 9
#define Motor2PinPWM 7
#define Motor3Pin1 5
#define Motor3Pin2 6
#define Motor3PinPWM 4
#define Motor4Pin1 2
#define Motor4Pin2 1
#define Motor4PinPWM 3

#define StepperPin1 18
#define StepperPin2 17
#define StepperPin3 16
#define StepperPin4 15

const int stepsPerRevolution = 100;
int stepperSpeed = 400;

// Stepper Declaration
Stepper stepper = Stepper(stepsPerRevolution, StepperPin4, StepperPin3, StepperPin2, StepperPin1);

// Motor Declaration
L298N motor1(Motor1PinPWM, Motor1Pin1, Motor1Pin2);
L298N motor2(Motor2PinPWM, Motor2Pin1, Motor2Pin2);
L298N motor3(Motor3PinPWM, Motor3Pin1, Motor3Pin2);
L298N motor4(Motor4PinPWM, Motor4Pin1, Motor4Pin2);

// Sets the speed of the motors
void setSpeed(float speed)
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
void move(int direction, int delayPeriod)
{
  switch (direction)
  {
  case 1:
    motor1.stop();
    motor2.forward();
    motor3.stop();
    motor4.forward();
    break;
  case 2:
    motor1.stop();
    motor2.backward();
    motor3.stop();
    motor4.backward();
    break;
  case 3:
    motor1.backward();
    motor2.stop();
    motor3.backward();
    motor4.stop();
    break;
  case 4:
    motor1.forward();
    motor2.stop();
    motor3.forward();
    motor4.stop();
    break;
  }
  for (float i = 0; i >= speed; i += 0.001)
  {
    setSpeed(i);
    delay(10);
  }
  delay(delayPeriod - 500);
}

// Stops all motors. duh
void stop()
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
void rotate(int direction, int delayPeriod)
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

// Pickup Balls
void pickup()
{
}

// Dropoff Balls
void dropoff()
{
}

void setup()
{
  // Start serial monitor
  Serial.begin(9600);
  delay(5000);
  stepper.setSpeed(stepperSpeed);
}

void loop()
{
  stepper.step(200);
  delay(2000);
  // Step on revolution in the other direction:
  stepper.step(-200);
  delay(2000);
  // move(4, 1500);
  // stop();
  // pickup();
  // delay(500);
  // move(1, 1000);
  // stop();
  // pickup();
  // delay(800);
  // move(1, 1000);
  // stop();
  // pickup();
  // delay(1000);
  // move(3, 3000);
  // stop();
  // dropoff();
  // delay(100000);
}