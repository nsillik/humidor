#include <Adafruit_ssd1306syp.h>

#include <App.h>

#define SDA_PIN D1
#define SCL_PIN D2
#define DHT_PIN D6
#define RELAY_PIN D7

App *app = NULL;
void setup()
{
  app = new App();
  app->setup();
}

void loop()
{
  app->runLoop();
}