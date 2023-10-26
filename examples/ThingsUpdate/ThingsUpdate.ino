/***************************************************
  This is Consentium's IoT library
  ----> https://consentiuminc.online/
  Check out the links above for our tutorials and product diagrams.

  This Consentium's IoT library works only for 3.3v tolerant ESP8266/ESP32 Edge boards.  
 
  Written by Debjyoti Chowdhury for Consentium.
  MIT license, all text above must be included in any redistribution
 ****************************************************/


#include <ConsentiumThingsDalton.h>

ConsentiumThings board; // Create ConsentiumThings object

const char *ssid = "YOUR_WIFI_SSID"; // Add WiFi SSID
const char *pass = "YOUR_WIFI_PASSWORD"; // Add WiFi password
constexpr int interval = 7000; // Wait for 7 seconds
const char *ApiKey = "YOUR_API_KEY"; // Write API key
const char *BoardApiKey = "YOUR_BOARD_API_KEY"; // Board API key

void setup() {
  board.begin(); // Initialize IoT board
  board.initWiFi(ssid, pass); // Begin WiFi connection
}

void loop(){
  double data_0 = board.busRead(0);  // read voltage data
  
  double sensorValues[] = {data_0};  // sensor data array
  const char* sensorInfo[] = {"Temperature"}; // sensor info. array
  
  int sensorCount = sizeof(sensorValues)/sizeof(sensorValues[0]); // number of sensors connected 
  
  board.sendREST(ApiKey, BoardApiKey, sensorValues, sensorInfo, sensorCount, LOW_PRE); // send over REST with delay with desired prescision

  delay(interval);
}
