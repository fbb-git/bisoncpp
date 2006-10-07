#ifndef Parser_h_included
#define Parser_h_included

// for error()'s inline implementation
#include <iostream>

// $insert baseclass
#include "Parserbase.h"


#undef Parser
class Parser: public ParserBase
{
        
    public:
        int parse();

    private:
        void error(char const *msg)
        {
            std::cerr << msg << std::endl;
        }

        // $insert lex
        int lex();

        void print()    // d_token, d_loc
        {}

    // support functions for parse():
        void executeAction(int ruleNr);
        void errorRecovery();
        int lookup();
        void nextToken();
};


#endif
