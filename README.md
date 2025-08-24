# ZMPT101B

An Arduino library to interact with the [ZMPT101B](http://www.zeming-e.com/file/0_2013_10_18_093344.pdf),
an active single phase AC voltage sensor module.

This library is based on [Ruslan Koptev](https://github.com/rkoptev) ACS712
current sensors library for Arduino <https://github.com/rkoptev/ACS712-arduino>.
This library is modified so that it can be used with ZMPT101B voltage sensor
with the same code principle.
An alternate constructor and method are also included to provide a similar structure
to that in the [Rob Tillaart](https://github.com/RobTillaart/ACS712) library.

## Methods

### Constructor

```c++
ZMPT101B(uint8_t pin, uint16_t frequency = DEFAULT_FREQUENCY);
```

Basic constructor has a parameters `pin` for analog input to tell where is connected
and the `frequency` value of the AC voltage that the sensor will measure (by
default 50.0Hz).

```c++
ZMPT101B (uint8_t pin, float adcVref, uint16_t adcScale, float sensitivity);
```

Alternate constructor provides a similar structure to that used in the Tillaart ACS712
library. It has parameters `pin` to identify the ADC to which the sensor is connected,
`adcVref` to identify the ADC reference voltage, `adcScale` to set the ADC scale and
`sensitivity` to set the sensitivity of the sensor.

### Reading RMS Voltage Value

```c++
float getRmsVoltage(uint8_t loopCount = 1)
```

This method allows us to obtain the root mean square (RMS) value of the voltage.
By default this method will only calculate the RMS value of one period wave. If
you want the calculation to be done over several periods you can specify how
many iterations you want. Reading more than once will usually return a more
precise value however, sometimes it will take longer.

```c++
float getRmsVoltage(uint16_t frequency, uint8_t loopCount)
```

This method allows us to specify the input voltage frequency, from which the
measurement period is derived, at the time of measurement.

### Set Sensitivity

```c++
void setSensitivity(float value)
```

This method sets the sensitivity value of the sensor. The Sensitivity is the
ratio of the output voltage sensor (that read by the ADC) to the input voltage
sensor. The default value of sensitivity is 500.0.

## Example

### Circuit

![circuit](/img/schematic.png)

⚠️ If you are using a board with a 3.3 Volt system you should connect VCC to 3.3
Volt (eg ESP board family).

### Steep

#### 0. Make sure the output voltage from the sensor is not clipped and distorted

Connect the sensor to the voltage source you are going to measure.

Use the following code to observe the waveform from the ZMPT1b sensor output.

```c++
void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.println(analogRead(A0));
  delayMicroseconds(1000);
}
```

Upload code and open serial plotter.

Rotate the trimpot on the sensor until the output is not clipped, distorted and
safe enough.

![Wave](/img/wave.png)

#### 1. Determine the appropriate sensitivity value

Open the [calibrate.ino](/examples/calibrate/calibrate.ino) example and change
the `ACTUAL_VOLTAGE` value according to the actual AC voltage value (eg based on
a measurement with a voltmeter or something else). Upload the code then open
serial monitor. Wait until the `sensitivity` value is displayed and then copy it.

#### 2. Start measurement

Open either the [simple_usage.ino](/examples/simple_usage/simple_usage.ino) example
then change the `SENSITIVITY` value (seventh line) based on the value you got in
the previous process or use the alternate constructor in the [alternate_usage.ino](/examples/simple_usage/alternate_usage.ino)
example to set the sensitivity in the sensor constructor. Upload the code then open
the serial monitor to observe the displayed voltage value.
