all: clean build run

clean:
	rm -f ./main.out

build:
	gcc -std=c99 -O0 ./src/globals.c ./src/main.c ./src/utils.c ./src/database.c ./src/associado.c ./src/livro.c ./src/emprestimo.c ./src/menu.c -o ./main.out

run:
	./main.out