#include <stdio.h>
#include <stdlib.h>
#include "bcm2835.h"
#include <unistd.h>


#define PIN1 RPI_GPIO_P1_11
#define PIN2 RPI_GPIO_P1_15
//gcc testing.c -o testing E4235_Read.s E4235_Select.s -Wall -lbcm2835
 // Set the pin to be an output to test read
extern int E4235_Read (int GPIO);
extern int E4235_Select (int GPIO, int state);

int main(){
	if(!bcm2835_init()){
		return 1;
	}
	
	//E4235_Select(22,0);          // 0 for input    
	bcm2835_gpio_fsel(PIN1, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(PIN2, BCM2835_GPIO_FSEL_INPT);
	int read = 0;
	while(1){
	bcm2835_gpio_write(PIN1 , HIGH); //1 = high
	
	bcm2835_delayMicroseconds(5000000);		//delay in mils
	//read = E4235_Read(22);
	//read = bcm2835_gpio_lev(PIN2);
	printf("%d\n", read);
	
	bcm2835_gpio_write(PIN1 , LOW); //0 = low
	//read = E4235_Read(22);
	read = bcm2835_gpio_lev(PIN2);
	printf("%d\n", read);
	bcm2835_delayMicroseconds(5000000);
	
	}
	
}
