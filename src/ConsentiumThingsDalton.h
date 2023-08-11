#ifndef ConsentiumThingsDalton_h
#define ConsentiumThingsDalton_h

#include <Arduino.h>  

#ifdef ESP32
    #include <WiFi.h>
    #include <HTTPClient.h> 

    #define S_0 14 
    #define S_1 12
    #define S_2 13
    #define S_3 15  
    #define ADC_IN 34 // ADC1_CH6
#elif ESP8266
    #include <ESP8266WiFi.h>
    #include <ESP8266HTTPClient.h>
    #include <WiFiClientSecure.h>

    #define S_0 14 
    #define S_1 12
    #define S_2 13
    #define S_3 15  
    #define ADC_IN A0 // A0     
#endif

#define SELECT_LINES 4
#define MUX_IN_LINES 16

#define WIFI_DELAY 500

#define MAX_JSON_SIZE 200
#define MAX_JSON_SENSOR_DATA_SIZE 50

#define ARRAY_RESERVE 100


#define THRES_5 4.8828
#define THRES_3 3.2226

#define ESPBAUD 115200

#define LOW_PRE 2
#define MID_PRE 4
#define HIGH_PRE 7

class ConsentiumThings{
    public:
        ConsentiumThings();
        void begin();
        void initWiFi(const char*, const char*);
        void sendREST(const char* , const char*, double [], String [], int, int); 
        float busRead(int, float);      
};

#endif