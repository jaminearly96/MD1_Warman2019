#include <Arduino.h>
#include <motorController.h>

motorController speedyboi;
int speed = 0.5;

void setup()
{
  // Start serial monitor
  Serial.begin(9600);

  // Use this to modify the speed. Put in a value between 0 and 1.
  speedyboi.setSpeed(speed);

  // Use this to move along each 4 axis. Look in the motor controller library for directions
  speedyboi.move(1);

  // Writes the current speed info of the motor to the screen every tick. Breaks after 100 ticks. This is likely to be broken bc fk cpp 2d arrays lol
  for (int ticks = 0; ticks >= 100; ticks += 10)
  {
    float **motorStates = speedyboi.getMovementState();
    for (int i = 0; i < 3; ++i)
    {
      Serial.print("Moving: ");
      Serial.print(motorStates[i][0]);
      Serial.print(" Speed: ");
      Serial.print(motorStates[i][1]);
      Serial.println();
    }
    delay(10);
    Serial.write(27);
    Serial.print("[2J");
    Serial.write(27);
    Serial.print("[H");
  }

  // Stops the motors
  speedyboi.stop();
}

void loop()
{
  // dab
}