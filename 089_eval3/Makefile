CFLAGS=-std=gnu++98 -pedantic -Wall -Werror -ggdb3
PROGS=cyoa-step1 cyoa-step2 cyoa-step3 cyoa-step4
OBJS=$(patsubst %,%.o,$(PROGS)) cyoa.o book.o depth.o
all: $(PROGS)
%.o: %.cpp %.hpp
	g++ $(CFLAGS) -c $<
cyoa-step%: cyoa-step%.o cyoa.o book.o depth.o
	g++ -o $@ $^

.PHONY: clean
clean:
	rm -f *~ *.o *.gch $(PROGS) $(OBJS)

