#define IRSensorIn  A0

/*
* The GP2D12 Sensor is an analog sensor that needs a 5V supply.
* The collor code is:
* - white: Signal (Vout) out
* - RED: Vcc
* - Blue: GND
* 
* To find out about the conversion (raw value to distance), check the datasheet: https://engineering.purdue.edu/ME588/SpecSheets/sharp_gp2d12.pdf
*/

void setup() {
  Serial.begin(9600);
}

void loop() {
// Read the analog value from the IR sensor
  int sensorValue = analogRead(IRSensorIn);

  // Print the raw sensor value to the Serial Monitor
  Serial.print("Raw Sensor Value: ");
  Serial.println(sensorValue);
  
  delay(500);
}
