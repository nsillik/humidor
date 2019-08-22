#include "Arduino.h"
#include "Humidifier.h"

Humidifier::Humidifier(uint8_t pin, float humidityThreshold)
{
    this->pin = pin;
    digitalWrite(this->pin, LOW);
    this->isOn = false;
    this->humidityThreshold = humidityThreshold;
}

void Humidifier::update(float currentHumidity)
{
    auto currentMillis = millis();
    if (this->isOn)
    {
        // If we're currently on, and the `duration` has passed, turn off.
        if (currentMillis - this->onAt > this->onDuration * 1000)
        {
            this->off();
        }
    }
    else if (currentHumidity < this->humidityThreshold && currentMillis - this->offAt > this->offDuration * 1000)
    {
        this->on();
    }
}

bool Humidifier::getIsOn() {
    return this->isOn;
}

void Humidifier::on()
{
    digitalWrite(this->pin, HIGH);
    this->isOn = true;
    this->onAt = millis();
}

void Humidifier::off()
{
    digitalWrite(this->pin, LOW);
    this->isOn = false;
    this->offAt = millis();
}