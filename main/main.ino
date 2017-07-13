#include <VictorSP.h>

#define VictorSP1 5
#define VictorSP2 6

VictorSP vic1(VictorSP1);
VictorSP vic2(VictorSP2);

typedef struct {
  int pin;
  int potMode;
} Pot;

typedef struct {
  int pin;
  boolean down : false;
} Button;

Pot pot1 = {0,1};
Pot pot2 = {1,1};

Button button1 = {4, false};
Button button2 = {7, false};

/*
 * Returns a value between -1 and 1 based on the read mode for the potentiometer
 * 0 - Returns a value between -1 and 0
 * 1 - Returns a value between -1 and 1
 * 2 - Returns a value between 0 and 1
 */
double readPot(Pot& pot) {
  switch(pot.potMode) {
    case 0:
      return -(analogRead(pot.pin) / 1023)
      break;
     case 1:
      double ret = analogRead(pot.pin) - 511.5
      if(-0.5 <= ret <= 0.5) {
        return 0;
      } else {
        return ret / 511.5;
      }
      break;
     case 2:
      return (analogRead(pot.pin) / 1023);
      break;
     default:
      return 0;
      break;
  }
}
void cyclePinmode(Pot& pot) {
  if(++pot.potMode == 3) {
    pot.potMode = 0;
  }
}

boolean isFirstPush(Button& button) {
  if(digitalRead(button.pin)) {
    if(button.down) {
      return false;
    } else {
      button.down = true;
      return true;
    }
  } else {
    button.down = false;
    return false;
  }
}

void setup() {
  pinMode(button1.pin, INPUT);
  pinMode(button2.pin, INPUT);
}

void loop() {
  vic1.writeSpeed(readPot(pot1));
  vic2.writeSpeed(readPot(pot2));
  if(isFirstPush(button1)) {
    cyclePinmode(pot1);
  }
  if(isFirstPush(button2)) {
    cyclePinmode(pot2);
  }
  }
  
}
