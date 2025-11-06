all: clean build run

clean:
	rm -f ./main.out

build:
	gcc -std=c99 -O0 ./main.c -o ./main.out

run:
	./main.out
