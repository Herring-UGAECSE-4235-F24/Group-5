#include "E4235.h"
#include <stdio.h>
//gcc blinkClass.c -o blinkClass -lE4235


int main() {
E4235_Select(17, 1); // set GPIO 17 to output
int pins[1] =	{17};
while (1) {
	E4235_multiwrite(17,1, 1);
	
	E4235_Delaynano(10000000);
	
	E4235_multiwrite(17,1, 0);
	
	E4235_Delaynano(10000000);

	

	
	
}
return 0;
}
