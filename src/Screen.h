#ifndef SCREEN_H
#define SCREEN_H

#include <Adafruit_SSD1306.h>

class Screen {
    public:
        Screen(uint8_t, uint8_t, TwoWire *);

        void displayTempAndHumidity(float temp, float humidity);
        void setup();
        void showConnecting();
        void showWifiFailure();
    private:
        Adafruit_SSD1306 *display;
};

#endif