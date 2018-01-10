#include <Servo.h>
#define MOTORPIN1 11
#define MOTORPIN2 5

#define POTPIN1 0 // values for motorpin1
#define POTPIN2 4 // values for motorpin2

#define DEADZONE 1

Servo servo1;
Servo servo2;

void setup() {
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
  int val1 = analogRead(POTPIN1);
  int val2 = analogRead(POTPIN2);
  val1 = processInput(val1);
  val2 = processInput(val2);
  servo1.write(val1);
  servo2.write(val2);
}
