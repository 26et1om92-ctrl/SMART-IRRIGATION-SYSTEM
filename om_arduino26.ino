#define SOIL_PIN 34
#define RELAY_PIN 26

// Adjust these values after calibration
int dryValue = 3000;
int wetValue = 1200;

// Moisture threshold
int moistureThreshold = 40;

// Most common relay modules are Active LOW
#define RELAY_ON LOW
#define RELAY_OFF HIGH

void setup()
{
  Serial.begin(115200);

  pinMode(SOIL_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);

  digitalWrite(RELAY_PIN, RELAY_OFF);

  Serial.println("Smart Irrigation System Started");
}

void loop()
{
  int sensorValue = analogRead(SOIL_PIN);

  // Convert sensor reading into moisture percentage
  int moisturePercent = map(
    sensorValue,
    dryValue,
    wetValue,
    0,
    100
  );

  moisturePercent = constrain(moisturePercent, 0, 100);

  Serial.print("Raw Sensor Value: ");
  Serial.println(sensorValue);

  Serial.print("Soil Moisture: ");
  Serial.print(moisturePercent);
  Serial.println("%");

  // Check soil moisture
  if (moisturePercent < moistureThreshold)
  {
    digitalWrite(RELAY_PIN, RELAY_ON);
    Serial.println("Soil is Dry - Pump ON");
  }
  else
  {
    digitalWrite(RELAY_PIN, RELAY_OFF);
    Serial.println("Soil is Wet - Pump OFF");
  }

  Serial.println("----------------------");

  delay(1000);
}