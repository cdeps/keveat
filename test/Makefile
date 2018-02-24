CC?=$(shell which cc)
CFLAGS?=
CFLAGS+= -O3 -s
OBJS=$(patsubst src/%.c,src/%.o,$(wildcard src/*.c))

all: test

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

test: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

.PHONY: clean
clean:
	$(foreach obj,$(wildcard src/*.o),rm $(obj))
