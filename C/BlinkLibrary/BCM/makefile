CC = gcc
CFLAGS = -Wall -o2 -lbcm2835

SRCS = blinkBcm2835.c bcm2835.h
OBJS = $(SRCS: .c = .o)

TARGET = blinkBcm2835

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	
%.o: %.c
	$(CC) $(CFLAGS) -c $<
	
clean:
	rm -f $(TARGET) $(OBJS)
