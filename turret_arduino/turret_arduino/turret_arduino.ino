#include <Arduino_LSM6DS3.h>
#include <CheapStepper.h>
#include <Servo.h>
#include <LCD_I2C.h>
#include <Encoder.h>

Encoder myEnc(21, 15);
unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
const unsigned long period = 1000;
double oldPosition = -999;
double speedstart = 0;
double newPosition = 0;
double distancePerStep = 1.25;
double prevInput;
int objectspeed=0;
String objectspeedshow="0";

LCD_I2C lcd(0x27, 16, 2);



void setup() {
 lcd.begin(); // If you are using more I2C devices using the Wire library use lcd.begin(false)
                 // this stop the library(LCD_I2C) from calling Wire.begin()
    lcd.backlight();
 Serial.begin(9600);
}
void loop()
{
  currentMillis = millis();

  if (currentMillis - startMillis >= period)
  {
    lcd.clear();
    lcd.setCursor(1,1);
    int difference = newPosition - speedstart;
    int objectspeed=difference * distancePerStep;
    startMillis = currentMillis;
    speedstart = newPosition;
    objectspeedshow = String(objectspeed);
    double proj=projDis(45);
    
    Serial.println(proj);
    
    lcd.setCursor(0, 0);
     lcd.print("Current speed: "+objectspeedshow); 
     lcd.setCursor(0, 2);
     lcd.print("Aim distace:"+String(proj)+"m"); 

  }

  newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
  }
   
  
}

double projDis(double angle){
  double U=5;
  float distanceTravelled;
  float time = (U*sin(angle*3.14/180))/(9.81);
  Serial.println(time);
  distanceTravelled=U*cos(angle*3.14/180)*time;  
  return distanceTravelled;
}

