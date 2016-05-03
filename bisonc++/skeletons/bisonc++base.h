#ifndef \@$Base_h_included
#define \@$Base_h_included

#include <exception>
#include <vector>
#include <iostream>
#include <utility>

$insert preincludes
$insert debugincludes

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
        int d_stackIdx__ = -1;
        std::vector<size_t>   d_stateStack__;
        std::vector<STYPE__>  d_valueStack__;
$insert LTYPEstack

    protected:
        enum Return__
        {
            PARSE_ACCEPT__ = 0,   // values used as parse()'s return values
            PARSE_ABORT__  = 1
        };
        enum ErrorRecovery__
        {
            DEFAULT_RECOVERY_MODE__,
            UNEXPECTED_TOKEN__,
        };
        bool        d_actionCases__ = false;
        bool        d_debug__ = true;
        size_t      d_nErrors__ = 0;
        size_t      d_requiredTokens__;
        size_t      d_acceptedTokens__;
        int         d_token__;
        int         d_nextToken__;
        size_t      d_state__;
        STYPE__    *d_vsp__;
        STYPE__     d_val__;
        STYPE__     d_nextVal__;
$insert LTYPEdata

        \@Base();

$insert debugdecl
        void ABORT() const;
        void ACCEPT() const;
        void ERROR() const;
        void clearin();
        bool actionCases() const;
        bool debug() const;
        void pop__(size_t count = 1);
        void push__(size_t nextState);
        void popToken__();
        void pushToken__(int token);
        void reduce__(PI__ const &productionInfo);
        void errorVerbose__();
        size_t top__() const;

    public:
        void setDebug(bool mode);
        void setDebug(DebugMode__ mode);
}; 

inline \@Base::DebugMode__ operator|(\@Base::DebugMode__ lhs, 
                                     \@Base::DebugMode__ rhs)
{
    return static_cast<\@Base::DebugMode__>(static_cast<int>(lhs) | rhs);
};

inline bool \@Base::debug() const
{
    return d_debug__;
}

inline bool \@Base::actionCases() const
{
    return d_actionCases__;
}

inline void \@Base::ABORT() const
{
$insert 4 debug "ABORT(): Parsing unsuccessful"
    throw PARSE_ABORT__;
}

inline void \@Base::ACCEPT() const
{
$insert 4 debug "ACCEPT(): Parsing successful"
    throw PARSE_ACCEPT__;
}

inline void \@Base::ERROR() const
{
$insert 4 debug "ERROR(): Forced error condition"
    throw UNEXPECTED_TOKEN__;
}

inline \@Base::DebugMode__ operator&(\@Base::DebugMode__ lhs,
                                     \@Base::DebugMode__ rhs)
{
    return static_cast<\@Base::DebugMode__>(
            static_cast<int>(lhs) & rhs);
}

// For convenience, when including ParserBase.h its symbols are available as
// symbols in the class Parser, too.
#define \@ \@Base

$insert namespace-close

#endif


