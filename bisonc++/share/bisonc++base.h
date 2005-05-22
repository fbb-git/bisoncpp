#ifndef @Base_h_included
#define @Base_h_included

#include <vector>

$insert preincludes

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
        std::vector<unsigned>   d_stateStack;
        std::vector<STYPE>      d_valueStack;
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
        unsigned    d_nErrors;
        int         d_token;
        unsigned    d_state;
        STYPE      *d_vsp;
        STYPE       d_val;
$insert LTYPEdata

        @Base();

$insert debugdecl
        void ABORT() const throw(Return);
        void ACCEPT() const throw(Return);
        void ERROR() const throw(ErrorRecovery);
        void clearin();

        bool debug() const
        {
            return d_debug;
        }
        void pop(unsigned count = 1);
        void push(unsigned nextState);
        unsigned reduce(PI const &productionInfo);
        void setDebug(bool mode)
        {
            d_debug = mode;
        }
        unsigned top() const;

// class @Base ends
};


// As a convenience, when including ParserBase.h its symbols are available as
// symbols in the class Parser, too.
#define @ @Base

$insert namespace-close

#endif


