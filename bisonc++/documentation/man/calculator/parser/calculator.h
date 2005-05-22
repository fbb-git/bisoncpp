#ifndef Calculator_h_included
#define Calculator_h_included

// for error()'s inline implementation
#include <iostream>

// $insert baseclass
#include "calculatorbase.h"
// $insert scanner.h
#include "../scanner/scanner.h"


#undef Calculator
class Calculator: public CalculatorBase
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
