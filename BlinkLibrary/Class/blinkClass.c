#include "E4235.h"
#include <stdio.h>
int main() {
E4235_Select(11, 1); // set GPIO 12 to output
while (1) {
	E4235_Write(11, 1);
	E4235_Delaynano(500000);
	E4235_Write(11, 0);
	E4235_Delaynano(500000);
}
}
