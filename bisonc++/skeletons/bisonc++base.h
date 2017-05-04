#ifndef \@$Base_h_included
#define \@$Base_h_included

#include <iostream>
#include <exception>
#include <vector>
#include <stack>
#include <tuple>
$insert polyincludes
$insert preincludes
$insert debugincludes

namespace // anonymous
{
    struct PI__;
    struct SR__;
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
        typedef std::tuple<size_t, size_t, size_t> StateTuple;

        int d_stackIdx__;
        std::vector<StateTuple> d_stateStack__;
        std::vector<STYPE__> d_valueStack__;
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
        std::stack<int> d_tokenStack__;
        size_t const *d_s_nErrors__;            // saves Meta__::s_nErrors__
        bool        d_actionCases__ = false;
        bool        d_debug__ = true;
        size_t      d_nErrors__;
        size_t      d_requiredTokens__;
        size_t      d_acceptedTokens__;
        int         d_token__;
        size_t      d_state__;
        STYPE__    *d_vsp__;
        STYPE__     d_val__;
        STYPE__     d_nextVal__;
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

        SR__ const *findToken__() const;
        size_t msgIdx__() const;
        void done__();
        void errorVerbose__();
        void msgIdx__(size_t idx);
        void pop__(size_t count = 1);
        void print__();
        void pushToken__(int token);
        void push__(size_t nextState);
        void reduce__(PI__ const &pi);
        void reset__();

        template<int>                           // elements fm the stateStack:
        size_t top__(size_t shift = 0) const;   // <0>: state, <1>: msg idx, 
                                                // <2>: org msg idx
        template<int>   
        size_t &top__();

    private:
        void checkStackSize();

        StateTuple &top();
}; 

template<int idx>
inline size_t \@Base::top__(size_t shift) const
{
    return std::get<idx>(d_stateStack__[ d_stackIdx__ - shift ]);
}

template<int idx>
inline size_t &\@Base::top__()
{
    return std::get<idx>(d_stateStack__[ d_stackIdx__ ]);
}

inline \@Base::StateTuple &\@Base::top()
{
    return d_stateStack__[d_stackIdx__];
}

inline \@Base::DebugMode__ operator|(\@Base::DebugMode__ lhs, 
                                     \@Base::DebugMode__ rhs)
{
    return static_cast<\@Base::DebugMode__>(static_cast<int>(lhs) | rhs);
};

inline size_t \@Base::msgIdx__() const
{
    return top__<1>();
}

inline void \@Base::msgIdx__(size_t idx)
{
    top__<1>() = idx;
}

inline bool \@Base::debug() const
{
    return d_debug__;
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
