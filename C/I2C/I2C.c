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
int length = 8; //Number of bytes to be transmitted or received.
char buf[32];
char wbuf[32];
uint8_t slave_address = 0x68;
uint8_t mode = 0;
uint8_t data;

char day[100], month[100];
int date, hours, minutes, seconds, year;
struct tm *timeData;

void getTime(){
    time_t rawTime;

    // Get the current time as raw time
    time(&rawTime);

    // Convert to local time
    timeData = localtime(&rawTime);

    // Store each component in separate variables
    
    // Fill the substrings/variables with the appropriate values
    strftime(day, sizeof(day), "%A", timeData);    // Day 
    strftime(month, sizeof(month), "%B", timeData);// Month 
    date = timeData->tm_mday;                      // Date 
    hours = timeData->tm_hour;                     // Hours 
    minutes = timeData->tm_min;                    // Minutes
    seconds = timeData->tm_sec;                    // Seconds 
    year = timeData->tm_year + 1900;               // Year since 1900 so add 1900
    
    
  

}

int main(){
     
     
      getTime();
      wbuf[0] = 00; //Word address to start
      wbuf[1] = seconds;
      wbuf[2] = minutes;
      wbuf[3] = hours;
      wbuf[4] = 0;
      wbuf[5] = 0;
      wbuf[6] = 0;
      wbuf[7] = 0;
      
      printf("Day: %s\n", day);
      printf("Month: %s\n", month);
      printf("Date: %d\n", date);
      printf("Time: %02d:%02d:%02d\n", hours, minutes, seconds);
      printf("Year: %d\n", year); 
    
      
      
      
        if(!bcm2835_init()){
                return 1;
        }
        
        if(!bcm2835_i2c_begin()){
                printf("I2C did not start");
        }
        
        bcm2835_i2c_setSlaveAddress(slave_address);
        bcm2835_i2c_set_baudrate(100000);
        
        
        
        
        bcm2835_i2c_write(wbuf,length);
        bcm2835_i2c_end();
       
//===================== Read ===========================\\  
    
        //bcm2835_i2c_setSlaveAddress(slave_address);
       // bcm2835_i2c_set_baudrate(100000);
        
        if(!bcm2835_i2c_begin()){
                printf("I2C did not start");
        }
        
        for(int i = 0; i<32; i++) buf[i] = 'n';
        data = bcm2835_i2c_read(buf,32);
        printf("Read Result = %d\n", data);
        for(int i = 0; i<32; i++) {
                if(buf[i] != 'n') printf("Read Buf[%d] = %d\n", i, buf[i]);
        }
        bcm2835_i2c_end();
       
//

        
       
        

        
        
       
        

  
        
        
        
       
        
}
        
