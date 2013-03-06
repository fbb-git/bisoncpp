#ifndef Parser_h_included
#define Parser_h_included

// $insert baseclass
#include "parserbase.h"
// $insert scanner.h
#include "../scanner/scanner.h"


#undef Parser
class Parser: public ParserBase
{
    // $insert scannerobject
    Scanner d_scanner;
        
    public:
        int parse();

    private:
        void error(char const *msg);
        int lex();                  
                                    
        void print();               
        void prompt();
        void done();

    // support functions for parse():
        void executeAction(int ruleNr);
        void errorRecovery();
        int lookup(bool recovery);
        void nextToken();
        void print__();
};

inline void Parser::prompt()
{
    std::cout << "? " << std::flush;
}

inline void Parser::done()
{
    std::cout << "Done\n";
    ACCEPT();
}

#endif
