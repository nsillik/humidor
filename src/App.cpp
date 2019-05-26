#include "App.h"
#include <Arduino.h>
#include <DHT.h>
// #include <ESP8266WiFi.h>        // Include the Wi-Fi library
// #include <ESP8266mDNS.h>        // Include the mDNS library

#define SDA_PIN D1
#define SCL_PIN D2
#define DHT_PIN D6
#define RELAY_PIN D7

App::App()
{
    screen = new Screen(D1, D2);
    dht = new DHT(DHT_PIN, DHT11);
}

void App::runLoop()
{
    bool chk = dht->read();

    if (chk)
    {
        float temp = dht->readTemperature(true);
        float humidity = dht->readHumidity();

        if ((humidity > 0) && (humidity < 99))
        {
            screen->displayTempAndHumidity(temp, humidity);

            if (humidity < 40)
            {
                digitalWrite(RELAY_PIN, HIGH);
            }
            else
            {
                digitalWrite(RELAY_PIN, LOW);
            }
        }
    }
    delay(2000);
}

void App::setup()
{
    screen->setup();
    screen->showConnecting();
    // WiFi.begin("NovelT", "gafsdgafsd");
    // auto status = WL_IDLE_STATUS;
    // do {
    //     status = WiFi.status();
    // } while (status != WL_CONNECTED || status != WL_CONNECT_FAILED);

    // if (status = WL_CONNECT_FAILED) {
    //     screen->showWifiFailure();
    // }
    pinMode(RELAY_PIN, OUTPUT);
    delay(1000);
}