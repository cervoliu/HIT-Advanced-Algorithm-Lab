CC = g++
CFLAGS = -Wall -Wextra -O2
LDFLAGS = -lpcap

all: analyzer

analyzer: analyzer.cpp sketch.h
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

.PHONY:
clean:
	rm -f analyzer output.txt