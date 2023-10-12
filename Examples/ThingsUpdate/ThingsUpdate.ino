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

void loop() {
  double data_0 = board.busRead(0, THRES_5); // Read voltage data as a double

  double sensor_val[] = {data_0}; // Sensor data array of doubles
  String info_buff[] = {"Temperature"}; // Sensor info array

  int sensor_num = sizeof(sensor_val) / sizeof(sensor_val[0]); // Number of sensors connected

  // Send data over REST with delay and desired precision
  board.sendREST(key, board_key, sensor_val, info_buff, sensor_num, LOW_PRE);

  delay(interval);
}
