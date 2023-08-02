#include <ArduinoJson.h>

#include "ConsentiumThingsDalton.h"
#include "auth_cert.h"


WiFiClientSecure client;
HTTPClient http;

int select_lines[4] = {14,12,13,15}; //s0, s1, s2, s3

int MUXtable[16][4]=
{
  {0,0,0,0}, {1,0,0,0}, {0,1,0,0}, {1,1,0,0},
  {0,0,1,0}, {1,0,1,0}, {0,1,1,0}, {1,1,1,0},
  {0,0,0,1}, {1,0,0,1}, {0,1,0,1}, {1,1,0,1},
  {0,0,1,1}, {1,0,1,1}, {0,1,1,1}, {1,1,1,1}
};

ConsentiumThings::ConsentiumThings(){}

void ConsentiumThings::begin(){
    Serial.begin(EspBaud);
    pinMode(NETWRK_LED, OUTPUT);
    for(int i=0; i<4; i++) {
      pinMode(select_lines[i],OUTPUT); 
    }   
}

void ConsentiumThings::initWiFi(const char* ssid, const char* password){
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Got IP : ");
  Serial.println(WiFi.localIP());
}

float ConsentiumThings::busRead(int j, float threshold){
  digitalWrite(select_lines[0], MUXtable[j][0]);
  digitalWrite(select_lines[1], MUXtable[j][1]);
  digitalWrite(select_lines[2], MUXtable[j][2]);
  digitalWrite(select_lines[3], MUXtable[j][3]);
  float adc_0_data = analogRead(A0) * threshold;
  return adc_0_data;
}

void ConsentiumThings::sendREST(const char* key, const char* board_id, float sensor_data[], String sensor_info[], int sensor_num, int pre){ 
  String serverUrl = "https://consentiuminc.onrender.com/api/board/updatedata/?";
  serverUrl += "key=" + String(key) + "&boardkey=" + String(board_id);
  
  if(WiFi.status()== WL_CONNECTED){
    
    #ifdef ESP8266
      client.setBufferSizes(8192, 8192);
      client.setInsecure();
      client.setCACert((const uint8_t*)consentium_root_ca, sizeof(consentium_root_ca) - 1);     
    #endif
    #ifdef ESP32
      client.setCACert(consentium_root_ca);
    #endif
    
    DynamicJsonDocument jsonDocument(200 + sensor_num * 50); // Adjust the initial size based on your JSON data size

    // Create a JSON array for sensor data
    JsonArray sensorDataArray = jsonDocument["sensors"]["sensorData"].to<JsonArray>();

    // Add sensor data dynamically
    for (int i = 0; i < sensor_num; i++) {
      // Create a JSON object for the current sensor data
      JsonObject sensorData = sensorDataArray.createNestedObject();
      sensorData["info"] = sensor_info[i];
      sensorData["data"] = String(sensor_data[i], pre); // Adjust the precision based on your sensor data
    }

    // Serialize the JSON document to a string
    String jsonString;
    
    serializeJson(jsonDocument, jsonString);
    
    http.begin(client, serverUrl);

    // Set the content type header to application/json
    http.addHeader("Content-Type", "application/json");

    // Make the POST request
    int httpCode = http.sendRequest("POST", jsonString);

    // Check for errors
    if (httpCode > 0) {
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_CREATED) {
          String response = http.getString();
          Serial.println("Server response: " + response);
      }
    } 
    else{
      Serial.println("HTTP POST request failed.");
    }
    // Close the HTTP connection
    http.end();

    // Print the generated JSON payload to the serial monitor
    Serial.println("Data packet: " + jsonString);
  }
}

