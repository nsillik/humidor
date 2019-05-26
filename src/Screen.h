#include <Adafruit_ssd1306syp.h>

class Screen {
    public:
        Screen(uint8_t, uint8_t);

        void displayTempAndHumidity(float temp, float humidity);
        void setup();
        void showConnecting();
        void showWifiFailure();
    private:
        Adafruit_ssd1306syp *display;
};