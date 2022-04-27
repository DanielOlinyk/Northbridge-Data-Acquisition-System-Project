/*MPU6050 sensor with Arduino.
 * http://srituhobby.com
 */
 
//#include <LiquidCrystal_I2C.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

#include <Wire.h>
 
Adafruit_MPU6050 mpu;
//LiquidCrystal_I2C lcd(0x27, 16, 2);

#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 // attach pin D3 Arduino to pin Trig of HC-SR04

long duration; // variable for the duration of sound wave travel
int distance;  // variable for the distance measurement
 
void setup(void) {
  Serial.begin(9600);
  //lcd.init();
  //lcd.backlight();
  mpu.begin();
  mlx.begin();  
 
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  pinMode(trigPin, OUTPUT);                         // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT);                          // Sets the echoPin as an INPUT
  Serial.begin(9600);                               // // Serial Communication is starting with 9600 of baudrate speed
  
  //delay(100);
}
 
void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

      // put your main code here, to run repeatedly:
  float PinValue = analogRead(A0);
  float v = PinValue*5/1023; // Change value range from 0-1023 to range 0-5 volts.
 
  /* Print out the values */
 
    // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm ");

  // From datasheet, pressure-voltage relationship: v = 3*p+0.5
  // Link: https://media.digikey.com/pdf/Data%20Sheets/Seeed%20Technology/114991178_Web.pdf
  float p = (v-0.5)/3;
  Serial.print("Pressure: "); Serial.print(p); Serial.print(" Pa ");
  
  Serial.print("Acceleration X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);
  Serial.print(" m/s^2 ");
 
  //Serial.println(""); // C\t

  Serial.print("Ambient Temperature = "); Serial.print(mlx.readAmbientTempC()); 
  Serial.print("*C Object Temperature = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
  //Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempF()); 
  //Serial.print("*F\tObject = "); Serial.print(mlx.readObjectTempF()); Serial.println("*F");
  Serial.println();
  delay(500);
}
