#ifndef APP_H
#define APP_H
#include <DHT.h>
#include <Wire.h>
#include <ESP8266WiFi.h> // Include the Wi-Fi library
#include <PubSubClient.h>

#include "Humidifier.h"
#include "Screen.h"

class App {
    public:
        App();

        void setup();
        void runLoop();
    private:
        Screen *screen;
        DHT *dht;
        Humidifier *humidifier;
        TwoWire *twoWire;
        PubSubClient *pubSubClient;
        WiFiClient *wifiClient;

        int lastSendAt;
        void mqttReconnect();
        void mqttCallback(char* topic, byte* payload, unsigned int length);
};
#endif