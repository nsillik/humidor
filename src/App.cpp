#include "App.h"
#include <Arduino.h>
#include <DHT.h>

#define SDA_PIN D1
#define SCL_PIN D2
#define DHT_PIN D6
#define RELAY_PIN D7

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
  } else {
    digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}

App::App()
{
    twoWire = new TwoWire();
    screen = new Screen(D1, D2, twoWire);
    dht = new DHT();
    humidifier = new Humidifier(RELAY_PIN);
    wifiClient = new WiFiClient();
    pubSubClient = new PubSubClient(*wifiClient);
    pubSubClient->setServer(IPAddress(68, 183, 22, 2), 1883);
    pubSubClient->setCallback(callback);
}

void App::setup()
{
    delay(1000);
    WiFi.disconnect();
    WiFi.persistent(false);
    WiFi.mode(WIFI_STA);
    WiFi.setAutoReconnect(true);
    Serial.begin(9600);
    dht->setup(DHT_PIN, DHT::DHT22);
    twoWire->begin(D2, D1);
    screen->setup();
    screen->showConnecting();
    lastSendAt = millis();
    WiFi.begin("NovelT", "gafsdgafsd");

    auto status = WL_IDLE_STATUS;
    Serial.printf("Connecting: ");
    Serial.printf("%d.", status);
    do
    {
        status = WiFi.status();
        Serial.printf("%d", status);
        delay(500);
    } while (status != WL_CONNECTED && status != WL_CONNECT_FAILED);
    Serial.println();
    randomSeed(micros());

    if (status == WL_CONNECT_FAILED)
    {
        screen->showWifiFailure();
        delay(2000);
    }
    else
    {
        Serial.print(WiFi.localIP());
        if (!pubSubClient->connected())
        {
            mqttReconnect();
        }
    }
    pinMode(RELAY_PIN, OUTPUT);
}

int errCount = 0;
void App::runLoop()
{
    bool chk = dht->getStatus();
    if (chk == DHT::ERROR_NONE)
    {
        float temp = dht->getTemperature() * 1.8 + 32;
        float humidity = dht->getHumidity();

        if ((humidity > 0) && (humidity < 99))
        {
            screen->displayTempAndHumidity(temp, humidity);
            humidifier->update(humidity);
        }
        Serial.printf("Tick: %10ld\tHum: %2.0f%%\tTem: %2.0f\n", millis(), humidity, temp);
        errCount = 0;

        if (millis() - lastSendAt > 10 * 1000)
        { // Every thirty seconds
            char *msg = (char *)malloc(256);
            int isOn = humidifier->getIsOn() ? 1 : 0;
            sprintf(msg, "%ld,%2.2f,%2.2f,%d", millis(), humidity, temp, isOn);
            pubSubClient->publish("office/humidor/humidity", String(humidity).c_str());
            pubSubClient->publish("office/humidor/temp", String(temp).c_str());
            pubSubClient->publish("office/humidor/isOn", String(isOn).c_str());
            free(msg);
            lastSendAt = millis();
        }
    }
    else
    {
        Serial.printf("DHT Error: %d (errCount: %d)\n", chk, errCount);
        errCount++;

        // Turn off the humidifier when there's an error, to prevent it getting stuck on
        humidifier->off(); 

        if (errCount > 50)
        {
            ESP.reset();
        }
    }

    if (!pubSubClient->connected())
    {
        mqttReconnect();
    }
    pubSubClient->loop();

    delay(100);
}

void App::mqttReconnect()
{
    // Loop until we're reconnected
    while (!pubSubClient->connected())
    {
        Serial.print("Attempting MQTT connection...");
        // Create a random client ID
        String clientId = "ESP8266Clientxxx-";
        clientId += String(random(0xffff), HEX);
        // Attempt to connect
        if (pubSubClient->connect(clientId.c_str(), "nsillik", "gafsdgafsd"))
        {
            Serial.println("connected");
            // Once connected, publish an announcement...
            pubSubClient->subscribe("inTopic");
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(pubSubClient->state());
            Serial.print(" WiFi status: ");
            Serial.print(WiFi.status());
            Serial.print(" ");
            Serial.print(clientId);
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}