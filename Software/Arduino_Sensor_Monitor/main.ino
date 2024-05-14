/******************************************
 * Company : PXL
 *
 * Date: 20/03/2024
 * Authors : Jasper Maes & Jonas Vanhulst
 *
 * License: MIT LICENSE
 ******************************************/

#include <Wire.h>
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
#define BUTTON_SELECT_IR D2    // Select button for the infrared
#define BUTTON_SELECT_RANGE D3 // Select button for the range finder sensor

// Start with 0 liters
int currentLiters = 0;
const float tank_depth = 1.0;
const float max_volume = 100.0;
const float max_sensor_value = 1023.0; // Analog ultrasonic sensor max value

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

  // Clear the buffer
  display.clearDisplay();

  // Display on OLED
  display.display();

  // Update water level
  updateWaterLevel(currentLiters);
}

void loop()
{
  // Set text size and color
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // bool button_state_ir = digitalRead(BUTTON_SELECT_IR);
  // bool button_state_range = digitalRead(BUTTON_SELECT_RANGE);

  float IR_Value = analogRead(IR_SENSOR);
  float IR_Converterd;

  float ultrasonic_value = analogRead(ULTRASONIC);
  float Ultrasonic_Converted = (tank_depth - (ultrasonic_value / max_sensor_value)) * max_volume;

  float range_value = analogRead(RANGE_FINDER);
  float distance_range_finder = (tank_depth - ((tank_depth - (range_value * tank_depth / max_sensor_value)) / tank_depth)) * max_volume;
  Serial.println(distance_range_finder);

  /*
    int newLiters;
    if (button_state_ir) {
      // Show ir value on display
      display.setCursor(0, 0);
      display.println("Water Tank Infrared");
      newLiters = IR_Converted;
    } else if (button_state_range) {
      // Show range on display
      // Display "Water Tank" text
      display.setCursor(0, 0);
      display.println("Water Tank Range finder");
      newLiters = Range_Converted;
    } else {
      // Default is the ultrasonic showed on the display
      display.setCursor(0, 0);
      display.println("Water Tank Ultrasonic");
      newLiters = Ultrasonic_Converted;
    }
  */

  // Display "Water Tank" text
  display.setCursor(0, 0);
  display.println("Water Tank Range");

  // Update water level only if it has changed
  if (distance_range_finder != currentLiters)
  {
    currentLiters = distance_range_finder;
    drawWaterTank(currentLiters);
    updateWaterLevel(currentLiters);
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
