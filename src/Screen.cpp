#include "Screen.h"
#include <Arduino.h>
#include <Adafruit_ssd1306syp.h>

Screen::Screen(uint8_t sda, uint8_t scl)
{
    display = new Adafruit_ssd1306syp(sda, scl); // = Adafruit_ssd1306syp display(D1, D2);

}

void Screen::setup() {
    display->initialize();
    display->clear();
    display->setTextSize(3);
    display->setTextColor(WHITE);
    display->setCursor(20, 20);
    display->print("BEEP");
    display->update();
}

void Screen::displayTempAndHumidity(float temp, float humidity) {
      display->clear();
      display->setTextSize(3);
      display->setTextColor(WHITE);
      display->setCursor(10, 10);
      display->print("T: ");
      display->printf("%.0f", temp);
      display->print((char)167);
      display->setCursor(10, 40);
      display->print("H: ");
      display->printf("%.0f", humidity);
      display->print("%");
      display->update();
}

void Screen::showConnecting(){
    display->clear();
    display->setTextSize(2);
    display->setCursor(10, 10);
    display->print("Connecting.");
    display->update();
}

void Screen::showWifiFailure() {
    display->clear();
    display->setTextSize(2);
    display->setCursor(10, 10);
    display->print("CONN FAILED");
    display->update();
}