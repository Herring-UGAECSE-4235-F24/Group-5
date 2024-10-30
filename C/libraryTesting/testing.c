#include <stdio.h>
#include <stdlib.h>
#include "bcm2835.h"
#include <unistd.h>

#define PIN RPI_GPIO_P1_11
//gcc testing.c -o testing E4235_Read.s
 // Set the pin to be an output to test read
extern int E4235_Read ( int GPIO);
int main(){
	if(!bcm2835_init()){
		return 1;
	}
	
	bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_OUTP);
	int freq;
    	printf("Enter Freq in Hz: ");
    	if (scanf("%d", &freq) != 1) {
        	printf("Error: Invalid input\n");
        	exit(1);
    	}
	 
	printf("your freq is %d", freq);

	while(1){
	bcm2835_gpio_write(PIN , HIGH); //1 = high
    if(E4235_Read(16)){
        printf("HIGH");
    } else {
        printf("LOW");
    }

	bcm2835_delayMicroseconds(1);		//delay in mils
	
	bcm2835_gpio_write(PIN , LOW); //0 = low
	 if(E4235_Read(16)){
        printf("HIGH");
    } else {
        printf("LOW");
    }
	bcm2835_delayMicroseconds(1);
	}
	
}
