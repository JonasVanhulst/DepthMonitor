/******************************************
 * Company : PXL
 *
 * Date: 20/03/2024
 * Authors : Jasper Maes & Jonas Vanhulst
 *
 * License: MIT LICENSE
 ******************************************/
#include <stdio.h>
#include <Arduino_HTS221.h>
#include <Arduino_LPS22HB.h>
#include <Arduino_LSM9DS1.h>

/*
 * TODO
 *
 * Proximity Detection
 * Color Detection ?
 * Gesture Recognition
 * Edge Impulse
 */

/* Sensor connection pins */
int ULTRASONIC = A1;
int INFRARED_1 = A2;
int INFRARED_2 = A3;

/* Global variables */
int ultrasonic_value = 0;
int infrared_1_value = 0;
int infrared_2_value = 0;

void setup()
{
  // Starting the serial at a 9600 baundwidth.
  Serial.begin(9600);
  while (!Serial)
  {
  }

  // Security to check for failure on the temperature sensor.
  if (!HTS.begin())
  {
    Serial.println("Failed to initialize humidity temperature sensor!");
    while (1)
    {
    }
  }

  // Security to check for failure on the pressure sensor.
  if (!BARO.begin())
  {
    Serial.println("Failed to initialize pressure sensor!");
    while (1)
    {
    }
  }

  // Security to check for failure on the IMU sensor.
  if (!IMU.begin())
  {
    Serial.println("IMU init failed");
    while (1)
    {
    }
  }
}

void loop()
{

Serial.println("---------------------------");
  float temperature = HTS.readTemperature();
  float humidity = HTS.readHumidity();
  float pressure = BARO.readPressure();

  bool accelAvailable;
  float accelX, accelY, accelZ;
  int degreesX, degreesY = 0;
  if ((accelAvailable = IMU.accelerationAvailable()))
  {
    IMU.readAcceleration(accelX, accelY, accelZ);
  }

  bool gyroAvailable;
  float gyroX, gyroY, gyroZ;
  int plusThreshold = 30, minusThreshold = -30;
  if ((gyroAvailable = IMU.gyroscopeAvailable()))
  {
    IMU.readGyroscope(gyroX, gyroY, gyroZ);
  }

  bool magAvailable;
  float magX, magY, magZ, ledvalue;
  if ((magAvailable = IMU.magneticFieldAvailable()))
  {
    IMU.readMagneticField(magX, magY, magZ);
  }

  // Printing the temperature, humidity and pressure data.
  // Serial.print("%+7.2f°C %+7.2f%% %+7.2f hPa   ", temperature, humidity, pressure);
  Serial.print("Temperatur: ");
  Serial.print(temperature);
  Serial.print(" °c\r\n");
  Serial.print("humidity: ");
  Serial.print(humidity);
  Serial.print(" %\r\n");
  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.print(" hpa\r\n");

  /* Checking the accerlero data to print the degrees at every board state.*/
  if (accelX > 0.1)
  {
    accelX = 100 * accelX;
    degreesX = map(accelX, 0, 97, 0, 90);
    // Serial.print("Tilting up %+5.2f degrees", degreesX);
    Serial.print("Tilting up ");
    Serial.print(degreesX);
    Serial.print(" degrees\r\n");
  }

  if (accelX < -0.1)
  {
    accelX = 100 * accelX;
    degreesX = map(accelX, 0, -100, 0, 90);
    // Serial.print("Tilting down %+5.2f degrees", degreesX);
    Serial.print("Tilting down ");
    Serial.print(degreesX);
    Serial.print(" degrees\r\n");
  }

  if (accelY > 0.1)
  {
    accelY = 100 * accelY;
    degreesY = map(accelY, 0, 97, 0, 90);
    // Serial.print("Tilting left %+5.2f degrees", degreesY);
    Serial.print("Tilting left ");
    Serial.print(degreesY);
    Serial.print(" degrees\r\n");
  }

  if (accelY < -0.1)
  {
    accelY = 100 * accelY;
    degreesY = map(accelY, 0, -100, 0, 90);
    // Serial.print("Tilting right %+5.2f degrees", degreesY);
    Serial.print("Tilting right ");
    Serial.print(degreesY);
    Serial.print(" degrees\r\n");
  }

  /* Checking the gyroscope values to print the board state. */
  if (gyroY > plusThreshold)
  {
    Serial.println("Collision front");
  }
  if (gyroY > minusThreshold)
  {
    Serial.println("Collision back");
  }
  if (gyroX < minusThreshold)
  {
    Serial.println("Collision right");
  }
  if (gyroY > plusThreshold)
  {
    Serial.println("Collision left");
  }

  /* Checking the magnetic field data to assign its value to the ledvalue. */
  if (magX < 0)
  {
    ledvalue = -(magX);
  }
  else
  {
    ledvalue = magX;
  }

  // Writing the built in led with the magnetic field received value.
  analogWrite(LED_BUILTIN, ledvalue);

  // Reading the ultrasonic distance sensor.
  ultrasonic_value = analogRead(ULTRASONIC);

  // Reading the infrared sensors.
  infrared_1_value = analogRead(INFRARED_1);
  infrared_2_value = analogRead(INFRARED_2);
  Serial.println("---------------------------");
  // Wait one second to read all the sensor data again.
  delay(2000);
}