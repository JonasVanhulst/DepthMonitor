
/******************************************
 * Company : PXL
 *
 * Date: 20/03/2024
 * Authors : Jasper Maes & Jonas Vanhulst
 *
 * License: MIT LICENSE
 ******************************************/

// General includes
#include <Wire.h>

// Arduino includes
#include <Arduino_HTS221.h>   // Temp & humidity sensor
#include <Arduino_LPS22HB.h>  // Barometer sensor
#include <Arduino_LSM9DS1.h>  // IMU sensor
#include <Arduino_APDS9960.h> // Proximity sensor

// Adafruit includes
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128     // OLED Screen width
#define SCREEN_HEIGHT 64     // OLED Screen height
#define TANK_WIDTH 80        // Tank width for fitting on the screen
#define OLED_RESET -1        // Reset number for display
#define SCREEN_ADDRESS 0x3C  // Display I2C address
#define MAX_HEIGHT_PIXELS 48 // Definieer de maximale hoogte van de waterton in pixels

#define IR_SENSOR A7           // Analog infrared sensor
#define ULTRASONIC A1          // Analog ultrasonic sensor
#define RANGE_FINDER A0        // Analog range finder sensor
#define BUTTON_SELECT_IR D12    // Select button for the infrared
#define BUTTON_SELECT_RANGE D8 // Select button for the range finder sensor

// imu variables
int r, g, b;                                  // color detection
float gyroX, gyroY, gyroZ;                    // Gyroscope variables
float accelX, accelY, accelZ;                 // Accelero variables
float magX, magY, magZ, ledvalue;             // magnitude variables
int degreesX, degreesY = 0;                   // Accelero degrees
int plusThreshold = 30, minusThreshold = -30; // threshold values


// Start with 0 liters
int currentLiters = 0;
int lastGesture = -1;
const float tank_depth = 1.0;
const float max_volume = 100.0;
const float max_sensor_value = 1023.0; // Analog ultrasonic sensor max value
const float ofset = 0.2; //in meters

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup()
{
    // initialize with the I2C addr 0x3C (for the 128x64)
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }

  // Security to check for failure on the temperature sensor.
  if (!HTS.begin())
  {
    Serial.println("Failed to initialize humidity & temperature sensor!");
    for (;;)
      ;
  }

  // Security to check for failure on the pressure sensor.
  if (!BARO.begin())
  {
    Serial.println("Failed to initialize pressure sensor!");
    for (;;)
      ;
  }

  // Security to check for failure on the imu sensor.
  if (!IMU.begin())
  {
    Serial.println("Failed to initialize IMU!");
    for (;;)
      ;
  }
  // Security to check for failure on the proximity sensor.
  if (!APDS.begin())
  {
    Serial.println("Error initializing APDS-9960 sensor!");
  }
  APDS.setGestureSensitivity(90);
  // Getting the sample rate from the accelero meter
  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println("Hz");

  // Clear the buffer
  display.clearDisplay();

  // Display on OLED
  display.display();

  // Update water level
  updateWaterLevel(currentLiters);
}

