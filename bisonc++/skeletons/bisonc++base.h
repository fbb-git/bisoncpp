// hdr/includes
#ifndef \@$Base_h_included
#define \@$Base_h_included

#include <exception>
#include <vector>
#include <iostream>
$insert polyincludes
$insert preincludes
$insert debugincludes

// hdr/baseclass

namespace // anonymous
{
    struct PI__;
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
                        // state  semval
        typedef std::pair<size_t, STYPE__> StatePair;
                       // token   semval
        typedef std::pair<int,    STYPE__> TokenPair;

        int d_stackIdx = -1;
        std::vector<StatePair> d_stateStack;
        StatePair  *d_vsp = 0;       // points to the topmost value stack
        size_t      d_state = 0;

        TokenPair   d_next;
        int         d_token;

        bool        d_terminalToken = false;
        bool        d_recovery = false;

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

        bool        d_actionCases__ = false;    // set by options/directives
        bool        d_debug__ = true;
        size_t      d_requiredTokens__;
        size_t      d_nErrors__;                // initialized by clearin()
        size_t      d_acceptedTokens__;
        STYPE__     d_val__;

$insert LTYPEdata

        \@Base();

$insert debugdecl
        void ABORT() const;
        void ACCEPT() const;
        void ERROR() const;

        STYPE__ &vs__(int idx);             // value stack element idx 
        int  lookup__() const;
        int  savedToken__() const;
        int  token__() const;
        size_t stackSize__() const;
        size_t state__() const;
        size_t top__() const;
        void clearin__();
        void errorVerbose__();
        void lex__(int token);
        void popToken__();
        void pop__(size_t count = 1);
        void pushToken__(int token);
        void push__(size_t nextState);
        void redoToken__();
        bool recovery__() const;
        void reduce__(int rule);
        void shift__(int state);
        void startRecovery__();

    public:
        void setDebug(bool mode);
        void setDebug(DebugMode__ mode);
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


// hdr/error
inline void \@Base::ERROR() const
{
$insert 4 debug "ERROR(): Forced error condition"
    throw UNEXPECTED_TOKEN__;
}

// hdr/savedtoken
inline int \@Base::savedToken__() const
{
    return d_next.first;
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

// hdr/recovery
inline bool \@Base::recovery__() const
{
    return d_recovery;
}

// hdr/stacksize
inline size_t \@Base::stackSize__() const
{
    return d_stackIdx + 1;
}

// hdr/state
inline size_t \@Base::state__() const
{
    return d_state;
}

// hdr/token
inline int \@Base::token__() const
{
    return d_token;
}

// hdr/vs
inline \@Base::STYPE__ &\@Base::vs__(int idx) 
{
    return (d_vsp + idx)->second;
}

// hdr/tail
// For convenience, when including ParserBase.h its symbols are available as
// symbols in the class Parser, too.
#define \@ \@Base

$insert namespace-close

#endif



