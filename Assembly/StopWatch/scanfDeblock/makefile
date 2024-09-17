OBJS = scanfDeblock.o
ifdef DEBUG
DEBUGFLGS = -g
else
DEBUGFLGS =
endif

%.o : %.s
	as $(DEBUGFLGS) $< -o $@
GPIO_OFF: $(OBJS)
	gcc -o scan $(OBJS) E4235_KYBdeblock.s

clean:
	rm *.o scan
