// hdr/includes
#ifndef \@$Base_h_included
#define \@$Base_h_included

#include <iostream>
#include <exception>
#include <vector>
$insert polyincludes
$insert preincludes
$insert debugincludes

// hdr/baseclass
namespace // anonymous
{
    struct PI__;
    struct SR__;

    enum ReservedTokens
    {
        PARSE_ACCEPT     = 0,   // `ACCEPT' TRANSITION
        _FORCED_GET_     = -3,
        _UNDETERMINED_   = -2,
        _EOF_            = -1,
        _error_          = 256
    };
}

$insert namespace-open

$insert polymorphic

class \@Base
{
    public:
        enum DebugMode__
        {
            OFF           = 0,
            ON            = 1 << 0,
            ACTIONCASES   = 1 << 1
        };

$insert tokens
$insert LTYPE
$insert STYPE

    private:
                    //    state   semval
        typedef std::pair<size_t, STYPE__> StatePair;
                    //    token   semval
        typedef std::pair<int,    STYPE__> ValuePair;

        int d_stackIdx;
        std::vector<StatePair> d_stateStack;
        StatePair *d_vsp;               // points to the topmost value stack
                                        // element

        int         d_token;
        size_t      d_state;

        ValuePair d_next;

        bool        d_recovery;
        bool        d_skipToken;        // force the next token on error recov.
        bool        d_terminalToken;

$insert LTYPEstack

    protected:
        enum Return__
        {
            PARSE_ACCEPT__ = 0,   // values used as parse()'s return values
            PARSE_ABORT__  = 1
        };
        enum ErrorRecovery__
        {
            UNEXPECTED_TOKEN__,
        };

        size_t const *d_s_nErrors__;            // saves Meta__::s_nErrors__
        bool        d_actionCases__ = false;
        bool        d_debug__ = true;
        size_t      d_nErrors__;
        size_t      d_requiredTokens__;
        size_t      d_acceptedTokens__;
        STYPE__     d_val__;
$insert LTYPEdata

    public:
        void setDebug(bool mode);
        void setDebug(DebugMode__ mode);

    protected:
        \@Base();

$insert debugdecl
        void ABORT() const;
        void ACCEPT() const;
        void ERROR() const;
        bool debug() const;

        int token__() const;
        int nextToken__() const;

        bool terminalToken__() const;

        STYPE__ &vs__(size_t idx);      // value stack element idx 
                                        // counting back fm the current 
                                        // element in the production rule

        void errorVerbose__();
        size_t stackSize__() const;
        StatePair const &top__() const;

        bool recovering__();
        int lookup__() const;
        void done__();
        void error__();
        void lex__(int token);
        void pop__(size_t count = 1);
        void popToken__();
        void pushToken__(int token);
        void reduce__(int rule);
        void reset__();
        void shift__(int nextState);

    private:
        void push(size_t nextState);
        void checkStackSize();

        StatePair &top(size_t idx = 0);
}; 



// hdr/abort
inline void \@Base::ABORT() const
{
$insert 4 debug "ABORT(): Parsing unsuccessful"
    throw PARSE_ABORT__;
}

// hdr/accept
inline void \@Base::ACCEPT() const
{
$insert 4 debug "ACCEPT(): Parsing successful"
    throw PARSE_ACCEPT__;
}

// hdr/debug
inline bool \@Base::debug() const
{
    return d_debug__;
}

// hdr/error
inline void \@Base::ERROR() const
{
$insert 4 debug "ERROR(): Forced error condition"
    throw UNEXPECTED_TOKEN__;
}

// hdr/top
inline \@Base::StatePair &\@Base::top(size_t idx) 
{
    return d_stateStack[d_stackIdx - idx];
}

inline \@Base::StatePair const &\@Base::top__() const
{
    return d_stateStack[d_stackIdx];
}

// hdr/opbitand
inline \@Base::DebugMode__ operator&(\@Base::DebugMode__ lhs,
                                     \@Base::DebugMode__ rhs)
{
    return static_cast<\@Base::DebugMode__>(
            static_cast<int>(lhs) & rhs);
}

// hdr/opbitor
inline \@Base::DebugMode__ operator|(\@Base::DebugMode__ lhs, 
                                     \@Base::DebugMode__ rhs)
{
    return static_cast<\@Base::DebugMode__>(static_cast<int>(lhs) | rhs);
};

// hdr/stacksize
inline size_t \@Base::stackSize__() const
{
    return d_stackIdx + 1;
}

// hdr/terminaltoken
inline bool \@Base::terminalToken__() const
{
    return d_terminalToken;
}
// hdr/token
inline int \@Base::token__() const
{
    return d_token;
}
// hdr/nexttoken
inline int \@Base::nextToken__() const
{
    return d_next.first;
}
// hdr/vs
inline \@Base::STYPE__ &\@Base::vs__(size_t idx) 
{
    return (d_vsp - idx)->second;
}

// hdr/tail
// For convenience, when including ParserBase.h its symbols are available as
// symbols in the class Parser, too.
#define \@ \@Base

$insert namespace-close

#endif
