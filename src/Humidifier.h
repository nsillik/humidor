#if !defined(HUMIDIFIER_H)
#define HUMIDIFIER_H

class Humidifier
{
public:
    Humidifier(uint8_t pin, float humidityThreshold = 40.0f);
    void update(float currentHumidity);
    void off();
    bool getIsOn();

private:
    void on();             // This is private so only the internal logic of the humidifier can turn it on
    int32_t onDuration = 60 * 5; // Turn on for 5 minutes at a time, in seconds
    int32_t offDuration = 60; // Leave off for a minimum of one minute
    uint8_t pin;
    bool isOn;
    int32_t onAt = 0;
    int32_t offAt = 0;
    float humidityThreshold;
};

#endif
