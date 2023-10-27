#ifndef ConsentiumThingsDalton_h
#define ConsentiumThingsDalton_h

#ifdef ESP32
    #include <WiFi.h>
    #include <HTTPClient.h> 

    #define S_0 21
    #define S_1 19
    #define S_2 18
    #define S_3 5    
    #define ADC_IN 34 // ADC1_CH6

    #define ADC_VREF_mV    3300.0 // in millivolt
    #define ADC_RESOLUTION 4096.0
#elif ESP8266
    #include <ESP8266WiFi.h>
    #include <ESP8266HTTPClient.h>
    #include <WiFiClientSecure.h>
            
    #define S_0 14 
    #define S_1 12
    #define S_2 13
    #define S_3 15  
    #define ADC_IN A0 // A0

    #define ADC_VREF_mV    3300.0 // in millivolt
    #define ADC_RESOLUTION 1024.0
#elif ARDUINO_RASPBERRY_PI_PICO_W
    #include <WiFi.h>
    #include <HTTPClient.h>
    #include <WiFiClientSecure.h>
    #define S_0 6 
    #define S_1 7
    #define S_2 8
    #define S_3 9  
    #define ADC_IN 34 // ADC Channel 2
    #define ADC_VREF_mV    3300.0 // in millivolt
    #define ADC_RESOLUTION 4096.0  
#endif

#define SELECT_LINES 4
#define MUX_IN_LINES 16

#define WIFI_DELAY 500

#define NTP_SYNC_WAIT 8 * 3600 * 2

#define MAX_JSON_SIZE 200
#define MAX_JSON_SENSOR_DATA_SIZE 50

#define ARRAY_RESERVE 100

#define ESPBAUD 115200

#define LOW_PRE 2
#define MID_PRE 4
#define HIGH_PRE 7

class ConsentiumThings{
    public:
        ConsentiumThings();
        void begin();
        void initWiFi(const char*, const char*);
        void sendREST(const char* , const char*, double [], const char* [], int, int); 
        float busRead(int);      
};

#endif
