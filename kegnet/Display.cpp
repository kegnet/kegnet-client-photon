#include "Display.h"

#define OLED_RESET D4

Display::Display(int i2cAddress) {
  this->i2cAddress = i2cAddress;

 	display = new Adafruit_SSD1306(OLED_RESET);
	display->begin(SSD1306_SWITCHCAPVCC, i2cAddress);
  display->setTextColor(WHITE);
  display->setTextWrap(false);
  display->setTextSize(2);
  display->clearDisplay();
}

void Display::showPouring(float p, boolean isOz) {
  String s = String(p, 1);
  s.concat(isOz ? "oz" : "L");
  writeCenter(2, s);
}

void Display::showPour(float p, boolean isOz) {
  String s = String(p, 1);
  s.concat(isOz ? "oz" : "L");
  writeCenter(2, s, String("Enjoy!"));

  lastMessageTs = millis();
  lastMessageDelay = pourMessageDelay;
}

void Display::showNoPour() {
  writeCenter(2, String("No Pour"));

  lastMessageTs = millis();
  lastMessageDelay = noPourMessageDelay;
}

void Display::showTemp(float t, bool isF) {
  if (millis() - lastMessageTs < lastMessageDelay)
    return;

  String s = String(t, 0);
  s.concat(isF ? "F" : "C"); // TODO: add a degrees symbol (ascii 248)

  writeCenter(3, s);
}

void Display::writeCenter(int textSize, String s) {
  int x = (display->width() - (s.length() * textSize * 6))/2;
  int y = (display->height() - (textSize * 8))/2;

  display->clearDisplay();
  display->setTextSize(textSize);
  display->setCursor(x, y);
  display->println(s);
  display->display();
}

void Display::writeCenter(int textSize, String s1, String s2) {
  int y = (display->height() - (2 * textSize * 8))/2;
  display->clearDisplay();
  display->setTextSize(textSize);
  display->setCursorY(y);

  int x1 = (display->width() - (s1.length() * textSize * 6))/2;
  display->setCursorX(x1);
  display->println(s1);

  int x2 = (display->width() - (s2.length() * textSize * 6))/2;
  display->setCursorX(x2);
  display->println(s2);

  display->display();
}
