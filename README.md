# AT24CXX library for Arduino

## ABOUT

This library contains functions for writing, reading and updating bytes in EEPROM chip.

Supported chips: <b>AT24C32</b> and <b>AT24C64</b> over <b>I2C</b> bus.

The library includes an example how to use every function.

Supports writing/reading values up to 32bits/4 bytes.

<br/><br/>

## INSTALATION

<ul>
  <li>Download the library</li>
  <li>Extract files using WinRAR(or similar software) to location <i>C:\Users\{YOUR_USERNAME}\Documents\Arduino\libraries</i></li>
  <li>Extend <i>BUFFER_LENGTH</i> from 32 bytes to 34(or more if you want). Macro <i>BUFFER_LENGTH</i> is in <i>Wire.h</i> file.</li>
</ul>

<br/><br/>

## USING LIBRARY

In your sketch, add `#include <AT24CXX.h>`. Now, the library is included. In `setup()` put `EEPROM.init` and provide chip information. See given example for more.

<br/><br/>

## SETTINGS

Settings listed below change in `AT24CXX.h` file.

<ul>
  <li><b>DEFAULT_WR_DELAY</b> - After every write cycle comes delay. Delay is required to make sure that the EEPROM chip has enough time to complete write cycle. Recommended value is between 2 and 10 miliseconds. Check chip's datasheet to see recommended delay.</li>
  <li><b>DEFAULT_PAGES</b> - AT24CXX EEPROM chip is organized with pages. Page size is in bytes. Page size is 32 bytes.</li>
  <li><b>DEFAULT_ADDRESS</b> - Default I2C address of the chip. Default address is <i>0x57</i></li>
</ul>

<br/><br/>

## FUNCTIONS

### void init(uint8_t address, uint8_t page, uint8_t delay)

Initialize EEPROM object. Use only in `setup()`.

<b>Parameters</b>
<ul>
  <li><b>address</b> - I2C address of EEPROM chip</li>
  <li><b>page</b> - Page size in bytes</li>
  <li><b>delay</b> - Delay after write cycle in miliseconds</li>
</ul>

<b>Return</b>
<ul>
  <li>Nothing</li>
</ul>

<br/>

### inline uint8_t getAddress()

Returns I2C address of the chip.

<b>Parameters</b>
<ul>
  <li>None</li>
</ul>

<b>Return</b>
<ul>
  <li>8-bit value</li>
</ul>

<br/>

### inline uint8_t getDelay()

Returns delay duration in miliseconds.

<b>Parameters</b>
<ul>
  <li>None</li>
</ul>

<b>Return</b>
<ul>
  <li>8-bit value</li>
</ul>

<br/>

### void writePage(uint16_t const address, char \*data, uint8_t len)

Writes array of data using write-page method.

<b>NOTE:</b> Be careful when allocating addresses for data. This function will overwrite all bytes between addresses @address and @address+@len.

<b>Parameters</b>
<ul>
  <li><b>address</b> - EEPROM address of the first byte</li>
  <li><b>data</b> - Data in bytes to write</li>
  <li><b>len</b> - Length of `data` in bytes</li>
</ul>

<b>Return</b>
<ul>
  <li>Nothing</li>
</ul>

<b>Snippet</b>
<ul>
  <li>pageWrite(address, data)</li>
</ul>

<b>Snippet parameters</b>
<ul>
  <li><b>address</b> - EEPROM address of the first byte</li>
  <li><b>data</b> - Data in bytes to write</li>
</ul>

<br/>

### void write(uint16_t address, uint32_t const value, uint8_t const len)

Writes @len-byte @value at @address in EEPROM.

<b>NOTE:</b> Be careful when allocating addresses for data. This function will overwrite all bytes between addresses @address and @address+@len.

<b>Parameters</b>
<ul>
  <li><b>address</b> - Address of the first byte in the EEPROM</li>
  <li><b>value</b> - Value to write</li>
  <li><b>len</b> - Length of @value in bytes</li>
</ul>

<b>Return</b>
<ul>
  <li>Nothing</li>
</ul>

<br/>

### uint32_t read(uint16_t const address, uint8_t const len)

Reads @len bytes from the EEPROM and returns one value.

<b>Parameters</b>
<ul>
  <li><b>address</b> - EEPROM address of the first byte</li>
  <li><b>len</b> - Length of value in bytes</li>
</ul>

<b>Return</b>
<ul>
  <li>Value from bytes between @address and @address+@len </li>
</ul>

<br/>

### bool update(uint16_t const address, uint32_t const value, uint6_t const len)

Writes @value only if @value is different from value at @address

<b>Parameters</b>
<ul>
  <li><b>address</b> - EEPROM address of the first byte</li>
  <li><b>value</b> - Value to write in the EEPROM</li>
  <li><b>len</b> - Length of @value in bytes</li>
</ul>

<b>Return</b>
<ul>
  <li><b>False</b> - Value has not been updated</li>
  <li><b>True</b> - Value has been updated</li>
</ul>