//#include "E4235.h"
#include <stdio.h>
//gcc blinkClass.c -o blinkClass -lE4235
//gcc blinkClass.c -o blinkClass E4235_Delaynano.s E4235_Select.s E4235_Write.s
extern int E4235_Write ( int GPIO, int state );
extern int E4235_Select ( int GPIO, int state );
extern void E4235_DelayMicro ( int count );

int main() {
E4235_Select(17, 1); // set GPIO 17 to output

while (1) {
	E4235_Write(17, 1);
	
	E4235_DelayMicro(50);
	
	E4235_Write(17, 0);
	
	E4235_DelayMicro(50);
	
}
return 0;
}
