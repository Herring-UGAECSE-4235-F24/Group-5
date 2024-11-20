#include <stdio.h>
#include "E4235.h"
#include <sys/time.h>
#include <time.h>
#include "bcm2835.h"
#include <string.h>
#include <unistd.h>
#include <ctype.h>

//gcc -o I2CDriver I2CDriver.c -l -Wall -E4235

/* Addresses
* Adress 00, Seconds(00-59)
* Adress 01, Minutes(0-59)
* Address 02, Hours(1-12)
* Address 03, Day (1-7)
* Address 04, Date (01-31)
* Address 05, Month (01-12)
* Address 06, Year (00-99)
*/

#define SDA 27		//GPIO pin for SDA
#define SCL 17 		//GPIO17 pin for SCL
#define DS3231 0x68 //I2C address for DS3231

char userPrompt() { //will modify
	printf("Would you like to read or write to the RTC? Input 'r' for read or 'w' for write: ");
	return scanf(); //will finish
}


//Composed main block into functions
//Need to account for addresses from the DS3231. Not finished yet will modify. Used your structure from past I2C.
//Have a couple methods to add/modify


void I2C_Init() { //initialize
	E4235_Select(SDA, 1);
	E4235_Select(SCL, 1);
}

void I2C_begin() { //begins the I2C. Delays are used for timing purposes.
	E4235_Write(SDA, 1);
	E4235_Write(SCL, 1);

	E4235_DelayMicro(10);
	E4235_Write(SDA, 0);

	E4235_DelayMicro(10);
	E4235_Write(SCL, 0);
}

void I2C_write(int bit) { //write bit. This method im using is bit banging as described. We read and write bits using class library. Then read/write the bytes.
	if (bit == 1) {
		E4235_Write(SDA, 1);
	}
	else {
	E4235_Write(SDA, 0);
	}
	
	E4235_Write(SCL, 1);
	E4235_DelayMicro(10);
	E4235_Write(SCL, 0);
	E4235_DelayMicro(10);
}

int I2C_read() { //reads the bits from pin
	E4235_Write(SCL, 1);
	E4235_Delay(10);
	
	int bit = E4235_Read(SDA);
	E4235_Write(SCL, 0);
	return bit;
}

void I2C_WriteByte(unit8_t byte) { //write byte
	for(int i = 7; i >= 0; i--) {
		I2C_Write((byte >> i) & 0x01); //accounts for registers in comments above
	}
}

unit8_t I2C_ReadByte() { //read byte
	unit8_t byte = 0;
	for(int i = ; i>=0; i--) {
		byte |= (I2C_Read() << i); //accounts for registers in comments above
	}
	return byte;
}

void I2C_stop() { //acts same as bcm end
	E4235_Write(SDA, 0);
	E4235_Write(SCL, 1);
	E4235_DelayMicro(10);
	E4235_Write(SDA, 1);
	E4235_DelayMicro(10);
}


int main() {
	userPrompt();

	//Initialize the GPIO pins and I2C. Not finished will continue.
	I2C_Init();
	
	I2C_start();	
}
