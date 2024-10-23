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
int length = 20; //Number of bytes to be transmitted or received.
char buf[32];
char wbuf[32];
uint8_t slave_address = 0x68;
uint8_t mode = 0;
uint8_t data;

char days[100], months[100];
int date, hours, minutes, seconds, year;
struct tm *timeData;

int values[7];
int splitInt(int num){
  int tens = num/10;
  int output = tens<<4;
  int ones = num % 10;
  output = output | ones;
  return output;
  
}


int dayNum(const char * day){
  char num[100];
  strcpy(num, day);
  if(strcmp(num, "Tuesday") == 0) return 03;
  else if(strcmp(num, "Wednesday") == 0) return 04;
  else if(strcmp(num, "Thursday") == 0) return 05;
  else return 0;
  
}

int monthNum(const char * month){
  char num[100];
  strcpy(num, month);
  if(strcmp(num, "October") == 0) return 10;
  else return 0;
  
  
  
}

void getTime(){
    time_t rawTime;

    // Get the current time as raw time
    time(&rawTime);

    // Convert to local time
    timeData = localtime(&rawTime);

    // Store each component in separate variables
    
    // Fill the substrings/variables with the appropriate values
    strftime(days, sizeof(days), "%A", timeData);    // Day 
    strftime(months, sizeof(months), "%B", timeData);// Month 
    date = timeData->tm_mday;                      // Date 
    hours = timeData->tm_hour;                     // Hours 
    minutes = timeData->tm_min;                    // Minutes
    seconds = timeData->tm_sec;                    // Seconds 
    year = timeData->tm_year + 1900;               // Year since 1900 so add 1900
    
    
  

}

int main(){
     if(!bcm2835_init()){
                return 1;
        }
      
      
      
      getTime();
      int day = dayNum(days);
      int month = monthNum(months);
  
      wbuf[0] = 00; //Word address to start
      wbuf[1] = splitInt(seconds);
      wbuf[2] = splitInt(minutes);
      wbuf[3] = splitInt(hours);
      wbuf[4] = splitInt(day);
      wbuf[5] = splitInt(date);
      wbuf[6] = splitInt(month);
      wbuf[7] = splitInt(year-2000);
      wbuf[8] = 0x00;
      wbuf[9] = 0x00;
      wbuf[10] = 0x00;
      wbuf[11] = 0x00;
      wbuf[12] = 0x00;
      wbuf[13] = 0x00;
      wbuf[14] = 0x00;
      wbuf[15] = 0x00;
      wbuf[16] = 0x08;                  //Bit three is set high to enable crysta oscillator
      wbuf[17] = 0x00;
      wbuf[18] = 0x00;
     // wbuf[19] = 0x00;
      
      printf("Day: %s\n", days);
      printf("Month: %s\n", months);
      printf("Date: %d\n", date);
      printf("Time: %02d:%02d:%02d\n", hours, minutes, seconds);
      printf("Year: %d\n", year); 
    
      
      

        
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
        
        for(int i = 1; i<length; i++) buf[i] = 'n';
        data = bcm2835_i2c_read(buf,length);
        printf("Read Result = %d\n", data);
        for(int i = 1; i<length; i++) {
                if(buf[i] != 'n') {
                  int upper = buf[i] & 0xF0;
                  upper = (upper>>4);
                  upper = upper*10;
                  int lower = buf[i] & 0x0F; 
                  int value = upper+lower;
                  values[i] = value;
                 //printf("Buf = %d\n", value);
                 // printf("Read Buf[%d] = %d\n", i, buf[i]);
                  
                }
        }
        printf("Date in MM/DD/YY is: %d/%d/%d\n", values[6],values[5], values[7]);
        printf("Current Time in HH:MM:SS is: %d:%d:%d\n",values[3], values[2], values[1]);
       
       
       //while(1){
      //   int random_time = rand()% 60; //a random delay before reads of 0-60 seconds for testing
      //   printf("%d", random_time);
         
//}
       
        bcm2835_i2c_end();
     
//

        
       
        

        
        
       
        

  
        
        
        
       
        
}
        
