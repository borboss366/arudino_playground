#include <dht11.h>
#include <DFRobot_MAX31855.h>

// Humidity and temperature
DFRobot_MAX31855 max31855;
dht11 DHT;
int DHT11_PIN = 4;
// End of humidity and temperature

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

void setup(){
  Serial.begin(9600);
}

void loop(){
  printDHT();
  delay(2000);
}
