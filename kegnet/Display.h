#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "application.h"

#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

class Display {
	public:
		Display(int i2cAddress);
		void showPouring(float p, boolean isOz);
		void showNoPour();
		void showPour(float p, boolean isOz);
		void showTemp(float t, bool isF);

	private:
		int i2cAddress;
		Adafruit_SSD1306 *display;

		int pourMessageDelay = 6000;
		int noPourMessageDelay = 1000;

		unsigned long lastMessageTs = 0;
		int lastMessageDelay = 0;

		void writeCenter(int textSize, String s);
		void writeCenter(int textSize, String s1, String s2);
};

#endif
