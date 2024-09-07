#include <stdio.h>
#include <bcm2835.h>
#include <unistd.h>
#include <gpiotopin.h>
//gcc -o blinkBcm2835 blinkBcm2835.c -lbcm2835 for compile

int main(){
	double freq = 0;
	printf("Enter frequency: ");
	scanf("%d", &freq); //read int for freq

	while(1){
	bcm2835_gpio_write(4, 1); //1 = high
	sleep(1/freq);
	bcm2835_gpio_write(4, 0); //0 = low
	}
}
