#include <stdio.h>
#include <stdlib.h>
//as -o exponentialC.o exponentialC.s -mfpu=vfpv3 
//as -o factorialC.o factorialC.s  -mfpu=vfpv3 
//gcc series.c -o series -mfpu=vfpv3 exponentialC.o factorialC.o -lc -std=c99 -g

extern float exponentialC(float x, int n); 
extern float factorialC(float n);
//@ e^x = 1 + x+ x^2/2! + x^3/3! + x^4/4! + x^5/5!
int main() {
    printf("Calculate e^x.  Enter x: " );
    float x;
    scanf("%f", &x); // Use %f to read a double    
    float result = 1+x+((exponentialC(x,2))/(factorialC(2)))+((exponentialC(x,3)/factorialC(3)))+((exponentialC(x,4))/(factorialC(4)))+((exponentialC(x,5))/(factorialC(5)));
    printf("e^%f = %f\n", x, result);

    // float small = exponentialC(x,2);
    // float cat = exponentialC(x,3);
    // float dog = exponentialC(x,4);
    // float large = exponentialC(x,5);
    // printf("%f^n = %f\n, %f\n, %f\n, %f\n",x, small,cat,dog,large);

    
    // printf("x^2 = %f\n", cat);

    // float a = factorialC(2);
    // float b = factorialC(3);
    // float c = factorialC(4);
    // float d = factorialC(5);


    // printf("2! = %f\n 3! = %f\n 4! = %f\n 5! = %f\n", a,b,c,d);

    
    exit(0);
}