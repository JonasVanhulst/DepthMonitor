#define DigitalSensorIn 2

/*
* The SHARP 2Y0D02 is a digital sensor that will give a 0 signal when nothing is detected withing the range of 80 cm
* When something is detected withing this range, the value will be 1.
* this can be used for 'overflow prevention'
* The sensor requires 5V, but in the tests that where done, 3.3 V also seems to work just fine
* 
* The collor code for the connections is:
*  - orange: GND
*  - RED: Vout (digital output pin)
*  - BROWN: Vin (connected to 5V/3,3V pin)
*/

void setup() {
  // Start serial communication
  Serial.begin(9600);
  // Set the digital pin as input
  pinMode(DigitalSensorIn, INPUT);
}

void loop() {
  // Read the digital value from the sensor
  int sensorValue = digitalRead(DigitalSensorIn);

  // Print the digital sensor value to the Serial Monitor
  Serial.print("Digital Sensor Value: ");
  Serial.println(sensorValue);

  // Delay for a short period to avoid flooding the Serial Monitor
  delay(500);
}
