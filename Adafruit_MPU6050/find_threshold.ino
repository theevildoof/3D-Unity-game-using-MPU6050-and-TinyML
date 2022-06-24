// Basic demo for accelerometer readings from Adafruit MPU6050
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

// instantiates an object of the Adafruit_MPU6050 class
Adafruit_MPU6050 mpu;

void setup(void) {
Serial.begin(115200);

while (!Serial) {
delay(10); // will pause Zero, Leonardo, etc until serial console opens
}

// Try to initialize!
if (!mpu.begin()) {
Serial.println("Failed to find MPU6050 chip");
while (1) {
delay(10);
}
}

mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
mpu.setGyroRange(MPU6050_RANGE_250_DEG);
mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
Serial.println("");
delay(100);
}

void loop() {
/* Get new sensor events with the readings */
sensors_event_t a, g, temp;
mpu.getEvent(&a, &g, &temp);
/* Print out the values */
Serial.print("AccelX:");
Serial.print(a.acceleration.x);
Serial.print(",");
Serial.print("AccelY:");
Serial.print(a.acceleration.y);
Serial.print(",");
Serial.print("AccelZ:");
Serial.println(a.acceleration.z);
delay(10);
}
