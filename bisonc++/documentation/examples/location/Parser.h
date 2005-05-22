#ifndef Parser_h_included
#define Parser_h_included

// for error()'s inline implementation
#include <iostream>

// $insert scanner.h
#include "scanner/scanner.h"

// $insert baseclass
#include "Parserbase.h"
#undef Parser

class Parser: public ParserBase
{
    // $insert scannerobject
    Scanner d_scanner;
        
    public:
        Parser()
        :
            d_scanner(&d_loc, &d_val)
        {}
        
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
