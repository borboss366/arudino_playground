/*
* Moisture Sensor - DFRobot Capacitive Soil Moisture Sensor v1.0
* Light Sensor - Analog Ambient Light Sensor v2.1
* Relay - Gravity Realy Module v4.0
*/

int MOISTURE_SENSOR_PIN = A1;
int LIGHT_SENSOR_PIN = A0;
int PUMP_PIN = 12;

int MOISTURE_SENSOR_AIR_VALUE = 510;
int MOISTURE_SENSOR_WATER_VALUE = 242;  // Filled up to the line

int TURN_PUMP_FOR_SEC = 2;

float calcHumidity(int moistureSensorValue) {
  return (float)(moistureSensorValue - MOISTURE_SENSOR_AIR_VALUE) / (float)(MOISTURE_SENSOR_WATER_VALUE - MOISTURE_SENSOR_AIR_VALUE);
}

void turnPumpFor(int ms) {
  digitalWrite(PUMP_PIN, HIGH);
  Serial.println("Pump is on");
  delay(ms);
  digitalWrite(PUMP_PIN, LOW);
  Serial.println("Pump is off");
}

void setup() {
  Serial.begin(9600);
  pinMode(PUMP_PIN, OUTPUT);
  Serial.print("Type 'w' to turn on pump on pin ");
  Serial.print(PUMP_PIN);
  Serial.print(" for ");
  Serial.print(TURN_PUMP_FOR_SEC);
  Serial.println(" seconds");
}

void loop() {
  int lightSensorValue = analogRead(LIGHT_SENSOR_PIN);
  int moistureSensorValue = analogRead(MOISTURE_SENSOR_PIN);
  float humidity = calcHumidity(moistureSensorValue);
  Serial.print("Light Sensor Value:");
  Serial.println(lightSensorValue);
  Serial.print("Moisture Sensor Value:");
  Serial.println(moistureSensorValue);
  Serial.print("Humidity: ");
  Serial.println(humidity);
  if (Serial.available()) {
    int state = Serial.read();
    if (state == 'w') {
      turnPumpFor(TURN_PUMP_FOR_SEC * 1000);
    }
  }
  delay(1000);
}
