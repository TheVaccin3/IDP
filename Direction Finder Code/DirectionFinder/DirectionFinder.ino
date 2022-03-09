#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(OLED_RESET);
int angle;
void setup() {
  angle = 0;
  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.clearDisplay();
  display.display();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Audio Angle Finder");
  display.display();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 20);
  display.println("Angle = ");
  display.display();
  display.setCursor(50, 20);
  display.setTextColor(WHITE, BLACK);
}

int oldV1, newV1;
int oldV2, newV2;
double timerStart, timerStop;
float periodMS;
float frequency;

void loop() {
  oldV1 = newV1;
  newV1 = analogRead(A0);
  //Serial.print(newV1);
  //Serial.print(",");
  oldV2 = newV2;
  newV2 = analogRead(A3);
  //Serial.println(newV2);
  //Serial.println(angle);


  if (oldV1 <= 0 && newV1 > 0) {
    timerStart = micros();
  }

  if (oldV1 > 0 && newV1 <= 0) {
    periodMS = (2.0 * (micros() - timerStart)) / 1000;
    frequency = 1.0 / periodMS;
  }

  Serial.println(periodMS);

  if (oldV2 <= 0 && newV2 > 0) {
    timerStop = micros() - timerStart;
  }
  angle = calculateAngle(timerStop);

}

int calculateAngle(int timer) {
  if (frequency < 750 || frequency > 1050) {
    frequency = 0;
    return 0;
  }
  return (360 * frequency * timer);
}
