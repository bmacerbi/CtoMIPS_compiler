all:
	mkdir -p bin
	flex -o bin/lex.yy.c scanner.l
	gcc bin/lex.yy.c -lfl -o bin/scanner