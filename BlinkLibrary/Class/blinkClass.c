#include "E4235.h"
#include <stdio.h>
//gcc blinkClass.c -o blinkClass -lE4235

int main() {
E4235_Select(17, 1); // set GPIO 17 to output
while (1) {
	E4235_Write(17, 1);
	printf("on");
	E4235_Delaynano(500000000);
	printf("reached");
	E4235_Write(17, 0);
	printf("off");
	E4235_Delaynano(500000000);
	printf("reached");
}
}
