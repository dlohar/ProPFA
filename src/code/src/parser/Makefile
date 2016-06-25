include ../Makefile.variables

all: tokenize parse build

tokenize:
	flex tokenizer.l

parse:
	/usr2/faculty/soumyajit/debasmita/ProPFA/src/code/binary/bison/bin/bison -d grammar.y

build:
	$(CC) $(FLAGS) -c *.c

clean:
	rm -f grammar.tab.* lex.yy.c *.o
