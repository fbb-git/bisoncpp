#ifndef ParserBase_h_included
#define ParserBase_h_included

#include <vector>
#include <iostream>


namespace // anonymous
{
    struct PI;
}


class ParserBase
{
    public:
// $insert tokens

    // Symbolic tokens:
    enum Tokens
    {
        NUM = 257,
        VAR,
        FNCT,
        NEG,
    };

// $insert STYPE
struct STYPE
{
    double u_val;
    double *u_symbol;
    double (*u_fun)(double);
};


    private:
        int d_stackIdx;
        std::vector<size_t>   d_stateStack;
        std::vector<STYPE>    d_valueStack;

    protected:
        enum Return
        {
            PARSE_ACCEPT = 0,   // values used as parse()'s return values
            PARSE_ABORT  = 1
        };
        enum ErrorRecovery
        {
            DEFAULT_RECOVERY_MODE,
            UNEXPECTED_TOKEN,
        };
        bool        d_debug;
        size_t    d_nErrors;
        int         d_token;
        int         d_nextToken;
        size_t    d_state;
        STYPE      *d_vsp;
        STYPE       d_val;

        ParserBase();

        void ABORT() const throw(Return);
        void ACCEPT() const throw(Return);
        void ERROR() const throw(ErrorRecovery);
        void checkEOF() const;
        void clearin();
        bool debug() const;
        void pop(size_t count = 1);
        void push(size_t nextState);
        void reduce(PI const &productionInfo);
        size_t top() const;

    public:
        void setDebug(bool mode);
}; 

inline bool ParserBase::debug() const
{
    return d_debug;
}

inline void ParserBase::setDebug(bool mode)
{
    d_debug = mode;
}

inline void ParserBase::ABORT() const throw(Return) 
{
    throw PARSE_ABORT;
}

inline void ParserBase::ACCEPT() const throw(Return)
{
    throw PARSE_ACCEPT;
}

inline void ParserBase::ERROR() const throw(ErrorRecovery)
{
    throw UNEXPECTED_TOKEN;
}


// As a convenience, when including ParserBase.h its symbols are available as
// symbols in the class Parser, too.
#define Parser ParserBase


#endif


