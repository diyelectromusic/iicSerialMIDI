/*!
 *  @file       IICserialMIDI.h
 *  @license    MIT - Copyright (c) 2022 Kevin (@diyelectromusic)
 *  @author     Kevin, Francois Best
 *  @date       01/02/22
 *
 *  Based on:
 *  @file       serialMIDI.h
 *  Project     Arduino MIDI Library
 *  @brief      MIDI Library for the Arduino - Platform
 *  @license    MIT - Copyright (c) 2015 Francois Best
 *  @author     lathoub, Francois Best
 *  @date       22/03/20
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#pragma once
#include <MIDI.h>
using namespace MIDI_NAMESPACE;

#include "IICSerialMIDI_Namespace.h"

BEGIN_IICSerialMIDI_NAMESPACE

struct DefaultIICSerialSettings
{
    /*! Override the default MIDI baudrate to transmit over USB serial, to
    a decoding program such as Hairless MIDI (set baudrate to 115200)\n
    http://projectgus.github.io/hairless-midiserial/
    */
    static const long BaudRate = 31250;
};

template <class IICSerialPort, class _Settings = DefaultIICSerialSettings>
class IICSerialMIDI
{
    typedef _Settings Settings;

public:
	IICSerialMIDI(IICSerialPort& inIICSerial)
        : mIICSerial(inIICSerial)
	{
	};

public:
    static const bool thruActivated = true;
    
    void begin()
	{
        // Initialise the Serial port
        #if defined(AVR_CAKE)
            mIICSerial. template open<Settings::BaudRate>();
        #else
            mIICSerial.begin(Settings::BaudRate);
        #endif
	}

	bool beginTransmission(MidiType)
	{
		return true;
	};

	void write(byte value)
	{
		mIICSerial.write(value);
	};

	void endTransmission()
	{
	};

	byte read()
	{
		return mIICSerial.read();
	};

	unsigned available()
	{
        return mIICSerial.available();
	};

private:
    IICSerialPort& mIICSerial;
};

/*! \brief Create an instance of the library attached to a serial port.
 You can use iicSerial1 or iicSerial2 for the serial port.
 Example: MIDI_CREATE_INSTANCE(DFRobot_IICSerial, iicSerial2, midi2);
 Then call midi2.begin(), midi2.read() etc..
 */
#define IICSERIAL_MIDI_CREATE_INSTANCE(Type, IICSerialPort, Name)  \
    IICSerialMIDI_NAMESPACE::IICSerialMIDI<Type> IICserial##Name(IICSerialPort);\
    MIDI_NAMESPACE::MidiInterface<IICSerialMIDI_NAMESPACE::IICSerialMIDI<Type>> Name((IICSerialMIDI_NAMESPACE::IICSerialMIDI<Type>&)IICserial##Name);

/*! \brief Create an instance of the library attached to a serial port with
 custom settings.
 @see DefaultSettings
 @see MIDI_CREATE_INSTANCE
 */
#define IICSERIAL_MIDI_CREATE_CUSTOM_INSTANCE(Type, IICSerialPort, Name, Settings)           \
    IICSerialMIDI_NAMESPACE::IICSerialMIDI<Type, Settings> IICserial##Name(IICSerialPort);\
    MIDI_NAMESPACE::MidiInterface<IICSerialMIDI_NAMESPACE::IICSerialMIDI<Type, Settings>> Name((IICSerialMIDI_NAMESPACE::IICSerialMIDI<Type, Settings>&)IICserial##Name);

END_IICSerialMIDI_NAMESPACE
