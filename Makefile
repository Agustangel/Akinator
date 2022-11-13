
INCLUDES=include
SOURCE=source

akinator: main.o bintree.o akinator.o
	gcc -o akinator $^ -llogger -lonegin

main.o: main.c
	gcc -g -O0 -I${INCLUDES}/ -c $^

bintree.o: ${SOURCE}/bintree.c
	gcc -g -O0 -I${INCLUDES}/ -c $^

akinator.o: ${SOURCE}/akinator.c
	gcc -g -O0 -I${INCLUDES}/ -c $^

valgrind: akinator
	valgrind --leak-check=yes ./akinator

clean:
	rm akinator main.o bintree.o akinator.o
	