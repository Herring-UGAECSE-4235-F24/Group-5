CC = gcc
CFLAGS = -Wall -o2

SRCS = blinkClass.c
OBJS = $(SRCS: .c = .o)

TARGET = blinkClass

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	
%.o: %.c
	$(CC) $(CFLAGS) -c $<
	
clean:
	rm -f $(TARGET) $(OBJS)
