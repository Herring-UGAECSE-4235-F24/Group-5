                                                                                                                                                                  >#include <stdlib.h>
#include "bcm2835.h"
#include <unistd.h>


//gcc -o blinkBcm2835 blinkBcm2835.c -lbcm2835 -Wall for compile


int main(){
        if(!bcm2835_init()){
                return 1;
        }
        bcm2835_i2c_setSlaveAddress();
        
        bcm2835_i2c_write();
        
        
        
        
}
        