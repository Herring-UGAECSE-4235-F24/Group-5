#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include "bcm2835.h"
#include <string.h>
#include <unistd.h>
#include <ctype.h>

//gcc -o I2CDriver I2CDriver.c -Wall E4235_DelayMicro.s E4235_Select.s E4235_Write.s E4235_Read.s

//Externs for class library calls
extern int E4235_Write ( int GPIO, int state );
extern int E4235_Select ( int GPIO, int state );
extern void E4235_DelayMicro ( int count );
extern int E4235_Read (int GPIO);


#define SDA 27		//GPIO pin for SDA
#define SCL 17 		//GPIO17 pin for SCL
#define DS3231 0x68 //I2C address for DS3231


//Starts the commuincation by sending a start signal
void start(){
	E4235_Select(SDA, 1); 
	E4235_Write(SDA, 0);
	E4235_Select(SDA, 0); 
	E4235_Select(SCL, 0); 
	E4235_Select(SDA, 1); 
	E4235_Select(SCL, 1);
	E4235_Select(SDA, 0); 
	E4235_Select(SCL, 0); 
}

//Stops the communication by sending a stop fucntion
void stop(){ 
	E4235_Select(SDA, 0);
	E4235_Select(SCL, 0);
	E4235_Select(SCL, 1);
	E4235_Select(SCL, 0);

	
}


//Split int function is how I split the integers to be sent to the rtc
int splitInt(int num){ 
  int tens = num/10;
  int output = tens<<4; //top 4 bits
  int ones = num % 10;
  output = output | ones; //sets the bits accurately
  return output;
  
}


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
	while(count >= 0) {
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
	//toggle data back high for idle
		E4235_Select(SDA, 0);
		
}

//Sets to read or write based on mode. 
//Mode 0 = read, Mode 1 = write
void init(int mode) { 
    //Sends a start 
	start();

	unsigned char address;
		address = reverse(0x68); 	//Sets address
		int count = 8;
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
	if(mode){
		E4235_Select(SDA, 1); //Write
		 //printf("Pins are now good to write\n");
	}
	else{
		E4235_Select(SDA, 0);
		//printf("Pins are now good to read\n");
	}
	E4235_Select(SCL, 0);
	E4235_Select(SCL, 1);

	//toggle clock again for ack
	E4235_Select(SCL, 0);
	E4235_Select(SCL, 1);
	E4235_Select(SDA, 0);
	
	

   
}
//writes all parts of buf to I2C line
void I2C_Write( char * wbuf){
	init(1);
	for(int i = 0; i < 19; i++){
		sendByte(wbuf[i]);
	}

	stop();
}




char readByte(){
	char byte;
	for(int i = 0; i<8; i++){
		E4235_Select(SCL, 0);
		char bit = E4235_Read(SDA);
		byte = byte<<1;
		byte = byte | bit;
		E4235_Select(SCL, 1);
	}
	
	//then for ack set data low
	E4235_Select(SDA, 1);
	E4235_Select(SCL, 0);
	E4235_Select(SCL, 1);
	//high for idle
	E4235_Select(SDA, 1);
	E4235_Write(SDA, 0);
	E4235_Select(SDA, 0);
	return byte;
}

void I2C_Read(char * rbuf) {
	init(0);
	int output[19];
	for(int i = 0; i<18; i++){
		rbuf[i] = readByte();	
	}

	for(int i = 0; i<18; i++){
		 int upper = rbuf[i] & 0xF0;
         upper = (upper>>4);
         upper = upper*10;
         int lower = rbuf[i] & 0x0F; 
         int value = upper+lower;
         output[i] = value;
	}

	// printf("seconds = %d/n", output[2]);
	// printf("minutes = %d/n", output[3]);
	// printf("hours = %d/n", output[4]);
	// printf("seconds = %d/n", output[5]);
	// printf("minutes = %d/n", output[6]);
	// printf("hours = %d/n", output[7]);
	printf("Date in MM/DD/YY is: %02d/%02d/%02d\n", output[7],output[6], output[8]);
    printf("Current Time in HH:MM:SS is: %02d:%02d:%02d\n",output[4], output[3], output[2]);
	printf("\n");

	


	

	E4235_Select(SCL, 0);
	E4235_Select(SCL, 1);
	E4235_Select(SCL, 0);
	E4235_Select(SCL, 1);
	E4235_Select(SCL, 0);
	E4235_Select(SCL, 1);
	E4235_Select(SCL, 0);
	E4235_Select(SCL, 1);
	E4235_Select(SCL, 0);
	E4235_Select(SCL, 1);
	E4235_Select(SCL, 0);
	E4235_Select(SCL, 1);
	E4235_Select(SCL, 0);
	E4235_Select(SCL, 1);
	E4235_Select(SCL, 0);
	E4235_Select(SCL, 1);
	E4235_Select(SCL, 0);
	E4235_Select(SCL, 1);

	stop();


}

