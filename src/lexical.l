%{
  #include <stdlib.h>
  #include <stdio.h>
  #include "y.tab.h"
  
%}

letter [a-zA-Z_]
digit  [0-9]
exp_part [Ee][+-]?{digit}+
int_constant [1-9]{digit}*
char_const       \'(\\[abfnrtv\"\'?\\]|[^\\'\n])*\'
string_literal   \"(\\[abfnrtv\"\'?\\]|[^\\"\n])*\"
ID               {letter}({letter}|{digit})*

%%
"auto"			  { return(AUTO);  } 
"break"		  	{ return(BREAK); }
"case"			  { return(CASE);  }
"char"			  { return(CHAR);  }
"const"			  { return(CONST); }
"continue"	  { return(CONTINUE); }
"default"		  { return(DEFAULT);  }
"do"			    { return(DO);    }
"double"	  	{ return(DOUBLE);   }
"else"		  	{ return(ELSE);  }
"enum"		  	{ return(ENUM);  }
"extern"	  	{ return(EXTERN);}
"float"		  	{ return(FLOAT); }
"for"		    	{ return(FOR);   }
"goto"		  	{ return(GOTO);  }
"if"			    { return(IF);  }
" "             {return(SPACE);}
"\n"            {return(ENTER);}
"assert"        { return(ASSERT);  }
"int"		    	{ return(INT); }           
"long"			  { return(LONG);  }         
"register"   	{ return(REGISTER); }
"return"		  { return(RETURN); }
"short"		  	{ return(SHORT);  }        
"signed"	  	{ return(SIGNED); }        
"sizeof"	  	{ return(SIZEOF); }
"static"	  	{ return(STATIC); }
"struct"	  	{ return(STRUCT); }
"switch"	  	{ return(SWITCH); }
"typedef"	  	{ return(TYPEDEF);  }
"union"		  	{ return(UNION);  }
"unsigned"  	{ return(UNSIGNED); }
"void"			  { return(VOID); }
"volatile"		{ return(VOLATILE); }
"while"			  { return(WHILE);  }
"restrict"    { return(RESTRICT); }
"_Bool"       { return(_BOOL);}
"_Complex"    { return(_COMPLEX); }
"inline"      { return(INLINE); }
"_Imaginary"  { return(_IMAGINARY);} 
"#include"        {return(INCLUDE);}
"0"               {return(ZERO);}
{ID}                             { return(IDENTIFIER);    }

{int_constant}                   { return(INT_CONSTANT);  } 
{digit}+{exp_part}               { return(FLOAT_CONSTANT);}

{digit}*"."{digit}+({exp_part})? { return(FLOAT_CONSTANT);}

{digit}+"."{digit}*({exp_part})? { return(FLOAT_CONSTANT);}
{char_const}                     { return(CHAR_CONSTANT); }
{string_literal}                 { return(STRING_LITERAL);}

"..."			{ return(ELLIPSIS); }
">>="			{ return(RIGHT_ASSIGN); }
"<<="			{ return(LEFT_ASSIGN); }
"+="			{ return(ADD_ASSIGN); }
"-="			{ return(SUB_ASSIGN); }
"*="			{ return(MUL_ASSIGN); }
"/="			{ return(DIV_ASSIGN); }
"%="			{ return(MOD_ASSIGN); }
"&="			{ return(AND_ASSIGN); }
"^="			{ return(XOR_ASSIGN); }
"|="			{ return(OR_ASSIGN); }
">>"			{ return(RIGHT_OP); }
"<<"			{ return(LEFT_OP); }
"++"			{ return(INC_OP); }
"--"			{ return(DEC_OP); }
"->"			{ return(PTR_OP); }
"&&"			{ return(AND_OP); }
"||"			{ return(OR_OP); }
"<="			{ return(LE_OP); }
">="			{ return(GE_OP); }
"=="			{ return(EQ_OP); }
"!="			{ return(NE_OP); }
";"			  { return(';'); }
("{")		  { return('{'); }
("}")		  { return('}'); }
","			  { return(','); }
":"			  { return(':'); }
"="			  { return('='); }
"("			  { return('('); }
")"			  { return(')'); }
("[")		  { return('['); }
("]")		  { return(']'); }
"."			  { return('.'); }
"&"			  { return('&'); }
"!"			  { return('!'); }
"~"			  { return('~'); }
"-"			  { return('-'); }
"+"			  { return('+'); }
"*"			  { return('*'); }
"/"			  { return('/'); }
"%"			  { return('%'); }
"<"			  { return('<'); }
">"			  { return('>'); }
"^"			  { return('^'); }
"|"			  { return('|'); }
"?"			  { return('?'); }
"#"           { return('#'); }
"//@"         { return(WPCOND);}
"//#"			{return(PROB);}


 


"/*"        {
                     register int c;
     
                     for ( ; ; )
                       {
                         while ( (c = input()) != '*' &&
                                 c != EOF )
                             ;    /* eat up text of comment */
     
                         if ( c == '*' )
                             {
                             while ( (c = input()) == '*' )
                                 ;
                             if ( c == '/' )
                                 break;    /* found the end */
                             }
     
                         if ( c == EOF )
                             {
                             error( "EOF in comment" );
                             break;
                             }
                       }
            }

"//"  {
         register int c;
         while((c = input())!= '\n' && c != EOF );

 }

[ \t\v\n\f]		{ }
.             { }

%%



