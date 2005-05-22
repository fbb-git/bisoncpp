#ifndef MyParser_h_included
#define MyParser_h_included

// for error()'s inline implementation
#include <iostream>

// $insert baseclass
#include "MyParserbase.h"
// $insert scanner.h
#include "MyScanner.h"


#undef MyParser
class MyParser: public MyParserBase
{
    // $insert scannerobject
    MyScanner d_scanner;
        
    public:
        int parse();

    private:
        void error(char const *msg)
        {
            std::cerr << msg << std::endl;
        }

        // $insert lex
        int lex()
        {
            return d_scanner.yylex();
        }

        void print()    // d_token, d_lloc (?)
        {}

    // support functions for parse():

        void executeAction(int d_production);
        unsigned errorRecovery();
        int lookup(int token);
        int nextToken();
};


#endif
