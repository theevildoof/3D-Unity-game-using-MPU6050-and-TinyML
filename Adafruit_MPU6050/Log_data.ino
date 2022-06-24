#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;
int count =1;
float x_initial, y_initial, z_initial;
void setup() {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  //Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin(0x69)) {
    //Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  //Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  //Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    //Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    //Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    //Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
   // Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
 // Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
   // Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    //Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    //Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    //Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
   // Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
  //  Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    //Serial.println("5 Hz");
    break;
  }

 // Serial.println("");
  delay(100);
  calibrate_mpu();
  
}

void loop() {
  detect_motion();
  
}

void read_data(){
  
  for(int i =0;i<40;i++){
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
 
  Serial.print(a.acceleration.x );
  Serial.print(",");
  Serial.print(a.acceleration.y );
  Serial.print(",");
  Serial.println(a.acceleration.z);
  delay(10);
  }
  Serial.println("");
  Serial.println("--------");
  Serial.println(count);
  Serial.println("--------");
  count++;
}

void calibrate_mpu(){
  float totX, totY, totZ;
  sensors_event_t a, g, temp;
  
  
  for (int i = 0; i < 10; i++) {
    mpu.getEvent(&a, &g, &temp);
    totX = totX + a.acceleration.x;
    totY = totY + a.acceleration.y;
    totZ = totZ + a.acceleration.z;
  }
  x_initial = totX / 10;
  y_initial = totY / 10;
  z_initial = totZ / 10;
  Serial.println("Calibrated");
}

void detect_motion(){
   sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  if( abs(a.acceleration.x - x_initial) +abs(a.acceleration.y - y_initial) + abs(a.acceleration.z - z_initial) > 20){
    read_data();
  }
  else{
    delay(5);
  }
}
