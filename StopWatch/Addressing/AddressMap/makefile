OBJS = 0_AddressMap.o
ifdef DEBUG
DEBUGFLGS = -g
else
DEBUGFLGS =
endif

%.o : %.s
	as $(DEBUGFLGS) $< -o $@
GPIO_OFF: $(OBJS)
	gcc -o AddressMap $(OBJS)

clean:
	rm *.o AddressMap
