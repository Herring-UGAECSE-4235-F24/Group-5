#include <stdlib.h>
#include <stdio.h>
#include "bcm2835.h"
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <ctype.h>


//gcc -o I2C_read I2C_read.c -lbcm2835 -Wall for compile



/* Useful Addresses
 * Address 00, Seconds (00-59)
 * Address 01, Minutes (0-59)
 * Address 02, Hours (1-12)
 * Address 03, Day (1-7)
 * Address 04, Date (01-31)
 * Address 05, Month (01-12)
 * Address 06, Year (00-99)
 * 
 * Address 0F, bit 3 to enable 32khz 
 */

// READ = 0;
// WRITE = 1;
int length = 38; //Number of bytes to be transmitted or received.
char buf[32];
char wbuf[32];
uint8_t slave_address = 0x68;
uint8_t mode = 0;
uint8_t data;
int values[38];



int main(){
     if(!bcm2835_init()){
                return 1;
        }
      
       
//===================== Read ===========================\\  
    
       bcm2835_i2c_setSlaveAddress(slave_address);
       bcm2835_i2c_set_baudrate(100000);
        if(!bcm2835_i2c_begin()){
                printf("I2C did not start");
        }
        
        for(int i = 1; i<length; i++) buf[i] = 'n';
        data = bcm2835_i2c_read(buf,length);
        //printf("Read Result = %d\n", data);
        for(int i = 1; i<length; i++) {
                if(buf[i] != 'n') {
                  int upper = buf[i] & 0xF0;
                  upper = (upper>>4);
                  upper = upper*10;
                  int lower = buf[i] & 0x0F; 
                  int value = upper+lower;
                  values[i] = value;
                // printf("Buf = %d\n", value);
                  //printf("Read Buf[%d] = %d\n", i, buf[i]);
                  
                }
        }
       printf("Date in MM/DD/YY is: %02d/%02d/%02d\n", values[5],values[4], values[6]);
        printf("Current Time in HH:MM:SS is: %02d:%02d:%02d\n",values[2], values[1], values[19]);
       bcm2835_i2c_end();
//

        
       
        

        
        
       
        

  
        
        
        
       
        
}
        
        

  
        
        
        
       
        

