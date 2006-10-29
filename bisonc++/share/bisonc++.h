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
        void error(char const *msg);    // called on (syntax) errors
        int lex();                      // returns the next token from the
                                        // lexical scanner. 
        void print();                   // use, e.g., d_token, d_loc

    // support functions for parse():
        void executeAction(int ruleNr);
        void errorRecovery();
        int lookup();
        void nextToken();
};

inline void @::error(char const *msg)
{
    std::cerr << msg << std::endl;
}

$insert lex

inline void @::print()      // use d_token, d_loc
{}

$insert namespace-close

#endif
