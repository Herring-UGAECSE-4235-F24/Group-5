#include <stdio.h>
#include <bcm2835.h>
#include <unistd.h>
#include <stdint.h>


int main(){
	int freq = 0;
	printf("Enter frequency: ");
	scanf("%d", &freq); //read int for freq

	while(1){
	E4235_Write(4, HIGH);
	sleep(1/freq);
	E4235_Write(4, LOW);
	}
}
