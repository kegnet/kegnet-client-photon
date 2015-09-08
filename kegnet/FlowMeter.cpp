#include "FlowMeter.h"

#define PROCESS_ALARM_DELAY 18000

FlowMeter::FlowMeter(int pin, Display* display) {
	this->pin = pin;
	this->display = display;

	// this cool magic from https://community.particle.io/t/solved-how-to-register-a-c-instance-method-with-spark-function/13999/24
	auto interruptHandler = std::bind(&FlowMeter::pulse, this);
	attachInterrupt(pin, interruptHandler, RISING);
}

void FlowMeter::pulse() {
    interruptCount++;
}

void FlowMeter::process() {
	if (interruptCount == 0)
		return;

	unsigned long st = millis();
	unsigned long lastProcess = st;
	unsigned long lastPulse = st;

	int pulseCount = interruptCount;

	while (interruptCount > pulseCount || (millis() - lastPulse) < pourDelay) {
		if (interruptCount > pulseCount) {
			lastPulse = millis();
		}

		pulseCount = interruptCount;
		display->showPouring(isOz ? toOz(pulseCount) : toL(pulseCount), isOz);

		if ((millis() - lastProcess) > PROCESS_ALARM_DELAY) {
			lastProcess = millis();
			Particle.process();
		} else {
			delay(pollDelay);
		}
	}

	interruptCount = 0;

	unsigned long et = (millis() - st);

	if (pulseCount < minPourPulses) {
		display->showNoPour();
		return;
	}

	lastPour = millis();
	display->showPour(isOz ? toOz(pulseCount) : toL(pulseCount), isOz);
	publishPour(pulseCount, et);
}

void FlowMeter::publishPour(int pulseCount, unsigned long et) {
	String msg = String();
	msg.concat("{\"pin\":");
	msg.concat(pin);
	msg.concat(",\"pulses\":");
	msg.concat(pulseCount);
	msg.concat(",\"ms\":");
	msg.concat(et);
	msg.concat("}");

	Particle.publish("pour", msg);
}

float FlowMeter::toL(float pulses) {
	return pulses/ppl;
}

float FlowMeter::toOz(float pulses) {
	return pulses / (ppl/33.814);
}
