#include <Arduino_LSM6DS3.h>
#include <CheapStepper.h>

CheapStepper stepper (14,15,16,17); 
boolean moveClockwise = true;

void setup() {
 stepper.setRpm(10);
 Serial.begin(9600);
  while (!Serial);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");

    while (1);
  }

  Serial.print("Gyroscope sample rate = ");
  Serial.print(IMU.gyroscopeSampleRate());
  Serial.println(" Hz");
  Serial.println();
  Serial.println("Gyroscope in degrees/second");
  Serial.println("X\tY\tZ");
  float x, y, z;

  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(x, y, z);

    Serial.print(x);
    Serial.print('\t');
    Serial.print(y);
    Serial.print('\t');
    Serial.println(z);
  }
}

void loop() {
moveClockwise = false;
stepper.moveDegrees (moveClockwise, 90);
int stepsLeft = stepper.getStepsLeft();

}
