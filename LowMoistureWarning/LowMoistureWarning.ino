/*
* SEN0308 MoistureSensor
*/

int WARNING_PIN = LED_BUILTIN; // Pin to trigger on/off depending on humidity
int SENSOR_PIN = A1;

int SENSOR_AIR_VALUE = 571;
int SENSOR_WATER_VALUE = 129;  // At 100mm - "recommended" depth

float HUMIDITY_THRESHOLD = 0.5;

float calcHumidity(int sensorValue) {
  return (float)(sensorValue - SENSOR_AIR_VALUE) / (float)(SENSOR_WATER_VALUE - SENSOR_AIR_VALUE);
}

void setup() {
  Serial.begin(9600);
  pinMode(WARNING_PIN, OUTPUT);
}

void loop() {
  int sensorValue = analogRead(SENSOR_PIN);
  float humidity = calcHumidity(sensorValue);
  Serial.print("Moisture Sensor Value:");
  Serial.println(sensorValue);
  Serial.print("Humidity: ");
  Serial.println(humidity);
  if (humidity < HUMIDITY_THRESHOLD) {
    digitalWrite(WARNING_PIN, HIGH);
  } else {
    digitalWrite(WARNING_PIN, LOW);
  }
  delay(1000);
}
