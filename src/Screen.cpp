#include "Screen.h"
#include <Arduino.h>
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Screen::Screen(uint8_t sda, uint8_t scl, TwoWire *wire)
{
    display = new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, wire, -1);
}

void Screen::setup() {
    display->begin(SSD1306_SWITCHCAPVCC, 0x3c, false, false);
    display->clearDisplay();
    display->setTextSize(3);
    display->setTextColor(WHITE);
    display->setCursor(20, 20);
    display->print("BEEP");
    display->display();
}

void Screen::displayTempAndHumidity(float temp, float humidity) {
      display->clearDisplay();
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
      display->display();
}

void Screen::showConnecting(){
    display->clearDisplay();
    display->setTextSize(1);
    display->setCursor(10, 10);
    display->print("Connecting.");
    display->display();
}

void Screen::showWifiFailure() {
    display->clearDisplay();
    display->setTextSize(2);
    display->setCursor(10, 10);
    display->print("CONN FAILED");
    display->display();
}