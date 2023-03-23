all: clean analyzer

clean:
	rm -f analyzer

SRC = $(shell find src -name "*.c")

analyzer: $(SRC)
	gcc -o $@ $^ -lzip -ljson-c -g -O1 -Wall -Wextra -Wno-unused-parameter
# 	gcc -o $@ $^ -lzip -ljson-c -fsanitize=address -g -Wall -Wextra -Wno-unused-parameter
