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
#elif ESP8266
    #include <ESP8266WiFi.h>
    #include <ESP8266HTTPClient.h>
    #include <WiFiClientSecure.h>

    #define S_0 14 
    #define S_1 12
    #define S_2 13
    #define S_3 15       
#endif

#define THRES_5 4.8828
#define THRES_3 3.2226
#define EspBaud 115200

#define LOW_PRE 2
#define MID_PRE 4
#define HIGH_PRE 6

class ConsentiumThings{
    public:
        ConsentiumThings();
        void begin();
        void loop_delay(long);
        void initWiFi(const char*, const char*);
        void sendREST(const char* , const char*, float [], String [], int, int); 
        float busRead(int, float);      
};

#endif