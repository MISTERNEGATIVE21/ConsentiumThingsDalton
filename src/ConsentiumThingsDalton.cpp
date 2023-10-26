#include <ArduinoJson.h>
#include <ConsentiumThingsDalton.h>
#include <certs/server_certificates.h>
#include <utils/consentium_essentials.h>

WiFiClientSecure client;
HTTPClient http;

#ifdef ESP8266
  X509List cert(consentium_root_ca);
#endif

const int kselect_lines[SELECT_LINES] = {S_0, S_1, S_2, S_3}; // MUX select lines

const int kMUXtable[MUX_IN_LINES][SELECT_LINES] = {
  {0, 0, 0, 0}, {1, 0, 0, 0}, {0, 1, 0, 0}, {1, 1, 0, 0},
  {0, 0, 1, 0}, {1, 0, 1, 0}, {0, 1, 1, 0}, {1, 1, 1, 0},
  {0, 0, 0, 1}, {1, 0, 0, 1}, {0, 1, 0, 1}, {1, 1, 0, 1},
  {0, 0, 1, 1}, {1, 0, 1, 1}, {0, 1, 1, 1}, {1, 1, 1, 1}
};

ConsentiumThings::ConsentiumThings() {}

void syncTime(){
    configTime(3 * 3600, 0, "pool.ntp.org", "time.nist.gov");
    Serial.print(F("Waiting for NTP time sync: "));
    time_t now = time(nullptr);
    while (now < NTP_SYNC_WAIT) {
      delay(500);
      now = time(nullptr);
    }
    struct tm timeinfo;
    gmtime_r(&now, &timeinfo); 
}

void ConsentiumThings::begin() {
  Serial.begin(ESPBAUD);
  #if defined(ESP32) || defined(ARDUINO_RASPBERRY_PI_PICO_W)
    client.setCACert(consentium_root_ca);
  #elif ESP8266
    syncTime();
    client.setTrustAnchors(&cert);
  #endif

  for (int i = 0; i < SELECT_LINES; i++) {
    pinMode(kselect_lines[i], OUTPUT);
  }
}

void ConsentiumThings::initWiFi(const char* ssid, const char* password) {
  WiFi.mode(WIFI_STA);
  
  Serial.print(F("Attempting to connect SSID: "));
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(WIFI_DELAY);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print(F("Got IP : "));
  Serial.println(WiFi.localIP());
}

float ConsentiumThings::busRead(int j) {
  for (int i = 0; i < SELECT_LINES; i++) {
    digitalWrite(kselect_lines[i], kMUXtable[j][i]);
  }
  return analogRead(ADC_IN);
}

void ConsentiumThings::sendREST(const char* key, const char* board_id, double sensor_data[], const char* sensor_info[], int sensor_num, int precision) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println(F("WiFi not connected. Cannot send REST request."));
    return;
  }

  // create the server URL
  String serverUrl = String(server_url);
  serverUrl.reserve(ARRAY_RESERVE);
  serverUrl.concat("key=");
  serverUrl.concat(String(key));
  serverUrl.concat("&boardkey=");
  serverUrl.concat(String(board_id));

  DynamicJsonDocument jsonDocument(MAX_JSON_SIZE + sensor_num * MAX_JSON_SENSOR_DATA_SIZE);

  // Create a JSON array for sensor data
  JsonArray sensorDataArray = jsonDocument["sensors"]["sensorData"].to<JsonArray>();

  // Add sensor data dynamically
  for (int i = 0; i < sensor_num; i++) {
    // Create a JSON object for the current sensor data
    JsonObject sensorData = sensorDataArray.createNestedObject();
    sensorData["info"] = sensor_info[i];
    sensorData["data"] = String(sensor_data[i], precision);
  }

  // Serialize the JSON document to a string
  String jsonString;
  serializeJsonPretty(jsonDocument, jsonString);

  http.begin(client, serverUrl);

  // Set the content type header to application/json
  http.addHeader("Content-Type", "application/json");

  // Make the POST request
  int httpCode = http.sendRequest("POST", jsonString);
  
  // Check for errors
  if (httpCode > 0) {
    if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_CREATED) {
      String response = http.getString();
      String combinedOutput = "Server response: " + response + " with code: " + String(httpCode) + "\nData packet: " + jsonString + "\n";
      Serial.println(combinedOutput);
    }
  } 
  else {
    Serial.println(F("HTTP POST request failed."));
  }
  // Close the HTTP connection
  http.end();
}
