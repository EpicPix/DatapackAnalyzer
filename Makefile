all: clean analyzer

clean:
	rm -f analyzer

SRC = $(shell find src -name "*.c")

analyzer: $(SRC)
	gcc -o $@ $^ -lzip -ljson-c
