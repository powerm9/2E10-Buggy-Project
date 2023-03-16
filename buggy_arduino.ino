// get wifinina and ultrasonic sensor libraries. (Remember to download them in library manager)
#include <WiFiNINA.h>
#include <afstandssensor.h>
//set pins for ULsensors AfstandsSensor(triggerPin, echoPin);
AfstandsSensor afstandssensor(14, 15);

//Wifi setup. Enter password and ssid
char ssid[] = "crapphone";
char pass[] = "laptop123";
int status = WL_IDLE_STATUS;
WiFiServer server(80);
//Pinouts and interrupts
void leftM(int direc, int vel);
void rightM(int direc, int vel);
//These connect to the IN pins on the H-bridge
const int Right1 = 16;
const int Right2 = 17;
const int Left1 = 5;
const int Left2 = 9;
//PWN pins to control speed of each motor
const int RightSpeed = 11;
const int LeftSpeed = 12;
//Interrupt pins for IR sensors
int RightIR = 2;
int LeftIR = 3;
//Create a string that recieves messages from Processing
String c="waiting";
int distance=0;
bool disState=false;

void setup() {
  WifiAndPinoutSetup();
  //Interrupts for IR sensors e.g attachInterrupt(digitalPinToInterrupt(pin), function, trigger)
  //The arduino nano 33 iot needs specific pins for this to work. Google interrupt pins
  attachInterrupt(digitalPinToInterrupt(RightIR), LeftTurn, LOW);
  attachInterrupt(digitalPinToInterrupt(LeftIR), RightTurn, LOW);
}

void loop() {
  //T
  interrupts();

delay(250);
Serial.println(c);

distance=afstandssensor.afstandCM();
//noInterrupts();
Serial.println(distance);
//Start processing as a client. If its connected send Processing "Hello world". Read a string from Processing
WiFiClient client =server.available();
  if (client.connected()){
  Serial.println("connected");
  client.write("hello world");
  c = client.readString();
  }
  //If the string is "go" then check if the distance is under 20cm of the Usonic sensor.
  //If so turn both motors off else run forward
  if (c=="go"){
    interrupts();
      if (distance<=15){
      rightM(0,0);
      leftM(0,0);
       
        server.write(distance);
       
      }else{
      rightM(2,150);
      leftM(2,150);
      }
   }else if(c=="stop"){
    //If Processing sends "stop" stop both motors. noInterrupts is used so that the IR sensors dont move the buggy
    
    leftM(0,0);
    rightM(0,0);
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
//Function to control left motor. E.g leftM(direction 0 or 1 or 2, Speed 0-255);
//0 for stop, 1 for reverse, 2 for forward
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
void rightM(int direc, int vel){
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
// Turns left for a brief time when the interrupt is called
void LeftTurn(){
    rightM(2,60);
    leftM(2,220);
}
void RightTurn(){
    rightM(2,220);
    leftM(2,60);
}
