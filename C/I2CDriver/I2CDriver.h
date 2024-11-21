
#include <stdint.h>
#include <time.h>


#define SDA 27          // GPIO pin for SDA
#define SCL 17          // GPIO pin for SCL
#define DS3231 0x68     // I2C address for RTC 

// External Function Prototypes (Assembly)
extern int E4235_Write(int GPIO, int state);
extern int E4235_Select(int GPIO, int state);
extern void E4235_DelayMicro(int count);
extern int E4235_Read(int GPIO);

// Function Prototypes

void start(void);

void stop(void);

int splitInt(int num);

unsigned char reverse(unsigned char byte);

void sendByte(unsigned char byte);

void init(int mode);

void I2C_Write(char *wbuf);

void I2C_Read(char *rbuf);

char readByte(void);

