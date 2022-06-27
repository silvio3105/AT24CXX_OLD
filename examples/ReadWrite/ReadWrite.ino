
/*

	EXAMPLE HOW TO USE EEPROM READ-WRITE FUNCTIONS
	AT24C32 & AT24C64 CHIPS
	ARDUINO & STM32 BOARDS
    LAST UPDATE: 25. 9. 2019.
    CREDITS: Pararera (c)

	Tested on Arduino Nano R3(Old bootloader) and STM32F103C8 boards with AT24C32 EEPROM chip.
    BUFFER_LENGTH macro is in Wire.h file.

*/


#include 																			<AT24CXX.h>


void setup()
{
	delay(100);
	Serial.begin(9600);
	Wire.begin();
	randomSeed(analogRead(0));

	/* 
		0x57 is I2C address of EEPROM chip (depends on chip. It may be different for you)
		32 is size of EEPROM page in bytes (32 or 64 bytes, depends on the chip you have)
		5 is delay(ms) after write function (recommended value is 2-10ms)
	*/
	EEPROM.init(0x57, 5);		

	uint32_t bytes[20]; // 80 BYTES IN TOTAL
	uint8_t startAddress = random(0, 10);
	uint32_t tick = 0;

	Serial.print("->> GENERATING RANDOM NUMBERS: ");
	for (uint8_t i = 0; i < 20; i++)
	{
		bytes[i] = random(100000000, 555555555);
		Serial.print(bytes[i], DEC);
		if (i != 19) Serial.print(", ");
	}

	Serial.print("\n\n->> writePage function\nStart address: ");
	Serial.print(startAddress, DEC);
	Serial.print("\nWriting...\n");

	tick = millis();

	/*
		This function writes array of data using write-page method.
		Write-page method writes up to 32/64 bytes(depends on chip you have) in one go.
		After every written page, MCU freezes for X miliseconds.
		Original function is:
		EEPROM.writePage(address, reinterpret_cast<char*>(&data[0]), sizeof(data))
	*/	
	pageWrite(startAddress, bytes);

	Serial.print("- Done!\nTook ");
	Serial.print(millis() - tick, DEC);
	Serial.print("ms to complete writing using write-page method. Lets read those values!\n\n");
	Serial.print("->> Read function\nStart address: ");
	Serial.print(startAddress, DEC);
	Serial.print("\nValues: ");

	for (uint8_t i = 0; i < 20; i++)
	{
		/*
			This function reads N-bytes from EEPROM and returns one value.
			Function needs EEPROM address of first byte and length in bytes.
		*/
		Serial.print(EEPROM.read(startAddress + (4 * i), 4), DEC);
		if (i != 9) Serial.print(", ");		
	}

	uint32_t x = random(100000, 1000000);
	uint8_t address = random(70, 80);

	Serial.print("\n- Done!\n\nLets write ");
	Serial.print(x, DEC);
	Serial.print(" at address ");
	Serial.print(address, DEC);
	Serial.print(" using standard function.\n");

	/*
		Writes 4-byte value from @x to @address.
		It will write for bytes so byte on @address and three bytes at next three addresses will be overwritten.
		Be careful when allocating addresses.
	*/
	EEPROM.write(address, x, 8);

	Serial.print("- Done!\nLets read it! Value: ");
	Serial.print(EEPROM.read(address, 4), DEC);
	Serial.print("\nThat is how you use writePage, write and read functions.\nNow lets see how to use update function!\n\n->>Update function\n");

	uint8_t dice = random(100);
	bool updated = false;

	if (dice % 2 != 0) x = random(100000, 1000000); // ODD NUMBER - LETS CHANGE VALUE @x

	/*
		Update function first reads N-byte value from @address
		If value if different from @x(given value), it will write given value.
		If not, it will not write given value.
		Function also returns false(0) if it did not update the value, true(1) will return if value was updated.
	*/
	updated = EEPROM.update(address, x, 4);

	Serial.print("- Done!\n Lets see what happend.\n");
	if (updated) Serial.print("Value is updated! New value is ");
		else Serial.print("Value is not updated! Old value is ");

	Serial.print(EEPROM.read(address, 4), DEC);
	Serial.print("\n\n\nEEPROM I2C address: ");
	Serial.println(EEPROM.getAddress(), DEC);
	Serial.print("EEPROM write delay: ");
	Serial.println(EEPROM.getDelay(), DEC);

	Serial.println("\n\n\n\nDONE!\n\n\n");

	while (1) delay(10000);
}

void loop()
{

}