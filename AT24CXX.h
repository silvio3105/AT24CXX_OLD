
/*

	EEPROM FUNCTIONS
	AT24C32 & AT24C64 CHIPS
	ARDUINO
    LAST UPDATE: 25. 9. 2019.
    CREDITS: Pararera (c)

    *** WARNING - If writePage function doesn't work properly, extend Wire BUFFER_LENGTH by two(2) bytes. 99% you will have to.
	BUFFER_LENGTH macro is in Wire.h file. ***

*/

#ifndef _AT24CXX_H
#define _AT24CXX_H


// MODULES
#include 																			<Arduino.h>
#include 																			<Wire.h>


// SETTINGS
/*
	Default delay after writing data onto EEPROM chip
	@values: 2-10
	@unit: ms
*/
#ifndef DEFAULT_WR_DELAY
	#define DEFAULT_WR_DELAY															5
#endif

/*
	Default page size of EEPROM chip
	@values: 32 only!
*/
#define DEFAULT_PAGES         														32


/*
	Default I2C address of EEPROM chip 
*/
#ifndef DEFAULT_ADDRESS
	#define DEFAULT_ADDRESS 															0x57
#endif


// BUFFER_LENGTH CHECK
#if BUFFER_LENGTH < (DEFAULT_PAGES + 2)
	#error "BUFFER_LENGTH is smaller than it should be. Extend it!"
#endif


// MACRO FUNCTION
#define pageWrite(address, data) \
	EEPROM.writePage(address, reinterpret_cast<char*>(&data[0]), sizeof(data))



// CLASS
class AT24CXX {
public:
	// OBJECT CONSTRUCOTR
	AT24CXX();

	/*
		Sets I2C address of EEPROM chip
		@params:
			- address: I2C address of EEPROM chip
			- delay: Delay after write function 
	*/
	void init(uint8_t, uint8_t);

	/*
		Returns I2C address of EEPROM chip
		@return:
			- I2C address of EEPROM chip
	*/
	inline uint8_t getAddress() const;

	/*
		Returns write delay
		@return:
			- Duration of delay in ms after write function
	*/
	inline uint8_t getDelay() const;

	/*	
		Writes multiple bytes in the one go
		@params:
			- adress: EEPROM address of first byte
			- data: Data to write in EEPROM
			- len: Size of @data in bytes
	*/
	void writePage(uint16_t const, char*, uint8_t);

	/*
		Writes @len-byte @value in EEPROM at @address		
		@params:
			- adress: EEPROM address of first byte
			- value: Value to write in EEPROM
			- len: Size of @data (maximum 5 for 6-byte data and 4 for 8-byte data)
	*/
	void write(uint16_t, uint32_t const, uint8_t const);

	/*	
		Reads @len-byte value from @address in EEPROM
		If enabled, it will write only bytes that are different from previous value	
		@params:
			- adress: Data address in EEPROM
			- len: Size of @data
		@return:
			- Data from @address in EEPROM
	*/
	uint32_t read(uint16_t const, uint8_t const);


	/*	
		Writes @len-byte @value at given @address only if current value at @address is different from @value	
		@params:
			- adress: Address in EEPROM where data will be written
			- value: Value to write in EEPROM
			- len: Size of @data
		@return:
			- True: Value has been updated
			- False: Value has not been updated
	*/
	bool update(uint16_t const, uint32_t const, uint8_t const);


private:

	// Holds I2C address of AT24CXX chip
	uint8_t chipAddress;

	// Delay after write function
	uint8_t writeDelay;

	/*
		Writes bytes into EEPROM chip
		@params:
			- data: Data to write in EEPROM
			- len: Number of bytes that will be written into EEPROM
			- address: Address of first byte
			- onByte: Index of @data
	*/
	void writeBytes(char*, uint8_t, uint16_t&, uint16_t&);
};



// OBJECT
extern AT24CXX EEPROM;


#endif // _AT24CXX_H