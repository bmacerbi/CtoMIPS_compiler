all: bison flex gcc
	@echo "Done."

bison: parser.y
	bison -v parser.y

flex: scanner.l
	flex scanner.l

gcc: scanner.c parser.c
	gcc -Wall -o compiler scanner.c parser.c

clear:
	@rm -f *.o *.output scanner.c parser.h parser.c compiler