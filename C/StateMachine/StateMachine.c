//Commented out because this is only used for Arduino IDE libraries which is what I was using. I created methods below that were included in the header file.
//#include <Keypad.h>
//#include "E4235.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "bcm2835.h"



//gcc StateMachine.c -o StateMachine E4235_DelayMicro.s E4235_Select.s E4235_Write.s E4235_Read.s E4235_PWM_Set.s E4235_PWM_Enable.s -lbcm2835 -Wall
extern int E4235_Write(int GPIO, int state);
extern int E4235_Select(int GPIO, int state);
extern int E4235_Read(int GPIO);
extern void E4235_DelayMicro(int count);
extern int E4235_PWM_Set ( int GPIO, int FREQ, int DUTY );
extern void E4235_PWM_Enable (int GPIO, int enable);
// Define the row and column pins
const int ROWS = 4; // Four rows
const int COLS = 4; // Four columns
const int rowPins[4] = {20, 17, 19, 23}; // Connect to the row pins of the keypad
const int colPins[4] = {24, 25, 26, 27};  // Connect to the column pins of the keypad
const int pins[4] = {RPI_GPIO_P1_18, RPI_GPIO_P1_22,   RPI_V2_GPIO_P1_37, RPI_V2_GPIO_P1_13};
const int outputPins[8] = {10, 4, 12, 18, 7, 15, 16, 17};
int pressed = 0;
char prev;


// Define the keymap
char keys[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};



//Read the Keypad
char keypadRead() {
  for (int i = 0; i < 4; i++) {
	  E4235_Write(rowPins[i], 1); //high output 1
	  for (int j = 0; j < 4; j++) {
	    if (bcm2835_gpio_lev(pins[j]) == 1) { //high output 1
        
		    //E4235_DelayMicro(20000); //debounce delay of tenth a second
		    if(bcm2835_gpio_lev(pins[j]) == 1) { //high output 1
			    E4235_Write(rowPins[i], 0); //low output 0
          char key = keys[i][j];
          if(key != '*'){
            if(key!='#'){
            prev = key;
            }
          pressed = 1;
          } else {
          pressed = 0;
          }
          return key;
		    }
	    }
    }
  E4235_Write(rowPins[i], 0); //low output 0
  }
return 0;
}

void asciiMode(char key){
 if(key == '\0'){
   key = '@';
 }
 int GPIO = 0;
 int ascii = key;
  while(GPIO<8){
    if(ascii>0){
    int output = ascii % 2;
    //printf("%d",output);
    E4235_Write(outputPins[GPIO], output); //outputs high or low depending on first bit
    ascii = ascii>>1;
    } else{
      E4235_Write(outputPins[GPIO],0);
      //printf("0");
    }
    GPIO ++;
  }
    
}

void binaryMode(char key){
//printf("(Key recieved: %c )", key);
int GPIO = 0;
int binary = key -'0';// char conversion to int
  if(key == 'A'){
    binary = 10;
  } else if(key == 'B'){
    binary = 11;
  } else if(key == 'C'){
    binary = 12;
  } else if(key =='D'){
    binary = 13;
  } else if (key== '\0'){
    binary = 64;
  }else if (key== '@'){
    binary = 64;
  }
    while(GPIO<8){
      if(binary>0){
        int output = binary % 2; //gives lsb to output
        //printf("%d",output);
        E4235_Write(outputPins[GPIO], output); //outputs high or low depending on first bit
        binary = binary>>1; //right shift to
      } else {
        E4235_Write(outputPins[GPIO],0);
        //printf("0");
      }
      GPIO ++;
    }
  //printf("----------------------");
  
}

//to get correct ascii number we can just convert char to int to retrieve ascii value
int main(){
 // Define the row and column pins as ouputs and inputs
 // Define the row and column pin connections
   if (!bcm2835_init()){
        return 1;
    }

  for(int i = 0; i < ROWS; i++) {
  E4235_Select(rowPins[i], 1); //setting rows to be outputs
  E4235_Write(rowPins[i], 1);
  E4235_Select(colPins[i], 1);
  E4235_Write(colPins[i], 0);
  E4235_Select(colPins[i], 0);
  }
  E4235_Select(9, 1);
  for(int i = 0; i<8; i++){
    E4235_Select(outputPins[i], 1);
     E4235_Write(outputPins[i], 0);
  }

  int swapMode = 0;
  
  
  
  
  while(1){

    E4235_DelayMicro(80);// will give 1khz clock
    //output gpio 9 high
    E4235_Write(9,1);
    //Get the key pressed we can use the GPIO 9 to replace the msb output for a clock to our analyzer if needed.
    
    char key =  keypadRead(); //this will convert the char into ascii
    if(key == '\0' && pressed){
      printf("reached");
      if(swapMode % 2 == 0){
        binaryMode(prev);
           int count = 2000;
      while(count>0){
        E4235_DelayMicro(500);
        E4235_Write(9,1);
        E4235_DelayMicro(500);
        E4235_Write(9,0);
        count--;
      }
       binaryMode('@');
       count = 500;
       while(count>0){
        E4235_DelayMicro(500);
        E4235_Write(9,1);
        E4235_DelayMicro(500);
        E4235_Write(9,0);
        count--;
      } 
      } else {
        asciiMode(prev);
           int count = 2000;
      while(count>0){
        E4235_DelayMicro(500);
        E4235_Write(9,1);
        E4235_DelayMicro(500);
        E4235_Write(9,0);
        count--;
      }
      asciiMode('@');
       count = 500;
         while(count>0){
        E4235_DelayMicro(500);
        E4235_Write(9,1);
        E4235_DelayMicro(500);
        E4235_Write(9,0);
        count--;
      }
    }
     
      
      
    }else if(key == '#'){
      swapMode++;
      E4235_DelayMicro(500000);// 
      if(swapMode % 2 == 0){
        printf("Binary Mode On, %d", swapMode);
      } else {
        printf("ASCII Mode On, %d", swapMode);
      }
    } else if (key == '*'){
      swapMode = 0;
      pressed=0;
      key = '@';
    } else if(swapMode % 2 == 0){ //aka default 
      
      binaryMode(key);
      key = '\0';
    } else if(swapMode % 2 ==1 ){
      asciiMode(key);
      key = '\0';
    }
  E4235_DelayMicro(50);
  E4235_Write(9,0);
  //printf("cycle");
  }
}


