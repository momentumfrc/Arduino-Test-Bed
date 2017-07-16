#include "Arduino.h"
#include "FRCMotor.h"
#include <Servo.h>

FRCMotor::FRCMotor(int pin) {
  motor.attach(pin);
  inverted = false;
}
FRCMotor::FRCMotor(int pin, boolean inverted) {
  motor.attach(pin);
  this->inverted = inverted;
}

void FRCMotor::writeSpeed(double speed) {
  if(speed > 1) {
    speed = 1;
  } else if (speed < -1) {
    speed = -1;
  }
  speed = (inverted) ? -speed : speed;
  int out = 90 + (speed * 90);
  motor.write(out);
}
void FRCMotor::setInverted(boolean inverted) {
  this->inverted = inverted;
}
void FRCMotor::cycleInverted() {
  this->inverted = !this->inverted;
}
boolean FRCMotor::isInverted() {
  return this->inverted;
}
