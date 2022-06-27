
/*

	EEPROM FUNCTIONS
	AT24C32 & AT24C64 CHIPS
	ARDUINO & STM32 BOARDS
    LAST UPDATE: 25. 9. 2019.
    CREDITS: Pararera (c)

    *** WARNING - If writePage function doesn't work properly, extend Wire BUFFER_LENGTH by two(2) bytes. 99% you will have to.
	BUFFER_LENGTH macro is in Wire.h file. ***

*/

// MODULES
#include 																			"AT24CXX.h"



// OBJECT
AT24CXX EEPROM;



// OBJECT CONSTRUCTOR
AT24CXX::AT24CXX()
{
	chipAddress = DEFAULT_ADDRESS;
	writeDelay = DEFAULT_WR_DELAY;	
}


// INIT FUNCTION
void AT24CXX::init(uint8_t address, uint8_t delay)
{
	chipAddress = address;
	writeDelay = delay;
}


// GET FUNCTIONS
inline uint8_t AT24CXX::getAddress() const
{
	return (chipAddress);
}

inline uint8_t AT24CXX::getDelay() const
{
	return (writeDelay);
}


// WRITE FUNCTION
void AT24CXX::write(uint16_t address, uint32_t const value, uint8_t const len)
{  
    Wire.beginTransmission(chipAddress);
	Wire.write(address >> 8);
	Wire.write(address & 0xFF);

    for (uint8_t i = 0; i < len; i++) Wire.write(((value >> 8 * i) & 0xFF));

    Wire.endTransmission();
    delay(writeDelay); // DO NOT DELETE
}

// PAGE WRITE FUNCTION
void AT24CXX::writePage(uint16_t address, char *data, uint8_t len)
{
	uint8_t pages = 0;
	uint8_t pageOffset = address % DEFAULT_PAGES;
	uint16_t onByte = 0;
	uint16_t startLen = len;

	if (pageOffset > 0) // PAGE OFFSET EXISTS
	{
		uint8_t excessLen = DEFAULT_PAGES - pageOffset;
		if (excessLen > len) excessLen = len;
		len -= excessLen;

		writeBytes(data, excessLen, address, onByte);
	}

	pages = len / DEFAULT_PAGES;
	if (pages > 0) // ONE OR MORE WHOLE PAGES EXIST
	{
		uint8_t onPage = 0;

		// PAGE LOOP
		while(onPage < pages)
		{
			writeBytes(data, DEFAULT_PAGES, address, onByte);

			onPage++;
			len -= DEFAULT_PAGES;
		}
	}

	if (len > 0) writeBytes(data, len, address, onByte); // LEFTOVER
}


// WRITE BYTES
void AT24CXX::writeBytes(char *data, uint8_t len, uint16_t &address, uint16_t &onByte)
{
	uint8_t i = 0;

	Wire.beginTransmission(chipAddress);
	Wire.write(address >> 8);
	Wire.write(address & 0xFF);

	do
	{
		Wire.write(data[onByte++]);
		address++;
		i++;
	}
	while(i < len);

    Wire.endTransmission();
    delay(writeDelay); // DO NOT DELETE
}


// READ FUNCTION
uint32_t AT24CXX::read(uint16_t const address, uint8_t const len)
{
	uint32_t value = 0;

	Wire.beginTransmission(chipAddress);
	Wire.write(address >> 8);
	Wire.write(address & 0xFF);
    Wire.endTransmission();
	Wire.requestFrom(chipAddress, len);

    for (uint8_t i = 0; i < len; i++)
    {
        if (Wire.available()) value += ((Wire.read() << i * 8) & static_cast<uint32_t>(pow(2, 8 * (i + 1)) - 1));
    }

	return (value);
}


// UPDATE FUNCTION
bool AT24CXX::update(uint16_t const address, uint32_t const value, uint8_t const len)
{
	if (read(address, len) != value)
	{
		write(address, value, len);
		return (true);
	}
	else return (false);
}