/*
 * This program shows the use of an alternate constructor and method to use this library.
*/

#include <ZMPT101B.h>

uint16_t signalFrequency = 50;	// 50Hz
uint8_t sampleCycles = 5;			  // Sampling cycles
float zmptSensitivity = 334;		// Sensor calibration
uint16_t adcScale = 4095;				// 12-bit resolution
float adcVref = 2.4;						// 2.4V

// ZMPT101B sensor output connected to analog pin A0
// Change the sensitivity value based on value you got from the calibrate example
ZMPT101B voltageSensor(A0, adcVref, adcScale, zmptSensitivity);

void setup() {
  Serial.begin(115200);
}

void loop() {
  // read the voltage and then print via Serial.
  float voltage = voltageSensor.getRmsVoltage(signalFrequency, sampleCycles);
  Serial.println(voltage);

  delay(1000);
}
