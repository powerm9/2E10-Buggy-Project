#include <WiFiNINA.h>
#include <Arduino_LSM6DS3.h>
#include <CheapStepper.h>
#include <Servo.h>
#include <Encoder.h>

Encoder myEnc(15, 21);
CheapStepper stepper (2,3,4,7);  
bool moveClockwise = true;
Servo myservo;
int pos = 0;

char ssid[] = "PHONE";
char pass[] = "laptop123";
int status = WL_IDLE_STATUS;
WiFiServer server(5204);
WiFiServer serverspeed(5203);

void leftM(int direc, int vel);
void rightM(int direc, int vel);

unsigned long startMillis;
unsigned long currentMillis;
const unsigned long period = 1000;
double speedstart = 0;
double newPosition = 0;
double oldPosition = -999;
double distancePerStep = 1.25;

//Peters
// const int Right1 = 10;
// const int Right2 = 9;
// const int Left1 = 5;
// const int Left2 = 6;

//Matthews
const int Right1 = 9;
const int Right2 = 5;
const int Left1 = 16;
const int Left2 = 17;




const int RightSpeed = 11;
const int LeftSpeed = 12;

int RightIR = 2;
int LeftIR = 3;

char c = 'W';
String prev_c = "waiting";
String buffer = "waiting";

int click = 0;
int serialTimer = 0;




void setup() {
  WifiAndPinoutSetup();
  //Interrupts for IR sensors e.g attachInterrupt(digitalPinToInterrupt(pin), function, trigger)
  //The arduino nano 33 iot needs specific pins for this to work. Google interrupt pins
 myservo.attach(16);
 stepper.setRpm(12);
 stepper.newMoveTo(moveClockwise, 2048);
}



void loop() {

  if (millis() - startMillis >= period){
    int difference = newPosition - speedstart;
    serverspeed.write(difference * distancePerStep);      
  }  

  newPosition = myEnc.read();
  if(newPosition != oldPosition){
    oldPosition = newPosition;
  }
  
  stepper.run();

  Serial.println(c);

  interrupts();

  WiFiClient clientspeed = serverspeed.available();
  if(clientspeed.connected()) {
    c = clientspeed.read();
  }

  WiFiClient client = server.available();
  if (client.connected()){
      Serial.println("Phone command received:");
      client.write("Recieved");
      c = client.read();
  }


  if (c == 'G') {
    rightM(2,255);
    leftM(2,255);
  }

  if (c == 'S') {
   leftM(0,0);
   rightM(0,0);
  }
 
  if (c == 'R') {
   rightM(2,60);
   leftM(2, 255);
  }

  if (c == 'L'){
    rightM(2, 255);
    leftM(2, 60);
  }

  if (c == 'F') {
    Honk();    
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

void LeftTurn() {
    rightM(2,60);
    leftM(2,220);
}
void RightTurn() {
    rightM(2,220);
    leftM(2,60);
}

void Honk() {
  digitalWrite(4, HIGH);
  delay(500);
  digitalWrite(4, LOW);  
  }