void loop()
{
  // proximity value
  int proximity, gesture;
  // Set text size and color
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

/**
   * Checking on the on board sensor if they are available
   */
  if (APDS.gestureAvailable())
  {
    
    gesture = APDS.readGesture();
  }
  if (IMU.accelerationAvailable())
  {
    IMU.readAcceleration(accelX, accelY, accelZ);
  }
  if ((IMU.gyroscopeAvailable()))
  {
    IMU.readGyroscope(gyroX, gyroY, gyroZ);
  }
  if ((IMU.magneticFieldAvailable()))
  {
    IMU.readMagneticField(magX, magY, magZ);
  }
  if (APDS.proximityAvailable())
  {
    // - 0   => close, - 255 => far, -1  => error
    proximity = APDS.readProximity();
  }

  if (APDS.colorAvailable())
  {
    APDS.readColor(r, g, b);
  }

  // Reading button states
  bool button_state_ir = digitalRead(BUTTON_SELECT_IR);
  bool button_state_range = digitalRead(BUTTON_SELECT_RANGE);

  // Reading HTS sensor (temp & humidity)
  float temperature = HTS.readTemperature();
  float humidity = HTS.readHumidity();
  float IR_Converted;

  // Reading the barometer
  float pressure = BARO.readPressure();


  // Reading infrared sensor & converting values
  float IR_Value = analogRead(IR_SENSOR);
  float IR_distance =  (IR_Value / 120) * 0.3; // max = 30 cm
  IR_Converted = ( (tank_depth - IR_distance) / tank_depth ) * max_volume;
  Serial.print("IR: ");
  Serial.print(IR_distance);
  Serial.println(" meters");


  float ultrasonic_value = analogRead(ULTRASONIC);
  float Ultrasonic_Distance =  (ultrasonic_value / max_sensor_value) * 6;
  float Ultrasonic_Converted = (  (tank_depth - Ultrasonic_Distance) / tank_depth ) * max_volume;//(tank_depth - (ultrasonic_value / max_sensor_value)) * max_volume;
  Serial.print("Ultrasonic: ");
  Serial.print(Ultrasonic_Distance);
  Serial.println(" meters");


  // Reading the range finder & converting the values
  float range_value = analogRead(RANGE_FINDER);
  float distance_range_finder = ((range_value / 512) * 6.45); //(tank_depth - ((tank_depth - (range_value * tank_depth / max_sensor_value)) / tank_depth)) * max_volume;
  float range_finder_converted = ((tank_depth - distance_range_finder )/ tank_depth) * max_volume;
  Serial.print("Range finder: ");
  Serial.print(distance_range_finder);
  Serial.println(" meters");

  int newLiters;
  if (button_state_ir)
  {
    // Show ir value on display
    display.setCursor(0, 0);
    display.clearDisplay();
    Serial.println("+++ IR SELECTED +++");
    display.println("Water Tank Infrared");
    newLiters = IR_Converted;//IR_Converted;
  }
  else if (button_state_range)
  {
    // Show range on display
    display.setCursor(0, 0);
    display.clearDisplay();
    Serial.println("+++ RANGE SELECTED +++");
    display.println("Water Tank Range finder");
    newLiters = range_finder_converted;
  }
  else
  {
    // Default is the ultrasonic showed on the display
    display.setCursor(0, 0);
    display.clearDisplay();
    Serial.println("+++ ULTRASONIC SELECTED +++");
    display.println("Water Tank Ultrasonic");
    newLiters = Ultrasonic_Converted;
  }

  // // Display "Water Tank" text
  // display.setCursor(0, 0);
  // display.println("Water Tank");

  // Update water level only if it has changed
  if (newLiters != currentLiters)
  {
    currentLiters = newLiters;
    drawWaterTank(currentLiters);
    updateWaterLevel(currentLiters);
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
  Serial.print("GESTURE: ");
  Serial.println(gesture);
  
  if (APDS.gestureAvailable()) {
    // Lees de nieuwe gesture en sla deze op in lastGesture
    lastGesture = APDS.readGesture();
  }

  switch (lastGesture)
  {
  case GESTURE_UP:
    Serial.println("\r\n\r\n\r\n\r\n\r\n\r\n\r\n---------------------------");
    Serial.println("Wheater mode:");
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" °c\r\n");
    Serial.print("humidity: ");
    Serial.print(humidity);
    Serial.print(" %\r\n");
    Serial.print("Pressure: ");
    Serial.print(pressure);
    Serial.print(" hpa\r\n");
    Serial.println("---------------------------");
    break;

  case GESTURE_DOWN:
    Serial.println("\r\n\r\n\r\n\r\n\r\n\r\n\r\n---------------------------");
    Serial.println("RGB detection mode:");
    Serial.print("r = ");
    Serial.println(r);
    Serial.print("g = ");
    Serial.println(g);
    Serial.print("b = ");
    Serial.println(b);
    Serial.println("---------------------------");
    break;

  case GESTURE_LEFT:
    Serial.println("\r\n\r\n\r\n\r\n\r\n\r\n\r\n---------------------------");
    Serial.println("Tilt detection mode:");
    /* Checking the accerlero data to print the degrees at every board state.*/
    if (accelX > 0.1)
    {
      accelX = 100 * accelX;
      degreesX = map(accelX, 0, 97, 0, 90);
      Serial.print("Tilting up ");
      Serial.print(degreesX);
      Serial.print(" degrees\r\n");
    }

    if (accelX < -0.1)
    {
      accelX = 100 * accelX;
      degreesX = map(accelX, 0, -100, 0, 90);
      Serial.print("Tilting down ");
      Serial.print(degreesX);
      Serial.print(" degrees\r\n");
    }

    if (accelY > 0.1)
    {
      accelY = 100 * accelY;
      degreesY = map(accelY, 0, 97, 0, 90);
      Serial.print("Tilting left ");
      Serial.print(degreesY);
      Serial.print(" degrees\r\n");
    }

    if (accelY < -0.1)
    {
      accelY = 100 * accelY;
      degreesY = map(accelY, 0, -100, 0, 90);
      Serial.print("Tilting right ");
      Serial.print(degreesY);
      Serial.print(" degrees\r\n");
    }
    Serial.println("---------------------------");
    break;

  case GESTURE_RIGHT:
    Serial.println("\r\n\r\n\r\n\r\n\r\n\r\n\r\n---------------------------");
    Serial.println("Collision mode:");
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
    Serial.println("---------------------------");
    break;

  default:
    // ignore
    break;
  }
  



  delay(1000); // Wait for 1 second before checking again
}

// Function to update the water level on the display
void updateWaterLevel(int liters)
{
  // Clear the area where the water level will be displayed
  display.fillRect(TANK_WIDTH, 20, SCREEN_WIDTH - TANK_WIDTH, MAX_HEIGHT_PIXELS, SSD1306_BLACK);

  // Calculate the height of the water level based on the liters
  int waterHeight = map(liters, 0, 100, 0, MAX_HEIGHT_PIXELS);

  // Draw the water level
  display.fillRect(TANK_WIDTH, 20 + (MAX_HEIGHT_PIXELS - waterHeight), SCREEN_WIDTH - TANK_WIDTH, waterHeight, SSD1306_WHITE);

  // Display on OLED
  display.display();
}

// Function to draw the water tank
void drawWaterTank(int liters)
{
  // Draw tank outline
  display.drawRect(5, 20, 60, 60, SSD1306_WHITE);

  // Clear previous liter value
  display.fillRect(22, 37, 35, 16, SSD1306_BLACK);

  // Draw tank details
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(22, 37);
  String volume = String(liters);
  display.print(volume);
  display.print("l");
}
