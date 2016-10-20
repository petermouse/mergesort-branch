CC ?= gcc
CFLAGS ?= -O0 -Wall -std=gnu99
SRCS = main.c
COUNT ?=100
EXEC = mergesort_orig mergesort_opt gen_testcase



all: $(EXEC)

mergesort_orig: $(SRCS) mergesort_orig.h mergesort_orig.c
	$(CC) $(CFLAGS) -DIMPL="\"$@.h\"" -o $@ $(SRCS) $@.c

mergesort_opt: $(SRCS) mergesort_opt.h mergesort_opt.c
	$(CC) $(CFLAGS) -DIMPL="\"$@.h\"" -o $@ $(SRCS) $@.c

gen_testcase: 
	$(CC) $(CFLAGS) -o $@ $@.c

test: $(EXEC)
	rm -f opt.txt orig.txt
	perf stat --repeat $(COUNT)	\
		-e cache-misses,cache-references,branches,branch-misses,instructions \
		./mergesort_orig
	perf stat --repeat $(COUNT)  \
		-e cache-misses,cache-references,branches,branch-misses,instructions  \
		./mergesort_opt
.PHONY: clean
clean:
	$(RM) $(EXEC) *.o *.txt 
