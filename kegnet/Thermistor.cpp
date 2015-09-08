#include "Thermistor.h"
#include "application.h"

#define ABS_ZERO 273.15

Thermistor::Thermistor(int pin, Display* display) {
	this->pin = pin;
	this->display = display;

	Particle.variable("tempC", &lastTemp, DOUBLE);

	pinMode(pin, INPUT);
}

void Thermistor::process() {
  if (millis() - lastTempTs > tempDelay) {
    updateTemp();
  }
}

void Thermistor::updateTemp() {
  float newTemp = readTempC();
  //float percentChange = ((newTemp - lastTemp)/newTemp)*100;
  //if (percentChange < -1 || percentChange > 1) {
    lastTemp = newTemp;
    display->showTemp(useF ? toF(newTemp) : newTemp, useF);
  //}
  lastTempTs = millis();
}

float Thermistor::toF(float tempC) {
	return (tempC * 1.8) + 32;
}

float Thermistor::readTempC() {
	float sum = 0;
	for(int i=0; i<samples; i++) {
			sum += analogRead(pin);
			delay(sampleDelay);
	}

	float adcRaw = sum / samples;

	float r = seriesResistor / (adcMax / adcRaw - 1);
	float s = (r / thermistorNominal);
	s = log(s);
	s = s * (1.0 / bCoef);
	s = s + 1.0 / (temperatureNominal + ABS_ZERO);
	s = 1.0 / s;
	s = s - ABS_ZERO;

	return s;
}
