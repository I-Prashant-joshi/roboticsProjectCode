#include <PS2X_lib.h>  
#define en1 3  
#define m1a 4 
#define m1b 5 
#define m2a 7 
#define m2b 8 
#define en2 6 
const int cirdelay = 2000;
int motor_right_speed = 0;
int motor_left_speed = 0;

PS2X ps2x; // create PS2 Controller Class
int error = 0; 
byte type = 0;
byte vibrate = 0;



void setup()
{
  //Motors pin
  pinMode(m1a, OUTPUT);
  pinMode(m1b, OUTPUT);
  pinMode(m2a, OUTPUT);
  pinMode(m2b, OUTPUT);
  //pwm pins
  pinMode(en1, OUTPUT);
  pinMode(en2, OUTPUT);

  // Start serial communication
  Serial.begin(57600);
  
  error = ps2x.config_gamepad(13,12,10,11, true, true);
  //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
 
  // Check for error
  if(error == 0)
  {
  Serial.println("Found Controller, configured successful");
  }
  else if(error == 1){
  Serial.println("No controller found, check wiring or reset the Arduino");
  }
  else if(error == 2){
  Serial.println("Controller found but not accepting commands");
  }
  else if(error == 3){
  Serial.println("Controller refusing to enter Pressures mode, may not support it.");
  }
  // Check for the type of controller
  type = ps2x.readType();
  switch(type) {
  case 0:
    Serial.println("Unknown Controller type");
    break;
  case 1:
    Serial.println("DualShock Controller Found");
    break;
  case 2:
    Serial.println("GuitarHero Controller Found");
    break;
  }
}


// Main loop
void loop(){
 if(error == 1) //skip loop if no controller found
  return; 
  
 else { 
    start:
    ps2x.read_gamepad(false, vibrate); 
     
     if(ps2x.Button(PSB_PAD_UP))
     {
       analogWrite(en1,200);
       analogWrite(en2,200);
       digitalWrite(m1a, HIGH);
       digitalWrite(m1b, LOW);
       digitalWrite(m2a, HIGH);
       digitalWrite(m2b, LOW);
       Serial.println("Move forward");
      }
      // TURN RIGHT
      if(ps2x.Button(PSB_PAD_RIGHT))
      {
         analogWrite(en1,150);
         analogWrite(en2,150);
         digitalWrite(m1a, HIGH);
         digitalWrite(m1b, LOW);
         digitalWrite(m2a, LOW);
         digitalWrite(m2b, HIGH);
         Serial.println("Turn right");
      }
      // TURN LEFT
      if(ps2x.Button(PSB_PAD_LEFT))
      {
        analogWrite(en1,150);
        analogWrite(en2,150);
        digitalWrite(m1a, LOW);
        digitalWrite(m1b, HIGH);
        digitalWrite(m2a, HIGH);
        digitalWrite(m2b, LOW);
        Serial.println("Turn left");
      }
      // MOVE BACK
      if(ps2x.Button(PSB_PAD_DOWN))
      {
         analogWrite(en1,200);
         analogWrite(en2,200);
         digitalWrite(m1a, LOW);
         digitalWrite(m1b, HIGH);
         digitalWrite(m2a, LOW);
         digitalWrite(m2b, HIGH);
         Serial.println("Move back");
      } 
      if(ps2x.Button(PSB_R1))
      {
         analogWrite(en1,70);
         analogWrite(en2,200);
         digitalWrite(m1a, HIGH);
         digitalWrite(m1b, LOW);
         digitalWrite(m2a, HIGH);
         digitalWrite(m2b, LOW);   
         Serial.println("Move Uturn");
      }
       if(ps2x.Button(PSB_L1))
       {
       analogWrite(en1,250);
       analogWrite(en2,80);
       digitalWrite(m1a, HIGH);
       digitalWrite(m1b, LOW);
       digitalWrite(m2a, HIGH);
       digitalWrite(m2b, LOW);  
       Serial.println("Move Lturn");
      }  
    
     
      if (!ps2x.Button(PSB_PAD_DOWN) && !ps2x.Button(PSB_PAD_UP) && !ps2x.Button(PSB_PAD_RIGHT) && !ps2x.Button(PSB_PAD_LEFT) && !ps2x.Button(PSB_L1) && !ps2x.Button(PSB_R1)) 
      {
        analogWrite(en1,0);
        analogWrite(en2,0);
      }

       delay(50);
 
 }
}
