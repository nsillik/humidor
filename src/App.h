#ifndef APP_H
#define APP_H
#include "Screen.h"
#include <DHT.h>

class App {
    public:
        App();

        void setup();
        void runLoop();
    private:
        Screen *screen;
        DHT *dht;
};
#endif