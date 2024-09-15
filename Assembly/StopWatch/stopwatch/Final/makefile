OBJS = stopwatchinput.o
ifdef DEBUG
DEBUGFLGS = -g
else
DEBUGFLGS =
endif

%.o : %.s
	as $(DEBUGFLGS) $< -o $@
GPIO_OFF: $(OBJS)
	gcc -o Stopwatch $(OBJS)

clean:
	rm *.o Stopwatch
