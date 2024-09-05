#include <stdio.h>
#include "bcm2835.h"
#include <unistd.h>


int main(){
	int freq = 0;
	printf("Enter frequency: ")
	scanf("%d", &freq) //read int for freq

	while(true){
	bcm2835_gpio_write(4, HIGH);
	sleep(1/freq);
	bcm2835_gpio_write(4, LOW);
	}
}
