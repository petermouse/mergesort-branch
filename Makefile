CC ?= gcc
CFLAGS ?= -O0 -Wall -std=gnu99
SRCS = main.c
EXEC = mergesort_orig mergesort_opt



all: $(EXEC)

mergesort_orig: $(SRCS) mergesort_orig.h mergesort_orig.c
	$(CC) $(CFLAGS) -DIMPL="\"$@.h\"" -o $@ $(SRCS) $@.c

mergesort_opt: $(SRCS) mergesort_opt.h mergesort_opt.c
	$(CC) $(CFLAGS) -DIMPL="\"$@.h\"" -o $@ $(SRCS) $@.c

.PHONY: clean
clean:
	$(RM) $(EXEC) *.o *.txt 
