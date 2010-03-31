#ifndef Parser_h_included
#define Parser_h_included

// for error()'s inline implementation
#include <iostream>

// $insert scanner.h
#include "../scanner/scanner.h"

// $insert baseclass
#include "parserbase.h"
#undef Parser

class Parser: public ParserBase
{
    // $insert scannerobject
    Scanner d_scanner;
        
    public:
        int parse();

    private:
        void prompt()
        {
            std::cout << "? " << std::flush;
        }

        void done()
        {
            std::cout << "Done\n";
            ACCEPT();
        }

        void error(char const *msg)
        {
            std::cerr << msg << '\n';
        }

        // $insert lex
        int lex()
        {
            return d_scanner.yylex();
        }

        void print()    // d_token, d_loc 
        {}

    // support functions for parse():
        void executeAction(int ruleNr);
        void errorRecovery();
        int lookup(bool);
        void nextToken();
};


#endif
