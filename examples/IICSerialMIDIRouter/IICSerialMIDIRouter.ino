/*
// Simple DIY Electronic Music Projects
//    diyelectromusic.wordpress.com
//
//  DFRobot Gravity IIC to Dual UART Serial MIDI Transport Example
//  
//
      MIT License
      
      Copyright (c) 2022 diyelectromusic (Kevin)
      
      Permission is hereby granted, free of charge, to any person obtaining a copy of
      this software and associated documentation files (the "Software"), to deal in
      the Software without restriction, including without limitation the rights to
      use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
      the Software, and to permit persons to whom the Software is furnished to do so,
      subject to the following conditions:
      
      The above copyright notice and this permission notice shall be included in all
      copies or substantial portions of the Software.
      
      THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
      IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
      FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
      COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHERIN
      AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
      WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
/*
  Using principles from the following:
     Arduino MIDI Library: https://github.com/FortySevenEffects/arduino_midi_library
     DFRobot IICSerial: https://github.com/DFRobot/DFRobot_IICSerial 
*/
#include <MIDI.h>
#include <DFRobot_IICSerial.h>
#include <IICSerialMIDI.h>

// Taken from the DFRobot_IICSerial dataTxAndRx example code
DFRobot_IICSerial iicSerial1(Wire, /*subUartChannel =*/SUBUART_CHANNEL_1,/*IA1 = */1,/*IA0 = */1);//Construct UART1
DFRobot_IICSerial iicSerial2(Wire, /*subUartChannel =*/SUBUART_CHANNEL_2, /*IA1 = */1,/*IA0 = */1);//Construct UART2

// Initialise the two MIDI transports
IICSERIAL_MIDI_CREATE_INSTANCE(DFRobot_IICSerial, iicSerial1, MIDI1);
IICSERIAL_MIDI_CREATE_INSTANCE(DFRobot_IICSerial, iicSerial2, MIDI2);

void setup() {
  MIDI1.begin(MIDI_CHANNEL_OMNI);
  MIDI1.turnThruOff();
  MIDI2.begin(MIDI_CHANNEL_OMNI);
  MIDI2.turnThruOff();
}

void loop() {
  // Send any data received on UART 1 to UART 2
  if (MIDI1.read()) {
    MIDI2.send(MIDI1.getType(),
               MIDI1.getData1(),
               MIDI1.getData2(),
               MIDI1.getChannel());
  }
  // Send any data received on UART 2 to UART 1
  if (MIDI2.read()) {
    MIDI1.send(MIDI2.getType(),
               MIDI2.getData1(),
               MIDI2.getData2(),
               MIDI2.getChannel());
  }
}
