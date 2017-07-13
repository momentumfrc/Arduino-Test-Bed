/*
 * VictorSP.h - A library for interfacing with VictorSP motor controllers.
 * Created by Jordan Powers, July 13, 2017
 */
#ifndef VictorSP_h
#define VictorSP_h
#include <Servo.h>

#include "Arduino.h"

class VictorSP {
  public:
    VictorSP(int pin);
    VictorSP(int pin, boolean inverted);
    void writeSpeed(double speed);
    void setInverted(boolean inverted);
    void cycleInverted();
    boolean isInverted();
   private:
    boolean inverted;
    Servo victor;
};

#endif
