#include <stdio.h>
#include <stdlib.h>
#include "bcm2835.h"
#include <unistd.h>

#define PIN RPI_GPIO_P1_03
//gcc -o blinkBcm2835 blinkBcm2835.c -lbcm2835 -Wall for compile
 // Set the pin to be an output

int main(){
	bcm2835_gpio_fsel(PIN, bcm2835.BCM2835_GPIO_FSEL_OUTP);
	int freq;
    	printf("Enter Freq in Hz: ");
    	if (scanf("%d", &freq) != 1) {
        	printf("Error: Invalid input\n");
        	exit(1);
    	}

	printf("your freq is %d", freq);

	while(1){
	bcm2835_gpio_write(PIN , bcm2835.HIGH); //1 = high

	bcm2835_delay(500);		//delay in mils
	
	bcm2835_gpio_write(PIN , bcm2835.LOW); //0 = low
	}
}
