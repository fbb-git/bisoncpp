%{ 
//  see README for modifications I made to the scanner and grammar.

#define _SKIP_YYFLEXLEXER_
#include "MyScanner.h"

#include "MyParserbase.h"

%}

%option yyclass="MyScanner" outfile="MyScanner.cc"
%option c++ 8bit warn noyywrap yylineno

digit   [0-9]
integer [1-9]{digit}*
ws  [ \t\n]+

%%

{ws}                { /* no action */ }
{integer}   {return MyParser::INTEGER; }
"AND"       {return(MyParser::AND);}
"OR"        {return(MyParser::OR);}
"NOT"       {return(MyParser::NOT);}
"TRUE"  {return MyParser::BOOLEAN; }
"FALSE" {return MyParser::BOOLEAN; }
"-"     {return(MyParser::MINUS);}
"+"     {return(MyParser::PLUS);}
"("     {return(MyParser::LPARA);}
")"     {return(MyParser::RPARA);}
