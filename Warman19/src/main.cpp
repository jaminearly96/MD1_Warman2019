#include <Arduino.h>
#include <L298N.h>
#include <Stepper.h>
#include <PWMServo.h>

/**********************************************************
 * Tweak these to modify timing for each movement 
 **********************************************************/
#define Roll1 2500
#define Roll2 1000
#define Roll3 1000
#define Roll4 2500
#define Roll5 2500
#define Lower1 2700
#define Lift1 1200
#define Lower2 1200
#define Lift2 1200
#define Lower3 1200
#define Lift3 2700
/********************************************************/

// Pin assignments for motor pins
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

#define ServoPin 14

int speed = 0.5; // Assign value between 0 and 1 to modify the wheel speed
const int stepsPerRevolution = 200; // How many steps are in a full revolution of the stepper
int stepperSpeed = 80; // The speed of the stepper motor in steps/second

// Stepper Declaration
Stepper stepper = Stepper(stepsPerRevolution, 18, 17, 16, 15);
PWMServo servo;

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
  delay(delayPeriod);
  // for (float i = 0; i >= speed; i += 0.001)
  // {
  //   setSpeed(i);
  //   delay(10);
  // }
  // delay(delayPeriod - 500);
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

void lift(int steps){
  stepper.step(-1 * steps);
}

void lower(int steps){
  stepper.step(steps);
}

void testStepper()
{
  stepper.step(200);
  delay(2000);
  // Step on revolution in the other direction:
  stepper.step(-200);
  delay(2000);
}

void turnServo(int i){
  int val = i;
  // val = map(val, 0, 1023, 0, 180);
  servo.write(val);
  delay(2000);
}

void setup()
{
  // Start serial monitor
  Serial.begin(9600);
    turnServo(0);
  delay(5000);
  stepper.setSpeed(stepperSpeed);
  servo.attach(ServoPin);
}

void loop()
{
  move(4, Roll1);
  stop();
  lower(Lower1);
  delay(100);
  lift(Lift1);
  move(2, Roll2);
  stop();
  lower(Lower2);
  lift(Lift2);
  move(2, Roll3);
  stop();
  lower(Lower3);
  lift(Lift3);
  move(3, Roll4);
  stop();
  rotate(1, 1000);
  stop();
  move(4, Roll5);
  stop();
  turnServo(180);
  delay(100000);
}