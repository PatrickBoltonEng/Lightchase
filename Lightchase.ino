/*
 * Project Lightchase
 * Description: P&ID control of LED using PWN with phototransitor feedback
 * Author:  Patrick Bolton
 * Date:  05-13-21
 */

#include "Particle.h"
#include "math.h"

SYSTEM_THREAD(ENABLED);

SerialLogHandler logHandler;

#define UPDATE_INTERVAL 1000  //1 sec = 1000 millis
#define PWM_FREQ 100

unsigned long UpdateInterval;

int LED = A0;
int PHOTOTRANS = A1;
int LEDSP, PTRead, updatecount;    //

void setup() 
{
  Serial.begin(9600);
  delay(100);

  pinMode(LED, OUTPUT);
  pinMode(PHOTOTRANS, INPUT);

  UpdateInterval = millis();
  LEDSP=0,
  updatecount = 0;
}

void loop() 
{

  if ((millis() - UpdateInterval) > UPDATE_INTERVAL)
  {
    PTRead=analogRead(PHOTOTRANS);
    Log.info("PTRead(4095): %d", PTRead);
    delayMicroseconds(11);

    analogWrite(LED, LEDSP, PWM_FREQ);
    Log.info("LEDSP(255): %d", LEDSP);
    
    if(updatecount==10)
    {
      if(LEDSP==255){LEDSP=0;}
      else{LEDSP=LEDSP+17;}
      Log.info("LEDSP(255): %d", LEDSP);
      updatecount=0;
    }
    else{updatecount++;}

    UpdateInterval = millis();
  }
}