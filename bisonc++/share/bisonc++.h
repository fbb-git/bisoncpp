#ifndef @_h_included
#define @_h_included

// for error()'s inline implementation
#include <iostream>

$insert baseclass
$insert scanner.h

$insert namespace-open

#undef @
class @: public @Base
{
$insert 4 scannerobject
        
    public:
        int parse();

    private:
        void error(char const *msg)
        {
            std::cerr << msg << std::endl;
        }

$insert 8 lex

        void print()    // d_token, d_loc
        {}

    // support functions for parse():

        void executeAction(int d_production);
        unsigned errorRecovery();
        int lookup(int token);
        int nextToken();
};

$insert namespace-close

#endif
