#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(OLED_RESET);
int angle;
void setup() {
  angle = 0;
  Serial.begin(1000000);
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
}

int oldV1, newV1;
int oldV2, newV2;
int timerStart, timerStop;
int frequency;


void loop() {
  oldV1 = newV1;
  newV1 = analogRead(A0) * (200.0 / 1023.0);
  Serial.print(newV1);
  Serial.print(",");
  oldV2 = newV2;
  newV2 = analogRead(A3) * (200.0 / 1023.0);
  Serial.print(newV2);
  Serial.println(angle);

  if (oldV1 < 5 && newV1 > 5) {
    timerStart = micros();
  }

  if (oldV1 > 5 && newV1 < 5) {
    frequency = 1 / (2 * (micros() - timerStart));
  }

  if (oldV2 < 5 && newV2 > 5) {
    timerStop = micros() - timerStart;
    //timerStop is the phase delay of the 2 signals in microseconds
  }
  //angle = calculateAngle(timerStop);

  if (micros() % 100000 == 0) { // run this section of code once/second
    display.setCursor(50, 20);
    display.setTextColor(WHITE, BLACK);
    display.println(frequency);
    display.display();
  }
}

int calculateAngle(int timer) {
  if (frequency < 750 || frequency > 1050) {
    return 0;
  }
  return (360 * frequency * timer);
}
