#include <stdio.h>
#include "y.tab.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio_ext.h>
#include <time.h>
extern char* yytext;

FILE *yyin,*yyout;

  int generate(char *filename){
  	int another=0;
  	int flag=0;
	int braces=0;
	int ignore=0;
	ignore=0;
	int token;
	token=1;
	yyin=fopen(filename,"r");
	if(!strcmp(filename,"temp.c")){
		yyout=fopen("lexfinal.txt","w");
	}else{
		yyout=fopen("lexfile.txt","w");
	}
	
	while(token!=0){
		token=yylex();
		switch (token) {
			case ZERO: 		fprintf(yyout,"%s`ZERO\n",yytext); break; 
			case SPACE: 	if(ignore!=1)fprintf(yyout,"%s`SPACE\n",yytext); break;
			case ENTER: 	fprintf(yyout,"$`ENTER\n"); break;
			case INCLUDE: 	ignore=1; break;
			case AUTO: 		fprintf(yyout,"%s`AUTO\n",yytext); break;
			case BREAK:	 	fprintf(yyout,"%s`BREAK\n",yytext); break;
			case CASE: 		fprintf(yyout,"%s`CASE\n",yytext); break;
			case CHAR: 		fprintf(yyout,"%s`CHAR\n",yytext); break;
			case CONST:		fprintf(yyout,"%s`CONST\n",yytext); break;
			case CONTINUE: 	fprintf(yyout,"%s`CONTINUE\n",yytext); break;
			case DEFAULT: 	fprintf(yyout,"%s`DEFAULT\n",yytext); break;
			case DO: 		fprintf(yyout,"%s`DO\n",yytext); break;
			case DOUBLE:	fprintf(yyout,"%s`DOUBLE\n",yytext); break;
			case ELSE: 		fprintf(yyout,"%s`ELSE\n",yytext); break;
			case ENUM: 		fprintf(yyout,"%s`ENUM\n",yytext); break;
			case EXTERN: 	fprintf(yyout,"%s`EXTERN\n",yytext); break;
			case FLOAT:		fprintf(yyout,"%s`FLOAT\n",yytext); break;
			case FOR: 		fprintf(yyout,"%s`FOR\n",yytext); break;
			case GOTO: 		fprintf(yyout,"%s`GOTO\n",yytext); break;
			case IF:		fprintf(yyout,"%s`IF\n",yytext); break;
			case ASSERT: 	if(ignore!=1){	fprintf(yyout,"%s`ASSERT\n",yytext);	}	break;
			case INLINE: 	fprintf(yyout,"%s`INLINE\n",yytext); break;
			case INT: 		fprintf(yyout,"%s`INT\n",yytext); break;
			case LONG:		fprintf(yyout,"%s`LONG\n",yytext); break;
			case REGISTER: 	fprintf(yyout,"%s`REGISTER\n",yytext); break;
			case RESTRICT: 	fprintf(yyout,"%s`RESTRICT\n",yytext); break;
			case RETURN: 	fprintf(yyout,"%s`RETURN\n",yytext); break;
			case SHORT: 	fprintf(yyout,"%s`SHORT\n",yytext); break;
			case SIGNED: 	fprintf(yyout,"%s`SIGNED\n",yytext); break;
			case SIZEOF:	fprintf(yyout,"%s`SIZEOF\n",yytext); break;
			case STATIC: 	fprintf(yyout,"%s`STATIC\n",yytext); break;
			case STRUCT: 	fprintf(yyout,"%s`STRUCT\n",yytext); break;
			case SWITCH: 	fprintf(yyout,"%s`SWITCH\n",yytext); break;
			case TYPEDEF: 	fprintf(yyout,"%s`TYPEDEF\n",yytext); break;
			case UNION: 	fprintf(yyout,"%s`UNION\n",yytext); break;
			case UNSIGNED: 	fprintf(yyout,"%s`UNSIGNED\n",yytext); break;
			case VOID: 		fprintf(yyout,"%s`VOID\n",yytext); break;
			case VOLATILE: 	fprintf(yyout,"%s`VOLATILE\n",yytext); break;
			case WHILE:		fprintf(yyout,"%s`WHILE\n",yytext); break;
			case _BOOL: 	fprintf(yyout,"%s`_BOOL\n",yytext); break;
			case _COMPLEX: 	fprintf(yyout,"%s`_COMPLEX\n",yytext); break;
			case _IMAGINARY:fprintf(yyout,"%s`_IMAGINARY\n",yytext); break;
			case IDENTIFIER:if(ignore!=1)fprintf(yyout,"%s`IDENTIFIER\n",yytext); break;

			case '[':		fprintf(yyout,"%s`[\n",yytext); break;
			case ']': 		fprintf(yyout,"%s`]\n",yytext); break;
			case '(': 		fprintf(yyout,"%s`(\n",yytext); break;
			case ')': 		fprintf(yyout,"%s`)\n",yytext); break;
			case '{': 		fprintf(yyout,"%s`{\n",yytext); break;
			case '}': 		fprintf(yyout,"%s`}\n",yytext); break;
			case '.': 		if(ignore!=1)fprintf(yyout,"%s`.\n",yytext); break;
			case PTR_OP: 	fprintf(yyout,"%s`PTR_OP\n",yytext); break;
			case INC_OP: 	fprintf(yyout,"%s`INC_OP\n",yytext); break;
			case DEC_OP: 	fprintf(yyout,"%s`DEC_OP\n",yytext); break;
			case '&': 		fprintf(yyout,"%s`&\n",yytext); break;
			case '*': 		fprintf(yyout,"%s`*\n",yytext); break;
			case '+': 		fprintf(yyout,"%s`+\n",yytext); break;
			case '-': 		fprintf(yyout,"%s`-\n",yytext); break;
			case '/': 		fprintf(yyout,"%s`/\n",yytext); break;
			case '!': 		fprintf(yyout,"%s`!\n",yytext); break;
			case '%': 		fprintf(yyout,"%s`%%\n",yytext); break;
			case RIGHT_OP: 	fprintf(yyout,"%s`RIGHT_OP\n",yytext); break;
			case LEFT_OP: 	fprintf(yyout,"%s`LEFT_OP\n",yytext); break;
			case '<': 		if(ignore!=1)fprintf(yyout,"%s`<\n",yytext); break;
			case '>': 		if(ignore!=1)fprintf(yyout,"%s`>\n",yytext); ignore=0;break;
			case LE_OP: 	fprintf(yyout,"%s`LE_OP\n",yytext); break;
			case GE_OP: 	fprintf(yyout,"%s`GE_OP\n",yytext); break;
			case EQ_OP: 	fprintf(yyout,"%s`EQ_OP\n",yytext); break;
			case NE_OP: 	fprintf(yyout,"%s`NE_OP\n",yytext); break;
			case '^': 		fprintf(yyout,"%s`^\n",yytext); break;
			case '|': 		fprintf(yyout,"%s`|\n",yytext); break;
			case AND_OP: 	fprintf(yyout,"%s`AND_OP\n",yytext); break;
			case OR_OP: 	fprintf(yyout,"%s`OR_OP\n",yytext); break;
			case '?': 		fprintf(yyout,"%s`?\n",yytext); break;
			case ':': 		fprintf(yyout,"%s`:\n",yytext); break;
			case ';': 		fprintf(yyout,"%s`;\n",yytext); break;
			case WPCOND:		fprintf(yyout,"%s`WPCOND\n",yytext); break;
            case PROB:		fprintf(yyout,"%s`PROB\n",yytext); break;
			case ELLIPSIS: 		fprintf(yyout,"%s`ELLIPSIS\n",yytext); break;
			case '=': 			fprintf(yyout,"%s`=\n",yytext); break;
			case ADD_ASSIGN:	fprintf(yyout,"%s`ADD_ASSIGN\n",yytext); break;
			case SUB_ASSIGN:	fprintf(yyout,"%s`SUB_ASSIGN\n",yytext); break;
			case DIV_ASSIGN:	fprintf(yyout,"%s`DIV_ASSIGN\n",yytext); break;
			case MUL_ASSIGN:	fprintf(yyout,"%s`MUL_ASSIGN\n",yytext); break;
			case XOR_ASSIGN:	fprintf(yyout,"%s`XOR_ASSIGN\n",yytext); break;
			case OR_ASSIGN: 	fprintf(yyout,"%s`OR_ASSIGN\n",yytext); break;
			case RIGHT_ASSIGN: 	fprintf(yyout,"%s`RIGHT_ASSIGN\n",yytext); break;
			case LEFT_ASSIGN: 	fprintf(yyout,"%s`LEFT_ASSIGN\n",yytext); break;
			case ',': 			fprintf(yyout,"%s`,\n",yytext); break;
			case '#': 			fprintf(yyout,"%s`#\n",yytext); break;

			case INT_CONSTANT: 	fprintf(yyout,"%s`INT_CONSTANT\n",yytext); break;
			case FLOAT_CONSTANT:fprintf(yyout,"%s`FLOAT_CONSTANT\n",yytext); break;
			case CHAR_CONSTANT: fprintf(yyout,"%s`CHAR_CONSTANT\n",yytext); break;
			case STRING_LITERAL:fprintf(yyout,"%s`STRING_LITERAL\n",yytext); break;

		}
	}
	fclose(yyin);
	fclose(yyout);	
	return 0;	
}

int main(int argsc,char **argsv){
	char *filename;
	if(argsc<2){
		printf("Please pass a filename to Calculate WP\n");
		return 0;
	}
	int exists=0,check=0,i;
	generate(argsv[1]);
	char process[10] = "final.out";
	char *tokens[10];
    for(i=0;i<10;i++){
        tokens[i]=NULL;
    }
    if(strcmp(argsv[1],"temp.c")){
	    system("g++ -std=c++0x  wpcond_paths.cpp -o final.out");
	    execv(process,tokens);
	    perror(" exec : ");
	}
    /*system("g++ wpcond_no.cpp -o final.out");
    //system("g++ wpcond.cpp -o final.out");
	execv(process,tokens);
    perror(" exec : ");
    //execvp(tokens[0],tokens);
    //perror(NULL);*/
	return 0;
}
