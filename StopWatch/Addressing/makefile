OBJS = Addressing.o
ifdef DEBUG
DEBUGFLGS = -ggdb
else
DEBUGFLGS =
endif

%.o : %.s
	as $(DEBUGFLGS) $< -o $@
GPIO_OFF: $(OBJS)
	gcc -o Addressing $(OBJS)

clean:
	rm *.o Addressing
