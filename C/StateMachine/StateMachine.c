//Commented out because this is only used for Arduino IDE libraries which is what I was using. I created methods below that were included in the header file.
//#include <Keypad.h>

// Define the row and column pins
const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns

//to get correct ascii number we can just convert char to int to retrieve ascii value

// Define the row and column pin connections
byte rowPins[ROWS] = {20, 21, 22, 23}; // Connect to the row pins of the keypad
byte colPins[COLS] = {24, 25, 26, 27};  // Connect to the column pins of the keypad


// Define the keymap
char getKey(int x, int y) {
  char keys[ROWS][COLS] = {
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
	  digitalWrite(rowPins[i], 1); //high output 1
	  for (int j = 0; j < 4; j++) {
	    if (digitalRead(colPins[j] == 1) { //high output 1
		    delay(.5); //debounce delay of half a second
		    if(digitalRead(colPins[j] == 1) { //high output 1
			    digitalWrite(rowPins[i], 0); //low output 0
			    return getKey(x,y);
		    }
	    }
    }
  digitalWrite(rowPins[i], 0); //low output 0
  }
return 0;
}

int main(){
  microsleep(1000);// will give 1khz clock
  //output gpio 9 high
  //commented out below and created new getkey method above
  //char key = keypad.getKey(); // Get the key pressed we can use the GPIO 9 to replace the msb output for a clock to our analyzer if needed.
  int ascii = key; //this will convert the char into ascii
  int GPIO = 17;
  while(ascii>0){
    int output = ascii % 2;
    write(GPIO, output) //outputs high or low depending on first bit
    ascii = ascii>>1;
    GPIO --;
  }
}
