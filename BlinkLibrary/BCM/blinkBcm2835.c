#include <stdio.h>
#include <bcm2835.h>
#include <unistd.h>

//gcc -o blinkBcm2835 blinkBcm2835.c -lbcm2835 -wall for compile

int main(){
	double freq;
	printf("Enter frequency: ");
	scanf("%lf", &freq); //read int for freq
	printf("made it to loop");
	while(1){
	bcm2835_gpio_write(4, 1); //1 = high
	usleep(1/frequency);
	bcm2835_gpio_write(4, 0); //0 = low
	}
}
