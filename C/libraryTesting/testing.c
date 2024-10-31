#include <stdio.h>
#include <stdlib.h>
#include "bcm2835.h"
#include <unistd.h>


#define PIN1 RPI_GPIO_P1_11
#define PIN2 RPI_GPIO_P1_15
//gcc testing.c -o testing E4235_Read.s E4235_Select.s E4235_Write.s E4235_DelayMicro.s -Wall 
 // Set the pin to be an output to test read
extern int E4235_Read (int GPIO);
extern int E4235_Select (int GPIO, int state);
extern int E4235_Write (int GPIO, int state);
extern void E4235_DelayMicro ( int count );

int main(){

	
	E4235_Select(22,0);          // 0 for input    
	E4235_Select(17,1);  		  // 1 for output

	int read = 0;
	while(1){
	
	E4235_Write(17, 1);
	read = E4235_Read(22);
	printf("%d\n", read);
	
	E4235_DelayMicro(5000000);
	E4235_Write(17, 0);
	
	read = E4235_Read(22);
	printf("%d\n", read);
	E4235_DelayMicro(5000000);
	
	}
	
}
