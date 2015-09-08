#ifndef THERMISTOR_H_
#define THERMISTOR_H_

#include <math.h>
#include "application.h"
#include "Display.h"

class Thermistor {
	public:
		Thermistor(int pin, Display* display);
		void process();
		void updateTemp();
		float readTempC();
		float toF(float tempK);

	private:
		int pin;
		Display* display;

		bool useF = true;
		int samples = 5;
		int sampleDelay = 20;
		int tempDelay = 1000;
		float adcMax = 4095;
    float seriesResistor = 10000;
    float thermistorNominal = 10000;
    float temperatureNominal = 25;
    float bCoef = 3950;

		double lastTemp = 0;
		unsigned long lastTempTs = 0;
};

#endif
