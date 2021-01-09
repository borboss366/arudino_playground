#include <WiFiNINA.h>
#include <ArduinoBearSSL.h>
#include <ArduinoECCX08.h>

WiFiClient wifiClient;
BearSSLClient sslClient(wifiClient);
String clientId;

const char CERTIFICATE[] = 
R"(-----BEGIN CERTIFICATE-----
MIIDqDCCAZACFDKUMbOTws3my1ID7L/qLMVFLVLIMA0GCSqGSIb3DQEBCwUAMHox
CzAJBgNVBAYTAmVlMQ4wDAYDVQQIDAVoYXJqdTEQMA4GA1UEBwwHVGFsbGlubjET
MBEGA1UECgwKa3J5ZidzIG1vbTEUMBIGA1UECwwLaGVyIGJlZHJvb20xHjAcBgNV
BAMMFXlvdSBkbyBub3Qgd2FubmEga25vdzAeFw0yMDEyMTkxNTIzMDNaFw0yMTEy
MTkxNTIzMDNaMHIxCzAJBgNVBAYTAmVlMQ4wDAYDVQQIEwVIYXJqdTEQMA4GA1UE
BxMHVGFsbGlubjEbMBkGA1UEChMSYXJkdWlubyBwbGF5Z3JvdW5kMRQwEgYDVQQL
Ewtrb3RrYXBvamEgMjEOMAwGA1UEAxMFYm9yaXMwWTATBgcqhkjOPQIBBggqhkjO
PQMBBwNCAAQ3wwkrRWWw8Qga5rvgMkd3bSg1Ho/uEX7LuIEc6JvHiTIddzyM0Guu
bap8h4sIU1kEsvFkYg46UXmcpBmZzpBIMA0GCSqGSIb3DQEBCwUAA4ICAQBNI/eK
Zi5JEyO+o2it/6NHMikK2MiIN2iMbEVay5ftxUj24o6AMD1jTbc1hxBPdi/VIbIX
J2jVfJLPVTcFvcQ7yQoACeB66O21XUJts9s4NfPkM9oIRvuS060QRyUMeS5IRITP
Psibnz5CwtG1OE2OJoT9CB5r4C94Kh1t2OtmEqqYjdzm06v8OGsJmYZGMp2moDZ2
lC1LRbRvLJ1rH8gIs/sk+csK4rtEPk6CrgKNB0j8QHFmTQbBphA8+tgZri99+uDv
bVoVZYEGXQNSh5nmZWU3GJOO1EO0ukXkKT1gCZUlDhnQ2PYhui/K85GL7i81eGua
INx2GYGPqRjs0VeoQmqZG25jn6HgPXL38rhrnMWitFXdp49q4JMQo1OODIXlJmMC
W3SZd05rcylDaFRpn8GPKy3hgm9eM+oxHMkzrFupAoXPxTfofpl3dUttlBPR9Rwi
2yYLZrQdH4y1UPXdq788F4MLYcU+Wa8NYdYOPJFDEgx3m6ptirnXE2tgq23vVw5X
ng6qw4YlOqCTCwhoyASDAN8heGR3/ctqYT2TEbOzLV7VWEEy/bYPv5FBik/xJZ27
/l/mNqhc4i77Dh7CCbndELJjfHYnfAPSFg8eAGKaEZvewiWEd2VVUaRF3JrYSmQC
5y5p8zQO/Xr/1X/YaLy9uVrFzPxwtZeRsg5sQg==
-----END CERTIFICATE-----)";

#define WIFI_SSID "111xxx-h368R"
#define WIFI_PASS "crypto9999"

IPAddress server(192,168,31,76);

unsigned long getTime() {
  return WiFi.getTime();
}


void connectWiFi() {
  Serial.print("Attempting to connect to SSID: ");
  Serial.print(WIFI_SSID);
  Serial.print(" ");

  while (WiFi.begin(WIFI_SSID, WIFI_PASS) != WL_CONNECTED) {
    // failed, retry
    Serial.print(".");
    delay(3000);
  }
  Serial.println();

  Serial.println("You are connected to the network");
  Serial.println();

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  delay(3000);
}

void setup() {
  Serial.begin(9600);

  // The next line waits for a serial connection for debugging
  while (!Serial);

  Serial.print("WiFi firmware version ");
  Serial.println(WiFi.firmwareVersion());
  Serial.println();

  // set a callback to get the current time
  // used for certification validation
  ArduinoBearSSL.onGetTime(getTime);

  if (!ECCX08.begin()) {
    Serial.println("No ECCX08 present!");
    while (1);
  }

  // Use the serial number from the ECC508 chip for the clientId
  // The MQTT clientId & AWS Thing name must match the common name in the X.509 certificate
  // If they don't match, an AWS IoT Core policy is configured to reject the connection
  // If you override the clientId here, create a new CSR, a new Thing and certificate
  // clientId = "";
  clientId = ECCX08.serialNumber();
  Serial.println("Client id = " + clientId);

  // set the ECCX08 slot to use for the private key
  // and the accompanying public cert for it
  sslClient.setEccSlot(0, CERTIFICATE);

  while(WiFi.status() != WL_CONNECTED) {
    connectWiFi();    
    delay(10000);
  }

  Serial.println(sslClient.connect(server, 443));
//
//  if (sslClient.connect(server, 443)) {
//    Serial.println("connected to server");
//    // Make a HTTP request:
//    sslClient.println("GET /");
//    sslClient.println("Connection: close");
//    sslClient.println(); 
//  } else {
//    Serial.println("Connection");
//  }
}

void loop() {
  // if the server's disconnected, stop the client:
//  if (!sslClient.connected()) {
//    Serial.println();
//    Serial.println("disconnecting from server.");
//    sslClient.stop();
//
//    // do nothing forevermore:
//    while (true);
//  }
//
//  while (sslClient.available()) {
//    char c = sslClient.read();
//    Serial.write(c);
//  }
}
