#include <stdlib.h>
#include <stdio.h>
#include "bcm2835.h"
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <ctype.h>


//gcc -o I2C I2C.c -lbcm2835 -Wall for compile



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
int length = 7; //Number of bytes to be transmitted or received.
char buf[32];
char wbuf[32]
uint8_t slave_address = 0x68;
uint8_t mode = 0;
uint8_t data;

int main(){
        

        if(!bcm2835_init()){
                return 1;
        }
        
        if(!bcm2835_i2c_begin()){
                printf("I2C did not start");
        }
       
/*       
        bcm2835_i2c_setSlaveAddress(slave_address);
        bcm2835_i2c_set_baudrate(100000);
        
  
        for(int i = 0; i<32; i++) buf[i] = 'n';
        data = bcm2835_i2c_read(buf,length);
        printf("Read Result = %d\n", data);
        for(int i = 0; i<32; i++) {
                if(buf[i] != 'n') printf("Read Buf[%d] = %x\n", i, buf[i]);
        }
        bcm2835_i2c_end();
        
*/

        
        struct tm* ptr;
        time_t t;
        t = time(NULL);
        ptr = localtime(&t);
        
        printf("%s", asctime(ptr));
        
       //char timeString[] = asctime(ptr);
        char test[] = strcpy(test, asctime(ptr));
        
        int stringLength = strlen(timeString);
        int count =0;
        while(count < stringLength) {
                int ws = isspace(stringLength);
                return ws;
        }

        
        
        bcm2835_i2c_begin();
        bcm2835_i2c_setSlaveAddress(slave_address);
        bcm2835_i2c_set_baudrate(100000);

  
        
        bcm2835_i2c_write(buf,length);
        bcm2835_i2c_end();
        
       
        
}
        
