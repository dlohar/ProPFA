ProPFA: lex.yy.o totext.o
	    gcc lex.yy.o totext.o -lfl -o ProPFA

totext.o: totext.c y.tab.h
	    gcc -c totext.c -o totext.o

lex.yy.o: lex.yy.c y.tab.h
	    gcc -c lex.yy.c 

y.tab.h:	parser.y 
	    yacc -dtv parser.y

y.tab.c:	parser.y
		yacc -dtv parser.y

lex.yy.c:	lexical.l 
	flex lexical.l



clean:
	rm lex.yy.o lex.yy.c y.tab.h y.tab.c y.output totext.o ProPFA final.out
