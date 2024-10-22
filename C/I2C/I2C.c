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

void getTime(){
    time_t rawTime;
    struct tm *timeInfo;

    // Get the current time as raw time
    time(&rawTime);

    // Convert to local time
    timeInfo = localtime(&rawTime);

    // Store each component in separate variables
    char day[10], month[10];
    int date, hours, minutes, seconds, year;

    // Fill the substrings/variables with the appropriate values
    strftime(day, sizeof(day), "%A", timeInfo);    // Day (e.g., "Tuesday")
    strftime(month, sizeof(month), "%B", timeInfo); // Month (e.g., "October")
    date = timeInfo->tm_mday;                      // Date (e.g., 22)
    hours = timeInfo->tm_hour;                     // Hours (e.g., 14)
    minutes = timeInfo->tm_min;                    // Minutes (e.g., 30)
    seconds = timeInfo->tm_sec;                    // Seconds (e.g., 00)
    year = timeInfo->tm_year + 1900;               // Year (e.g., 2024)

    printf("Day: %s\n", day);
    printf("Month: %s\n", month);
    printf("Date: %d\n", date);
    printf("Time: %02d:%02d:%02d\n", hours, minutes, seconds);
    printf("Year: %d\n", year);

}

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
        
