#include <stdio.h>
#include <stdlib.h>
#include <bcm2835.h>
#include <unistd.h>

//gcc -o blinkBcm2835 blinkBcm2835.c -lbcm2835 -Wall for compile

int main(){
	int freq;
    	printf("Enter Freq in Hz: ");
    	if (scanf("%d", &freq) != 1) {
        	printf("Error: Invalid input\n");
        	exit(1);
    	}

	printf("your freq is %d", freq);
	
	while(1){
	//bcm2835_gpio_write(4, 1); //1 = high
	usleep(freq);
	//bcm2835_gpio_write(4, 0); //0 = low
	}
}
