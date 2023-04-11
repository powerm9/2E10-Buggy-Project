#include <Arduino_LSM6DS3.h>
#include <CheapStepper.h>
#include <Servo.h>

CheapStepper stepper (14,15,17,18);  
bool moveClockwise = true;
bool servoChange=true;
unsigned long moveStartTime = 0;

Servo myservo;
int pos = 0;
unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
const unsigned long period = 3000;

void setup() {
  startMillis = millis();
  myservo.attach(16);
 stepper.setRpm(12);
 stepper.newMoveTo(moveClockwise, 2048);
 Serial.begin(9600);


  // if (!IMU.begin()) {
  //   Serial.println("Failed to initialize IMU!");
  //   while (1);
  // }

  // Serial.print("Gyroscope sample rate = ");
  // Serial.print(IMU.gyroscopeSampleRate());
  // Serial.println(" Hz");
  // Serial.println();
  // Serial.println("Gyroscope in degrees/second");
  // Serial.println("X\tY\tZ");
  // float x, y, z;

  // if (IMU.gyroscopeAvailable()) {
  //   IMU.readGyroscope(x, y, z);

  //   Serial.print(x);
  //   Serial.print('\t');
  //   Serial.print(y);
  //   Serial.print('\t');
  //   Serial.println(z);
  // }
  
}

void loop() {
  currentMillis = millis();
  if (currentMillis - startMillis >= period) {
    Serial.println(servoChange);
     servoChange=!servoChange;
    if (servoChange==true){
  myservo.write(45);  
    
    }else if(servoChange==false){
      myservo.write(10); 
      
    }


   
    startMillis = currentMillis;
  
  }
  
  stepper.run();

int stepsLeft = stepper.getStepsLeft();
if (stepsLeft == 0){
  moveClockwise = !moveClockwise;
  stepper.newMoveDegrees (moveClockwise, 180);
}

}
