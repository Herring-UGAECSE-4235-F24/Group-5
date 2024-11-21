#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include "bcm2835.h"
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "I2CDriver.h"

//gcc -o I2CRTC I2CRTC.c -Wall E4235_DelayMicro.s E4235_Select.s E4235_Write.s E4235_Read.s I2CDriver.c

void I2C_Write(char * wbuf);
void I2C_Read(char * rbuf);

//Variables from I2C handles getting the time
char rbuf[19];
char wbuf[19];

uint8_t data;

char days[100], months[100];
int date, hours, minutes, seconds, year;
struct tm *timeData; //Time struct to handle time

//Converts days of the week to numbers
int dayNum(const char * day){
  char num[100];
  strcpy(num, day);
  if(strcmp(num, "Tuesday") == 0) return 03;
  else if(strcmp(num, "Wednesday") == 0) return 04;
  else if(strcmp(num, "Thursday") == 0) return 05;
  else return 0;
  
}


//Converts months to numbers
int monthNum(const char * month){
  char num[100];
  strcpy(num, month);
  if(strcmp(num, "October") == 0) return 10;
  if(strcmp(num, "November") == 0) return 11;
  else return 0;
  
  
  
}


//get time method that gets time
void getTime(){
    time_t rawTime;

    // Get the current time as raw time
    time(&rawTime);

    // Convert to local time
    timeData = localtime(&rawTime);

    
    
    // Fill the variables with the appropriate values
    strftime(days, sizeof(days), "%A", timeData);    // Day 
    strftime(months, sizeof(months), "%B", timeData);// Month 
    date = timeData->tm_mday;                      // Date 
    hours = timeData->tm_hour;                     // Hours 
    minutes = timeData->tm_min;                    // Minutes
    seconds = timeData->tm_sec;                    // Seconds 
    year = timeData->tm_year + 1900;               // Year since 1900 so add 1900
    
    
  

}



int main(){
    
 while(1) {
        printf("Enter a command for read = r and write = w ");
        char input = getchar();
        getchar(); //gets rid of the newline so the next getChar works properly

        if (input == 'r') {      // User chooses read
            I2C_Read(rbuf);
        } 
        else if (input == 'w') { // User chooses auto write
        //============ Handles Time parsing ================
            getTime();
            int day = dayNum(days);
            int month = monthNum(months);
        
        //After getting time assign statements  
            wbuf[0] = 0x00; //Word address to start
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

            printf("Day: %s\n", days);
            printf("Month: %s\n", months);
            printf("Date: %d\n", date);
            printf("Time: %02d:%02d:%02d\n", hours, minutes, seconds);
            printf("Year: %d\n", year); 
            printf("\n");

            I2C_Write(wbuf);
        }
      
    }
    return 0;
}
