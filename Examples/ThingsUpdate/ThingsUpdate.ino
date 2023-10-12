/***************************************************
  This is Consentium Inc's IoT library
  ----> https://consentiuminc.online/
  Check out the links above for our tutorials and product diagrams.

  This Consentium Inc's IoT library works only for 3.3v tolerant ESP8266/ESP32 Edge boards.  
 
  Written by Debjyoti Chowdhury for Consentium Inc.
  MIT license, all text above must be included in any redistribution
 ****************************************************/


#include <ConsentiumThingsDalton.h>

ConsentiumThings board; // Create ConsentiumThings object

const char *ssid = "YOUR_WIFI_SSID"; // Add WiFi SSID
const char *pass = "YOUR_WIFI_PASSWORD"; // Add WiFi password
const long interval = 7000; // Wait for 7 seconds
const char *key = "YOUR_API_KEY"; // Write API key
const char *board_key = "YOUR_BOARD_API_KEY"; // Board API key

void setup() {
  board.begin(); // Initialize IoT board
  board.initWiFi(ssid, pass); // Begin WiFi connection
}

void loop(){
  float data_0 = board.busRead(0, THRES_5);  // read voltage data
  
  float sensor_val[] = {data_0};  // sensor data array
  String info_buff[] = {"Temperature"}; // sensor info. array
  
  int sensor_num = sizeof(sensor_val)/sizeof(sensor_val[0]); // number of sensors connected 
  
  board.sendREST(key, board_key, sensor_val, info_buff, sensor_num, LOW_PRE); // send over REST with delay with desired prescision

  delay(interval);
}
