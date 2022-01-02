# Arduino iicSerial MIDI Transport
I2C/IIC MIDI Transport for use with the Arduino MIDI Library and DFRobot IIC UART module.

This library implements a IIC/I2C Serial MIDI transport layer for the [FortySevenEffects Arduino MIDI Library](https://github.com/FortySevenEffects/arduino_midi_library) for use with the [DFRobot Gravity IIC to Dual UART module](https://wiki.dfrobot.com/Gravity%3A%20IIC%20to%20Dual%20UART%20Module%20SKU%3A%20DFR0627)

*Warning: This is a very draft implementation.  Use at your own risk!*

## Installation

This library depends on the [Arduino MIDI Library](https://github.com/FortySevenEffects/arduino_midi_library) and [DFRobot's IIC to Dual UART Library](https://github.com/DFRobot/DFRobot_IICSerial).

## Usage
### Basic / Default
```cpp
#include <MIDI.h>
#include <DFRobot_IICSerial.h>
#include <IICSerialMIDI.h>

DFRobot_IICSerial iicSerial1(Wire, SUBUART_CHANNEL_1,1,1);

IICSERIAL_MIDI_CREATE_INSTANCE(DFRobot_IICSerial, iicSerial1, MIDI);

...
IICSERIAL_MIDI_CREATE_INSTANCE();
...
void setup()
{
   MIDI.begin(1);
...
void loop()
{
   MIDI.read();
```
will create a instance named `MIDI` using UART 1 listening on MIDI channel 1.

Note: By default Software MIDI THRU is enabled.  You can turn it off using turnThruOff().

### Provided Example

The included example 'IICSerialMIDIRouter' shows how to use both serial ports and will send any MIDI messages received on UART 1 to UART 2 and vice versa.

Each UART port should be connected to a 5V MIDI IN/OUT module, as if you've connected it directly to an Arduino's built-in hardware serial port.

For more details, refer to the following blog post: [Arduino I2C MIDI Interface](https://diyelectromusic.wordpress.com/2022/01/02/arduino-i2c-midi-interface/)

Kevin
@diyelectromusic
