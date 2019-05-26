#include <Adafruit_ssd1306syp.h>
#include <DHT.h>

#define SDA_PIN D1
#define SCL_PIN D2
#define DHT_PIN D6
#define RELAY_PIN D7

Adafruit_ssd1306syp display(D1, D2);
DHT dht(DHT_PIN, DHT11);
static int loop_tick = 0;

void setup()
{
  pinMode(RELAY_PIN, OUTPUT);
  delay(1000);
  display.initialize();
  display.clear();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(20, 20);
  display.print("BEEP");
  display.update();
  delay(1000);
}

void loop()
{
  loop_tick++;
  bool chk = dht.read();

  if (chk) {
    float temp = dht.readTemperature(true);
    float humidity = dht.readHumidity();

    if ((humidity > 0) && (humidity < 99)) {
      display.clear();
      display.setTextSize(3);
      display.setTextColor(WHITE);
      display.setCursor(10, 10);
      display.print("T: ");
      display.printf("%.0f", temp);
      display.print((char)167);
      display.setCursor(10, 40);
      display.print("H: ");
      display.printf("%.0f", humidity);
      display.print("%");
      display.update();

      if (humidity < 40) {
        digitalWrite(RELAY_PIN, HIGH);
      } else {
        digitalWrite(RELAY_PIN, LOW);
      }
    }
  }

  delay(2000);

  display.clear();
}