#include <NMCU.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(D4);

bool lastFrame = true;

static const unsigned char PROGMEM tas_logo[] = {
  B00000000, B00011000, B00000000,
  B00000000, B00100100, B00000000,
  B00000000, B00100100, B00000000,
  B00000000, B01011010, B00000000,
  B00000000, B01011010, B00000000,
  B00000000, B01000010, B00000000,
  B00000000, B00111100, B00000000,
  B00000000, B00000000, B00000000,
  B00000100, B01111110, B00100000,
  B00001011, B10111101, B11010000,
  B00010000, B00111100, B00001000,
  B00010100, B10100101, B11101000,
  B00100011, B00100100, B11000100,
  B00100011, B00111101, B11100100,
  B00100100, B10111101, B00100100,
  B00010000, B00111100, B00001000,
  B00011111, B11111111, B11111000,
  B00011001, B11100111, B10011000,
  B00011001, B11100111, B10011000,
  B00111111, B11111111, B11111100,
  B00100000, B00111100, B00000100,
  B00100000, B00100100, B00000100,
  B00100000, B00100100, B00000100,
  B00100000, B00111100, B00000100,
  B00011000, B00111100, B00011000,
  B00000111, B11111111, B11100000,
  B11100000, B00111100, B00000111,
  B10011111, B11000011, B11111001,
  B11000000, B11111111, B00000011,
  B00111111, B10000001, B11111100,
  B00000000, B11111111, B00000000
};

void setup() {
  Serial.begin(115200); //For debug information if a unit breaks

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  Serial.println("Initialized");
  display.clearDisplay();
  display.drawBitmap(52, 0, tas_logo, 24, 35, WHITE);
  display.display();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  printSplash();
}

void printSplash() {
  display.setCursor(24, 5);
  display.println("TAS army cadet");
  display.setCursor(14, 13);
  display.println("navigational aid");
}

bool getButton() {
  if (digitalRead(D8)) {
    delay(5);
  }
  return digitalRead(D8);
}

void loop() {
  if (getButton() && !lastFrame) {
    display.clearDisplay();
    printSplash();
    display.setCursor(24, 21);
    display.println("Input recieved");
    display.display();
    lastFrame = true;
  } else if (!getButton() && lastFrame) {
    display.clearDisplay();
    printSplash();
    display.setCursor(24, 21);
    display.println("Awaiting input");
    display.display();
    lastFrame = false;
  }
}
