#include "Display.h"
#include "Thermistor.h"
#include "FlowMeter.h"

#define I2C_ADDRESS 0x3C
#define TEMP_PIN A1
#define FLOW_PIN D5

Display *display;
Thermistor *thermistor;
FlowMeter *flowMeter;

void setup()   {
  display = new Display(I2C_ADDRESS);
  flowMeter = new FlowMeter(FLOW_PIN, display);
  thermistor = new Thermistor(TEMP_PIN, display);
}

void loop() {
  flowMeter->process();
  thermistor->process();
}
