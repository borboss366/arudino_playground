#include <dht11.h>
#include <DFRobot_MAX31855.h>

// Humidity and temperature
DFRobot_MAX31855 max31855;
dht11 DHT;
int DHT11_PIN = 4;

int loadDHT() {
  return DHT.read(DHT11_PIN);  
}

int getHumidity() {
  return DHT.humidity;
}

int getTemperature() {
  return DHT.temperature;
}

void printDHT() {
  int check = loadDHT();

  switch (check){
    case DHTLIB_OK:
      Serial.print("Humidity: ");
      Serial.println(DHT.humidity, 1);
      Serial.print("Temperature: ");
      Serial.println(DHT.temperature,1);
      break;
    case DHTLIB_ERROR_CHECKSUM:
      Serial.print("DHT Checksum error,\t");
      break;
    case DHTLIB_ERROR_TIMEOUT:
      Serial.print("DHT Time out error,\t");
      break;
    default:
      Serial.print("DHT Unknown error,\t");
      break;
  }  
}
// End of humidity and temperature

// Moisture sensor
const int AIR_VALUE = 589; // changes with humidity
const int WATER_VALUE = 111;
const int MOISTURE_DRY_LEVEL_HIGH_PERCENT = 60;
const int MOISTURE_DRY_LEVEL_CRITICAL_PERCENT = 80;
const int LOOPS = 3;
const int LOOP_DELAY = 500;

const int MOISTURE_SENSOR_PIN = A0;



int measures[LOOPS];
int loopI = 0;
int moisture = 0;


void updateMoisture() {
  int v = analogRead(MOISTURE_SENSOR_PIN);
  measures[loopI] = v;
  loopI++;
  delay(LOOP_DELAY);

  if (loopI == LOOPS) {
    loopI = 0;
    moisture = calculatePercentage();
  }
}

/**
 * 0% - In water
 * 100%  - In air(dry)
 */
int calculatePercentage() {
  int measure = average(measures, LOOPS);
  int perc = (int)((float(measure - WATER_VALUE) / (AIR_VALUE - WATER_VALUE)) * 100);
  if (perc > 100) {
    perc = 100;
  }

  return perc;
}

int average(int * array, int len) {
  long sum = 0L;
  for (int i = 0 ; i < len ; i++) {
    sum += array[i];
  }
  return (int)(((float) sum) / len);
}

void printMoisture() {
  Serial.print("Moisture: ");
  Serial.println(moisture);
}
// End of moisture sensor

void setup(){
  Serial.begin(9600);
}

void loop(){
  updateMoisture();
  printMoisture();
  printDHT();
  delay(2000);
}
