/*
 * FRCMotor.h - A library for interfacing with FRC Motor controllers.
 * Created by Jordan Powers, July 13, 2017
 */
#ifndef FRCMotor_h
#define FRCMotor_h
#include <Servo.h>

#include "Arduino.h"

class FRCMotor {
  public:
    FRCMotor(int pin);
    FRCMotor(int pin, boolean inverted);
    void writeSpeed(double speed);
    void setInverted(boolean inverted);
    void cycleInverted();
    boolean isInverted();
   private:
    boolean inverted;
    Servo motor;
};

#endif
