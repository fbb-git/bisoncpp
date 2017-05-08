// hdr/includes
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

// hdr/baseclass
namespace // anonymous
{
    struct PI__;
    struct SR__;

    enum ReservedTokens
    {
        PARSE_ACCEPT     = 0,   // `ACCEPT' TRANSITION
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
                        // state   msgidx  orgidx  semval
        typedef std::tuple<size_t, size_t, size_t, STYPE__> StateTuple;

        int d_stackIdx;
        std::vector<StateTuple> d_stateStack;
        StateTuple *d_vsp;              // points to the topmost value stack
                                        // element
        int     d_reducedToken;
        int     d_token;
        size_t  d_state;
        bool    d_recovery;

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

        STYPE__ &vs__(size_t idx);      // value stack element idx 
                                        // counting back fm the current 
                                        // element in the production rule


        SR__ const *tryDefaultReduce__() const;
        SR__ const *findToken__() const;
        size_t msgIdx__() const;
        void done__();
        void error__();
        void newToken__(int token);
        void errorVerbose__();
        void msgIdx__(size_t idx);
        void pop__(size_t count = 1);
        void push__(size_t nextState);
        void reduce__(PI__ const &pi);
        void reset__();
        size_t stackSize__() const;
        
        template<int>                   // elements fm the stateStack:
        auto top__(size_t shift = 0) const;

        template<int>   
        auto &top__();

    private:
        void checkStackSize();
        void consumed();

        StateTuple &top();
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
inline \@Base::StateTuple &\@Base::top()
{
    return d_stateStack[d_stackIdx];
}

template<int idx>
inline auto \@Base::top__(size_t shift) const
{
    return std::get<idx>(d_stateStack[ d_stackIdx - shift ]);
}

template<int idx>
inline auto &\@Base::top__()
{
    return std::get<idx>(d_stateStack[ d_stackIdx ]);
}

// hdr/msgidx
inline size_t \@Base::msgIdx__() const
{
    return top__<1>();
}

inline void \@Base::msgIdx__(size_t idx)
{
    top__<1>() = idx;
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

// hdr/token
inline int \@Base::token__() const
{
    return d_reducedToken != _UNDETERMINED_ ? d_reducedToken : d_token;
}
// hdr/vs
inline \@Base::STYPE__ &\@Base::vs__(size_t idx) 
{
    return std::get<3>(*(d_vsp - idx));
}

// hdr/tail
// For convenience, when including ParserBase.h its symbols are available as
// symbols in the class Parser, too.
#define \@ \@Base

$insert namespace-close

#endif
