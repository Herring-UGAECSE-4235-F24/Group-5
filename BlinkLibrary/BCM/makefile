CC = gcc
CFLAGS = -Wall -o2

SRCS = blinkBcm2835.c
OBJS = $(SRCS: .c = .o)

TARGET = blinkBcm2835

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	
%.o: %.c
	$(CC) $(CFLAGS) -c $<
	
clean:
	rm -f $(TARGET) $(OBJS)
