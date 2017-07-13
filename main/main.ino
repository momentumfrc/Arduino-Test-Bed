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
  boolean down;
  unsigned long downTime;
  int lastEvent;
} Button;

typedef struct {
  VictorSP vic;
  Pot pot;
  Button button;
  boolean slave;
} Motor;

int len;
Motor motors[] = { 
  {vic1, {0, 1}, {4, false}, false}, 
  {vic2, {1,1}, {7, false}, false}
  };

Motor *master = &motors[0];

/*
   Returns a value between -1 and 1 based on the read mode for the potentiometer
   0 - Returns a value between -1 and 0
   1 - Returns a value between -1 and 1
   2 - Returns a value between 0 and 1
*/
double readPot(Pot& pot) {
  switch (pot.potMode) {
    case 0:
      return -(analogRead(pot.pin) / 1023);
             break;
    case 1:
      {
        double ret = analogRead(pot.pin) - 511.5;
        if (-0.5 <= ret <= 0.5) {
          return 0;
        } else {
          return ret / 511.5;
        }
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
  if (++pot.potMode == 3) {
    pot.potMode = 0;
  }
}

/**
 * 0 - Button not pushed
 * 1 - Regular push event
 * 2 - Button held more than heldSeconds
 */
int buttonType(Button& button, int heldSeconds) {
  int out;
   if(digitalRead(button.pin)) {
    if(!button.down){
      button.down = true;
      button.downTime = millis();
    }
  } else if(button.down) {
    if((millis() - button.downTime) > heldSeconds * 1000) {
        out = 2;
    } else {
      out = 1;
    }
    button.down = false;
  } else {
    out = 0;
  }
  return out;
}

void setup() {
  len = sizeof(motors) / sizeof(Motor);
  for( int i = 0; i < len; i++) {
    pinMode(motors[i].button.pin, INPUT);
  }
}

void switchButtonEvent(Motor& m) {
  m.button.lastEvent = buttonType(m.button, 5);
  
  if((m.button.down && master->button.down) && (master != &m)) {
    m.slave = true;
  }
  if(!m.slave) {
    switch(m.button.lastEvent) {
      case 1:
        cyclePinmode(m.pot);
        break;
      case 2:
        m.vic.cycleInverted();
        break;
      default:
        break;
    }
    m.vic.writeSpeed(readPot(m.pot));
  } else {
    if(m.button.lastEvent == 2) {
      m.slave = false;
    } else {
      m.vic.writeSpeed(readPot(master->pot));
    } 
  }
}

void loop() {
  for(int i = 0; i < len; i++) {
    switchButtonEvent(motors[i]);
  }
}
