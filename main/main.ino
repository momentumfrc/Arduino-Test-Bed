#include <Servo.h>
#define MOTORPIN1 11
#define MOTORPIN2 5

#define POTPIN1 0 // values for motorpin1
#define POTPIN2 4 // values for motorpin2

#define COMP_FWD 6
#define COMP_REV 7

#define SOL_FWD 8
#define SOL_REV 9

#define PRESSURE_SWITCH 3
#define PIST_BUTTON 12

#define DEADZONE 1

Servo servo1;
Servo servo2;

boolean fwd = false;
boolean first = false;

void compressor() {
  digitalWrite(COMP_FWD, digitalRead(PRESSURE_SWITCH));
}

void setup() {
  
  pinMode(COMP_FWD, OUTPUT);
  pinMode(COMP_REV, OUTPUT);

  pinMode(SOL_FWD, OUTPUT);
  pinMode(SOL_REV, OUTPUT);

  pinMode(PRESSURE_SWITCH, INPUT_PULLUP);
  pinMode(PIST_BUTTON, INPUT_PULLUP);
  
  //attachInterrupt(digitalPinToInterrupt(PRESSURE_SWITCH), compressor, CHANGE);
  
  servo1.attach(MOTORPIN1);
  servo2.attach(MOTORPIN2);
}

int processInput(int input) {
  double val = map(input, 0, 1023, 0, 180); // map to servo range
  if (val < 90 - DEADZONE) {
    return map(val, 0, 90 - DEADZONE, 0, 90); // adjust for deadzone, so that it's not a hard jump
  } else if (val > 90 + DEADZONE) {
    return map(val, 90 + DEADZONE, 180, 90, 180);
  } else {
    return 90;
  }
}


void loop() {
  // MOTORS
  int val1 = analogRead(POTPIN1);
  int val2 = analogRead(POTPIN2);
  val1 = processInput(val1);
  val2 = processInput(val2);
  servo1.write(val1);
  servo2.write(val2);

  compressor();

  // PNEUMATICS
  if(digitalRead(PIST_BUTTON)) {
    if(first) {
      first = false;
      fwd = !fwd;
      if(fwd) {
        digitalWrite(SOL_REV, LOW);
        digitalWrite(SOL_FWD, HIGH);
      } else {
        digitalWrite(SOL_FWD, LOW);
        digitalWrite(SOL_REV, HIGH);
      }
    }
  } else {
    first = true;
  }
  
}
