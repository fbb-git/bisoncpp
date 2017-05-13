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

        int d_stackIdx__ = -1;
        std::vector<StatePair>   d_stateStack__;

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

        bool        d_actionCases__ = false;    // set by options/directives
        bool        d_debug__ = true;
        size_t      d_requiredTokens__;

        size_t      d_nErrors__;                // initialized by clearin()
        size_t      d_acceptedTokens__;
        int         d_token__;
        size_t      d_state__;

        StatePair *d_vsp__;           // points to the topmost value stack

        STYPE__     d_val__;

        TokenPair   d_next__;

        bool        d_terminalToken__;
        bool        d_recovery__;

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
        STYPE__ &vs__(size_t idx);      // value stack element idx 
            // counts back fm the current element in the production rule.
            // E.g.:    rule: item1 item2 item3 {}
            //                  3     2     1    0

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
// hdr/actioncases
inline bool \@Base::actionCases() const
{
    return d_actionCases__;
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
// hdr/vs
inline \@Base::STYPE__ &\@Base::vs__(size_t idx) 
{
//    return *(d_vsp__ - idx);
    return (d_vsp__ - idx)->second;
}
// hdr/tail
// For convenience, when including ParserBase.h its symbols are available as
// symbols in the class Parser, too.
#define \@ \@Base

$insert namespace-close

#endif


