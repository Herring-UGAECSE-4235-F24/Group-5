#include <stdio.h>
#include <stdlib.h>
#include "bcm2835.h"
#include <unistd.h>


#define PIN RPI_GPIO_P1_11
//gcc testing.c -o testing E4235_Read.s -Wall -lbcm2835
 // Set the pin to be an output to test read
extern int E4235_Read (int GPIO);
extern int E4235_Read (int GPIO, int state);
int main(){
	if(!bcm2835_init()){
		return 1;
	}
	
    E4235_Select(16,0);          // 0 for input    
	bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_OUTP);
	int read = 0;
	while(1){
	bcm2835_gpio_write(PIN , HIGH); //1 = high
	
	bcm2835_delayMicroseconds(5000000);		//delay in mils
	read = E4235_Read(16);
	printf("%d", read);
	
	bcm2835_gpio_write(PIN , LOW); //0 = low
	
	bcm2835_delayMicroseconds(5000000);
	read = E4235_Read(16);
	printf("%d", read);
	printf("next loop\n");
	}
	
}
