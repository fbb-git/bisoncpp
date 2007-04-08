#ifndef @Base_h_included
#define @Base_h_included

#include <vector>
#include <iostream>

$insert preincludes
$insert debugincludes

namespace // anonymous
{
    struct PI;
}

$insert namespace-open

class @Base
{
    public:
$insert tokens
$insert LTYPE
$insert STYPE

    private:
        int d_stackIdx;
        std::vector<size_t>   d_stateStack;
        std::vector<STYPE>    d_valueStack;
$insert LTYPEstack

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
$insert LTYPEdata

        @Base();

$insert debugdecl
        void ABORT() const throw(Return);
        void ACCEPT() const throw(Return);
        void ERROR() const throw(ErrorRecovery);
        void clearin();
        bool debug() const;
        void pop(size_t count = 1);
        void push(size_t nextState);
        void reduce(PI const &productionInfo);
        size_t top() const;

    public:
        void setDebug(bool mode);
}; 

inline bool @Base::debug() const
{
    return d_debug;
}

inline void @Base::setDebug(bool mode)
{
    d_debug = mode;
}

// As a convenience, when including ParserBase.h its symbols are available as
// symbols in the class Parser, too.
#define @ @Base

$insert namespace-close

#endif


