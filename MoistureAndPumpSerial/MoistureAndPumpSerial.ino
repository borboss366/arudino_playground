/*
* Sensor - DFRobot Capacitive Soil Moisture Sensor v1.0
* Relay - Gravity Realy Module v4.0
*/

int SENSOR_PIN = A1;
int PUMP_PIN = 12;

int SENSOR_AIR_VALUE = 510;
int SENSOR_WATER_VALUE = 242;  // Filled up to the line

int TURN_PUMP_FOR_SEC = 2;

float calcHumidity(int sensorValue) {
  return (float)(sensorValue - SENSOR_AIR_VALUE) / (float)(SENSOR_WATER_VALUE - SENSOR_AIR_VALUE);
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
  int sensorValue = analogRead(SENSOR_PIN);
  float humidity = calcHumidity(sensorValue);
  Serial.print("Moisture Sensor Value:");
  Serial.println(sensorValue);
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
