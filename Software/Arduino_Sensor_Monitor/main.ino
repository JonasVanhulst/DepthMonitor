/******************************************
 * Company : PXL
 *
 * Date: 20/03/2024
 * Authors : Jasper Maes & Jonas Vanhulst
 *
 * License: MIT LICENSE
 ******************************************/

#define DELAY 500
#define IR_SENSOR A0
#define ULTRASONIC A1
#define RANGE_FINDER A7
#define BUTTON_SELECT_IR D2
#define BUTTON_SELECT_RANGE D3

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    // bool button_state_ir = digitalRead(BUTTON_SELECT_IR);
    // bool button_state_range = digitalRead(BUTTON_SELECT_RANGE);

    float IR_Value = analogRead(IR_SENSOR);
    float ultrasonic_value = analogRead(ULTRASONIC);
    float range_value = analogRead(RANGE_FINDER);

    // IR_Value to distance in cm (float)

    // ultrasonic_Value to distance in cm (float)

    // range_Value to distance in cm (float)

    Serial.print("Raw IR Value: ");
    Serial.println(IR_Value);
    Serial.print("Raw Ultrasonic Value: ");
    Serial.println(ultrasonic_value);
    Serial.print("Raw Range Value: ");
    Serial.println(range_value);

    // Displaying the different sensors on the display

    /*
      if (button_state_ir) {
        // Show ir value on display
      } else if (button_state_range) {
        // Show range on display
      } else {
        // Default is the ultrasonic showed on the display
      }
    */
    delay(DELAY);
}
