#define GP2Y0D02_SENSOR 5
#define GP2D12_SENSOR A6
#define UB6000_SENSOR A1
#define MB1000_SENSOR A7
#define DFR0486_SENSOR SCL A5
#define DFR0486_SENSOR_SDA A4

void setup()
{
    pinMode(GP2Y0D02_SENSOR, INPUT_PULLUP);
    pinMode(GP2D12_SENSOR, INPUT_PULLUP);
    pinMode(UB6000_SENSOR, INPUT);
    pinMode(MB1000_SENSOR, INPUT);

    Serial.begin(9600);
}

void loop()
{
    int GP2Y0D02_val = digitalRead(GP2Y0D02_SENSOR);
    float GP2D12_val = analogRead(GP2D12_SENSOR);
    float UB6000_val = analogRead(UB6000_SENSOR);
    float MB1000_val = analogRead(MB1000_SENSOR);
    Serial.print("GP2Y0D02: ");
    Serial.println(GP2Y0D02_val);
    Serial.print("GP2D12: ");
    Serial.println(GP2D12_val);
    Serial.print("UB6000: ");
    Serail.println(UB6000_val);
    Serial.print("MB1000: ");
    Serial.println(MB1000_val);

    delay(500);
}