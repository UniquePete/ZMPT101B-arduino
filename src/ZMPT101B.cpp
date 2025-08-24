#include "ZMPT101B.h"

/// @brief ZMPT101B constructor
/// @param pin analog pin that ZMPT101B connected to.
/// @param frequency AC system frequency
ZMPT101B::ZMPT101B(uint8_t pin, uint16_t frequency)
{
	this->pin = pin;
	period = 1000000 / frequency;
	this->adcVref = VREF;
	this->adcScale = ADC_SCALE;
	pinMode(pin, INPUT);
}

/// @brief Alternate ZMPT101B constructor
/// @param pin analog pin that ZMPT101B connected to.
/// @param adcVref ADC max voltage
/// @param adcScale ADC resolution
/// @param sensitivity module sensitivity
ZMPT101B::ZMPT101B(uint8_t pin, float adcVref, uint16_t adcScale, float sensitivity)
{
	this->pin = pin;
	period = 1000000 / frequency;
	this->adcVref = adcVref;
	this->adcScale = adcScale;
	this->sensitivity = sensitivity;
	pinMode(pin, INPUT);
}

/// @brief Set sensitivity
/// @param value Sensitivity value
void ZMPT101B::setSensitivity(float value)
{
	sensitivity = value;
}

/// @brief Calculate zero point
/// @return zero / center value
int ZMPT101B::getZeroPoint()
{
	uint32_t Vsum = 0;
	uint32_t measurements_count = 0;
	uint32_t t_start = micros();

	while (micros() - t_start < period)
	{
		Vsum += analogRead(pin);
		measurements_count++;
	}

	return Vsum / measurements_count;
}

/// @brief Calculate root mean square (RMS) of AC valtage
/// @param frequency AC system frequency
/// @param loopCount Loop count to calculate
/// @return root mean square (RMS) of AC valtage
float ZMPT101B::getRmsVoltage(uint16_t frequency, uint8_t loopCount)
{
	period = 1000000 / frequency;
	return getRmsVoltage(loopCount);
}

/// @brief Calculate root mean square (RMS) of AC valtage
/// @param loopCount Loop count to calculate
/// @return root mean square (RMS) of AC valtage
float ZMPT101B::getRmsVoltage(uint8_t loopCount)
{
	double readingVoltage = 0.0f;

	for (uint8_t i = 0; i < loopCount; i++)
	{
		int zeroPoint = this->getZeroPoint();

		int32_t Vnow = 0;
		uint32_t Vsum = 0;
		uint32_t measurements_count = 0;
		uint32_t t_start = micros();

		while (micros() - t_start < period)
		{
			Vnow = analogRead(pin) - zeroPoint;
			Vsum += (Vnow * Vnow);
			measurements_count++;
		}

		readingVoltage += sqrt(Vsum / measurements_count) / adcScale * adcVref * sensitivity;
	}

	return readingVoltage / loopCount;
}
