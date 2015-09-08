#ifndef FLOWMETER_H_
#define FLOWMETER_H_

#include "application.h"
#include "Display.h"

class FlowMeter {
	public:
		FlowMeter(int pin, Display* display);
		void pulse();
		void process();

	private:
		int pin;
		Display* display;

		boolean isOz = true;
		int pourDelay = 1500;
		int minPourPulses = 250;
		int pollDelay = 50;
		float ppl = 5600;

		unsigned long lastPour = 0;
		volatile int interruptCount = 0;

		void publishPour(int pulses, unsigned long et);

		float toL(float pulses);
		float toOz(float pulses);
};

#endif
