#include <WiFiNINA.h>
#include <Arduino_LSM6DS3.h>
#include <CheapStepper.h>
#include <Servo.h>

CheapStepper stepper (14,15,17,18);  
bool moveClockwise = true;
Servo myservo;
int pos = 0;

char ssid[] = "PHONE";
char pass[] = "laptop123";
int status = WL_IDLE_STATUS;
WiFiServer server(5204);

void leftM(int direc, int vel);
void rightM(int direc, int vel);

const int Right1 = 10;
const int Right2 = 9;
const int Left1 = 5;
const int Left2 = 6;

const int RightSpeed = 11;
const int LeftSpeed = 12;

int RightIR = 2;
int LeftIR = 3;

String c = "waiting";
String prev_c = "waiting";
String buffer = "waiting";

int click = 0;
int reverseTimer = 1000;
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
 stepper.run();
  //  if (millis() - serialTimer >= 1000) { 
  //   Serial.println(c);
  //   serialTimer = millis();
  // }
  Serial.println(c);

  interrupts();

  WiFiClient client = server.available();

  if (client.connected()){
      Serial.println("Phone command received:");
      client.write("Recieved");
      c = client.readString();
  }

  // if (millis() - serialTimer >= 3000) {
  //   c = "stopAll";
  //   Serial.println(c);
  //   serialTimer = millis();
  // }

  if (c == "go") {
    rightM(2,255);
    leftM(2,255);
  }

  if (c == "stop") {
    leftM(0,0);
    rightM(0,0);
  }
 
    if (c == "right") {
    rightM(2,60);
    leftM(2, 255);
  }

  if(c == "left"){
    rightM(2, 255);
    leftM(2, 60);
  }

  if (c == "fire") {
  
  }
    if (c == "tleft") {
         	moveClockwise = false;
     int stepsLeft = stepper.getStepsLeft();
     if (stepsLeft == 0){
  stepper.newMoveDegrees (moveClockwise, 20);
     }
     c = "stopAll";
  }

  if(c == "tright"){
   	moveClockwise = true;
     int stepsLeft = stepper.getStepsLeft();
     if (stepsLeft == 0){
  stepper.newMoveDegrees (moveClockwise, 20);
     }
     c = "stopAll";
  }
  if (c == "up") {
    pos=pos+3;
    myservo.write(pos);
     c = "stopAll";
  }

  if(c == "down"){
  pos=pos-3;
    myservo.write(pos);
     c = "stopAll";
  }

  if(c == "stopAll"){
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
