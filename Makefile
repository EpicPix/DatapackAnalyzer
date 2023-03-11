all: clean analyzer

clean:
	rm -f analyzer

SRC = $(wildcard src/*.c)

analyzer: $(SRC)
	gcc -o $@ $^ -lzip
