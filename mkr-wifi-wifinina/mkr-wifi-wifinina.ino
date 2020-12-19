#include <Wire.h>
#include <WireUtility.h>
#include <WiFiNINA.h>

int status = WL_IDLE_STATUS;
char ssid[] = "111xxx-h368R";       
char pass[] = "xxxx";  

// Temperature
#define MAX31855_Addr (0x10)
unsigned char rxbuf[4] = {0};

void setup() {
  
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial);

  // Loading I2C
  Wire.begin();

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to network: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }

  // you're connected now, so print out the data:
  Serial.println("You're connected to the network");

  Serial.println("----------------------------------------");
  printData();
  Serial.println("----------------------------------------");
}

void loop() {
  printTemperature();
  delay(3000);
}

void printTemperature() {
  float temp = readCelsius();
  Serial.print("Temperature:");
  Serial.print(temp);
  Serial.println(" ℃");
}

void printData() {
  Serial.println("Board Information:");
  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  Serial.println();
  Serial.println("Network Information:");
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.println(rssi);
}

void readData(int Reg, int Num) {
  unsigned char i = 0;
  Wire.beginTransmission(MAX31855_Addr);
  Wire.write(Reg); 
  Wire.endTransmission();
  Wire.requestFrom(MAX31855_Addr, Num);
  while (Wire.available()){
    rxbuf[i] = Wire.read();
    i++;
  }
}

float readCelsius(){
  readData(0x00 ,4);
  if(rxbuf[3]&0x7){
    return NAN;
  }
  if(rxbuf[0]&0x80){
    rxbuf[0] = 0xff - rxbuf[0];
    rxbuf[1] = 0xff - rxbuf[1];
    float temp =  -((((rxbuf[0] << 8)|(rxbuf[1] & 0xfc)) >> 2) + 1) * 0.25;
    return temp;
  }
  float temp =(((rxbuf[0] << 8 )| (rxbuf[1] & 0xfc)) >> 2)*0.25;
  return temp;
}
