#include "Arduino.h"
#include "VictorSP.h"
#include <Servo.h>

VictorSP::VictorSP(int pin) {
  victor.attach(pin);
  inverted = false;
}
VictorSP::VictorSP(int pin, boolean inverted) {
  victor.attach(pin);
  this->inverted = inverted;
}

void VictorSP::writeSpeed(double speed) {
  if(speed > 1) {
    speed = 1;
  } else if (speed < -1) {
    speed = -1;
  }
  speed = (inverted) ? -speed : speed;
  int out = 90 + (speed * 90);
  victor.write(out);
}
void VictorSP::setInverted(boolean inverted) {
  this->inverted = inverted;
}
void VictorSP::cycleInverted() {
  this->inverted = !this->inverted;
}
boolean VictorSP::isInverted() {
  return this->inverted;
}
