OBJS = PCLDR_6_2.o
ifdef DEBUG
DEBUGFLGS = -g
else
DEBUGFLGS =
endif

%.o : %.s
	as $(DEBUGFLGS) $< -o $@
GPIO_OFF: $(OBJS)
	gcc -o PCDLDR $(OBJS)

clean:
	rm *.o PCDLDR
