#include <stdio.h>
//#include "E4235.h"
#include <sys/time.h>
#include <time.h>
#include "bcm2835.h"
#include <string.h>
#include <unistd.h>
#include <ctype.h>

//gcc -o I2CDriver I2CDriver.c -Wall E4235_DelayMicro.s E4235_Select.s E4235_Write.s

extern int E4235_Write ( int GPIO, int state );
extern int E4235_Select ( int GPIO, int state );
extern void E4235_DelayMicro ( int count );

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

//function reverse bits in a byte in order to send MSB first
unsigned char reverse(unsigned char byte){
	unsigned char reversed = 0x00;

	for (int i = 0; i < 8; i++) {
        reversed = (reversed << 1) | (byte & 1);
        byte >>= 1;
    }
	return reversed;
}

void sendByte(unsigned char byte) { //write byte. This method is bit banging as described. We write bits using class library.
	byte = reverse(byte);
	int count = 8;
	while(count > 0) {
		int bit = byte & 1;		 //MSB of byte 
		byte = byte >> 1;		
		E4235_Select(SDA, !bit); //since active low 

		//A device must internally provide a hold time of at least 
		//300ns for the SDA signal according to data sheet
		
		E4235_Select(SCL, 0);	//sends next clock
		E4235_DelayMicro(1); //More than 300ns
		E4235_Select(SCL, 1);
		count--;
	}
	//toggle clock for acknowledge bit
		E4235_Select(SDA, 1);
		E4235_Select(SDA, 0);
		E4235_Select(SCL, 0);	//sends next clock
		E4235_DelayMicro(1); //More than 300ns
		E4235_Select(SCL, 1);
}

//Sets to read or write based on mode. 
//Mode 0 = read, Mode 1 = write
void init(int mode) { 
    //Sends a start 
	E4235_Select(SDA, 1); 
	E4235_Select(SCL, 1);
	E4235_Select(SDA, 0); 
	E4235_Select(SCL, 0);
	E4235_Select(SDA, 1); 
	E4235_Select(SCL, 1);
	unsigned char address;
	if(mode){
		address = reverse(0x6E); 	//Sets write
		int count = 7;
		while(count > 0) {
			int bit = address & 1;		 //MSB of byte 
			address = address >> 1;		
			E4235_Select(SDA, !bit); //since active low 

			//A device must internally provide a hold time of at least 
			//300ns for the SDA signal according to data sheet
			
			E4235_Select(SCL, 0);	//sends next clock
			E4235_DelayMicro(1); //More than 300ns
			E4235_Select(SCL, 1);
			count--;
		}

	}
	else{
		address = reverse(0x6E);		//Sets read
		sendByte(address);
	}

	

    printf("Pins are now floating\n");
}



//void I2C_read()

int main() {
init(1);

sendByte(0xFF);
sendByte(0xA3);

}