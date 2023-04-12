#include <WiFiNINA.h>
#include <Arduino_LSM6DS3.h>
#include <CheapStepper.h>
#include <Servo.h>
#include <Encoder.h>
#include <LCD_I2C.h>
#include "GY521.h"

GY521 sensor(0x68);
uint32_t counter = 0;
LCD_I2C lcd(0x27, 16, 2);

Encoder myEnc(21, 15);
CheapStepper stepper (2,3,4,7);  
bool moveClockwise = true;
Servo myservo;
int pos = 0;

char ssid[] = "PHONE";
char pass[] = "laptop123";
int status = WL_IDLE_STATUS;
WiFiServer server(5204);


void leftM(int direc, int vel);
void rightM(int direc, int vel);

unsigned long startMillis;
unsigned long currentMillis;
const unsigned long period = 1000;
double speedstart = 0;
double newPosition = 0;
double oldPosition = -999;
double distancePerStep = 1.25;

String objectspeedshow="0";
int objectspeed=0;
double prevInput;

//Peters
const int Right1 = 10;
const int Right2 = 9;
const int Left1 = 5;
const int Left2 = 6;

//Matthews
// const int Right1 = 9;
// const int Right2 = 5;
// const int Left1 = 16;
// const int Left2 = 17;




const int RightSpeed = 11;
const int LeftSpeed = 12;

int RightIR = 2;
int LeftIR = 3;

char c = 'W';


int click = 0;
int serialTimer = 0;




void setup() {
  WifiAndPinoutSetup();
  startI2cAndFire();

 myservo.attach(16);
 stepper.setRpm(12);
 stepper.newMoveTo(moveClockwise, 2048);

}



void loop() {

  
  currentMillis = millis();

  if (currentMillis - startMillis >= period) {
    lcd.clear();
    lcd.setCursor(1,1);
    int difference = newPosition - speedstart;
    int objectspeed = difference * distancePerStep;
    startMillis = currentMillis;
    speedstart = newPosition;
    objectspeedshow = String(objectspeed);

    sensor.read();
    // serverspeed.write(objectspeed);
  float x = sensor.getAngleX();
    double proj=projDis(abs(x));
    
    Serial.println(proj);
    
    
    lcd.setCursor(0, 0);
     lcd.print("Current speed:"+objectspeedshow + "cm/s"); 
     lcd.setCursor(0, 2);
     lcd.print("Aim distace:"+String(proj)+"m"); 

  }

  newPosition = myEnc.read();
  if(newPosition != oldPosition){
    oldPosition = newPosition;
  }
  
  stepper.run();

  


  // WiFiClient clientspeed = serverspeed.available();
  // if(clientspeed.connected()) {
  //   c = clientspeed.read();
  // }

  WiFiClient client = server.available();
  if (client.connected()){
      Serial.println("Phone command received:");
      client.write("Recieved");
      c = client.read();
  }


  if (c == 'G') {
    rightM(2,155);
    leftM(2,155);
  }

  if (c == 'S') {
   leftM(0,0);
   rightM(0,0);
  }
 
  if (c == 'R') {
   rightM(2,100);
   leftM(2, 155);
  }

  if (c == 'L'){
    rightM(2, 155);
    leftM(2, 100);
  }

  if (c == 'F') {
      digitalWrite(8, HIGH);
      delay(1000);
      digitalWrite(8, LOW);
      c == 'X';
   }
   
  if (c == 'T') {
    moveClockwise = false;
    int stepsLeft = stepper.getStepsLeft();
    if (stepsLeft == 0){
    stepper.newMoveDegrees (moveClockwise, 30);
    delay(50);
    }
    c = 'X';
  }

  if(c == 'Y'){
   	moveClockwise = true;
     int stepsLeft = stepper.getStepsLeft();
     if (stepsLeft == 0){
     stepper.newMoveDegrees (moveClockwise, 30);
     delay(50);
     }
     c = 'X';
  }
  if (c == 'U') {
    pos=pos+3;
    myservo.write(pos);
     c = 'X';
  }

  if(c == 'D'){
  pos=pos-3;
    myservo.write(pos);
     c = 'X';
  }

  if(c == 'X'){
    rightM(0, 0);
    leftM(0, 0);
  }
}



void WifiAndPinoutSetup(){
  //initiaize serial and wifi
  Serial.begin(9600);
  while (status != WL_CONNECTED) {
     Serial.print("Attempting to connect to network: ");
     Serial.println(ssid);
     // Connect to WPA/WPA2 network:
     status = WiFi.begin(ssid, pass);
     // wait 3 seconds for connection:
     delay(3000);
  }
   //Gets ip address of the buggy
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  //Starts arduino as server
  server.begin();
  Serial.println(ip);
  pinMode(Right1, OUTPUT);
  pinMode(Right2, OUTPUT);
  pinMode(Left1, OUTPUT); 
  pinMode(Left2, OUTPUT);
  pinMode(RightSpeed, OUTPUT);
  pinMode(LeftSpeed, OUTPUT);
  
}

void leftM(int direc, int vel){
  analogWrite(RightSpeed, vel);
  switch(direc){
    case 0:
    digitalWrite(Right1, LOW);
    digitalWrite(Right2, LOW);
    break;
    case 1:
    digitalWrite(Right1, HIGH);
    digitalWrite(Right2, LOW);
    break;
    case 2:
    digitalWrite(Right1, LOW);
    digitalWrite(Right2, HIGH);
    break;
  }
}
void rightM(int direc, int vel) {
  analogWrite(LeftSpeed, vel);
  switch(direc){
    case 0:
    digitalWrite(Left1, LOW);
    digitalWrite(Left2, LOW);
    break;
    case 1:
    digitalWrite(Left1, HIGH);
    digitalWrite(Left2, LOW);
    break;
    case 2:
    digitalWrite(Left1, LOW);
    digitalWrite(Left2, HIGH);
    break;
  }
}

double projDis(double angle){
  double U=5;
  float distanceTravelled;
  float time = (U*sin(angle*3.14/180))/(9.81);
  Serial.println(time);
  distanceTravelled=U*cos(angle*3.14/180)*abs(time);  
  if (distanceTravelled<0){
    distanceTravelled=0;
  }
  return distanceTravelled+1;
}


void startI2cAndFire(){
 pinMode(8, OUTPUT);
  Wire.begin();
 lcd.begin(); // If you are using more I2C devices using the Wire library use lcd.begin(false)
                 // this stop the library(LCD_I2C) from calling Wire.begin()
    lcd.backlight();
   while (sensor.wakeup() == false)
  {
    Serial.print(millis());
    Serial.println("\tCould not connect to GY521");
    delay(1000);
  }
 sensor.setAccelSensitivity(2);  //  8g
  sensor.setGyroSensitivity(1);   //  500 degrees/s
   sensor.setThrottle();
}



