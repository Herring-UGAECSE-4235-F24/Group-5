//Commented out because this is only used for Arduino IDE libraries which is what I was using. I created methods below that were included in the header file.
//#include <Keypad.h>
//#include "E4235.h"
#include <stdio.h>
#include <ctype.h>
//gcc StateMachine.c -o StateMachine E4235_DelayMicro.s E4235_Select.s E4235_Write.s E4235_Read.s
extern int E4235_Write(int GPIO, int state);
extern int E4235_Select(int GPIO, int state);
extern int E4235_Read(int GPIO);
extern void E4235_DelayMicro(int count);
// Define the row and column pins
const int ROWS = 4; // Four rows
const int COLS = 4; // Four columns
const int rowPins[4] = {20, 21, 22, 23}; // Connect to the row pins of the keypad
const int colPins[4] = {24, 25, 26, 27};  // Connect to the column pins of the keypad
  




// Define the keymap
char getKey(int x, int y) {
  char keys[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
  };
  return keys[y][x];
}


//Read the Keypad
char keypadRead() {
  for (int i = 0; i < 4; i++) {
	  E4235_Write(rowPins[i], 1); //high output 1
	  for (int j = 0; j < 4; j++) {
	    if (E4235_Read(colPins[j])) { //high output 1
		    E4235_DelayMicro(100000); //debounce delay of tenth a second
		    if(E4235_Read(colPins[j])) { //high output 1
			    E4235_Write(rowPins[i], 0); //low output 0
          char key = getKey(i,j);
          printf("pressed: %c", &key);
          return key;
		    }
	    }
    }
  E4235_Write(rowPins[i], 0); //low output 0
  }
return 0;
}

void asciiMode(char key){
 int GPIO = 10;
 int ascii = key;
  while(ascii>0){
    if(ascii>0){
    int output = ascii % 2;
    E4235_Write(GPIO, output); //outputs high or low depending on first bit
    ascii = ascii>>1;
    } else{
      E4235_Write(GPIO,0);
    }
    GPIO ++;
  }
}

void binaryMode(char key){
int GPIO = 10;
int binary = 40; //default
  if (isdigit(key)){
  int binary = key -'0'; // char conversion to int
  }else if(key == 'A'){
    int binary = 10;
  } else if(key == 'B'){
    int binary = 11;
  } else if(key == 'C'){
    int binary = 12;
  } else if(key =='D'){
    int binary = 13;
  }
    while(GPIO>18){
      if(binary>0){
        int output = binary % 2; //gives lsb to output
        E4235_Write(GPIO, output); //outputs high or low depending on first bit
        binary = binary>>1; //right shift to
      } else {
      E4235_Write(GPIO,0);
      }
      GPIO ++;
    }
}

//to get correct ascii number we can just convert char to int to retrieve ascii value
int main(){
 // Define the row and column pins as ouputs and inputs
  // Define the row and column pin connections
  
  for(int i = 0; i < ROWS; i++) {
  E4235_Select(rowPins[i], 1); //setting rows to be outputs
  E4235_Select(colPins[i], 0); //setting cols as inputs
  }

  int swapMode = 0;
  
  
  
  
  
  while(1){
    E4235_DelayMicro(500);// will give 1khz clock
    //output gpio 9 high
    E4235_Write(9,1);
    //Get the key pressed we can use the GPIO 9 to replace the msb output for a clock to our analyzer if needed.
    char key =  keypadRead(); //this will convert the char into ascii
    if(key == '#'){
      swapMode++;
    } else if (key == '*'){
      swapMode = 0;
      key = '@';
    } else if(swapMode % 2 == 0){ //aka default 
      binaryMode(key);
    } else {
      asciiMode(key);
    }
  E4235_DelayMicro(500);
  E4235_Write(9,0);
  }
}


