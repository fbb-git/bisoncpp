$insert class.ih
$insert debugincludes
#include <unordered_set>

namespace // anonymous
{
    char const author[] = "Frank B. Brokken (f.b.brokken@rug.nl)";

    enum ReservedTokens
    {
        PARSE_ACCEPT     = 0,   // `ACCEPT' TRANSITION
        _UNDETERMINED_   = -2,
        _EOF_            = -1,
        _error_          = 256
    };
    enum StateType      // modify statetype/data.cc when this enum changes
    {
        NORMAL,
        ERR_ITEM,       // from here: StateType values are bit-flags
        REQ_TOKEN,
        ERR_REQ,    // ERR_ITEM | REQ_TOKEN
        DEF_RED,    // state having default reduction
        ERR_DEF,    // ERR_ITEM | DEF_RED
        REQ_DEF,    // REQ_TOKEN | DEF_RED
        ERR_REQ_DEF // ERR_ITEM | REQ_TOKEN | DEF_RED
    };    
    struct PI__     // Production Info
    {
        size_t d_nonTerm; // identification number of this production's
                            // non-terminal 
        size_t d_size;    // number of elements in this production 
    };

    struct SR__     // Shift Reduce info, see its description above
    {
        union
        {
            int _field_1_;      // initializer, allowing initializations 
                                // of the SR s_[] arrays
            StateType d_type;
            int d_token;
        };
        union
        {
            int _field_2_;

            int d_lastIdx;          // with s_X[0]: last s_X[] element

            int d_action;           // postive (shift), or 0 (accept)
                                    // s_X[ s_X[ lastIdx ] ].d_action: if 
                                    // negative: rule to reduce to
        };
        size_t d_error = 0;         // Idx in s_errorLA__, used by 
    };                              // error-states

$insert 4 staticdata 

$insert namespace-open

$insert polymorphicCode

// If the parsing function call uses arguments, then provide an overloaded
// function.  The code below doesn't rely on parameters, so no arguments are
// required.  Furthermore, parse uses a function try block to allow us to do
// ACCEPT and ABORT from anywhere, even from within members called by actions,
// simply throwing the appropriate exceptions.

\@Base::\@Base()
:
$insert 4 requiredtokens
    d_acceptedTokens__(d_requiredTokens__),
    d_token__(_UNDETERMINED_),
    d_nextToken__(_UNDETERMINED_)
{}

$insert debugfunctions

void \@Base::setDebug(bool mode)
{
    d_actionCases__ = false;
    d_debug__ = mode;
}

void \@Base::setDebug(DebugMode__ mode)
{
    d_actionCases__ = mode & ACTIONCASES;
    d_debug__ =       mode & ON;
}

void \@Base::print__()
{
$insert print
}

void \@Base::push__(size_t state)
{
    checkStackSize();

    size_t previous = 
            d_stackIdx__ == -1 ? 0 : d_stateStack__[d_stackIdx__].second;
    ++d_stackIdx__;
    d_stateStack__[d_stackIdx__] = 
            std::pair<size_t, size_t>{d_state__ = state, previous};

$insert 4 LTYPEpush
$insert 4 debug  "\npush state " << state << " with token: " << symbol__(d_token__) +
$insert 4 debug "; stack size = " << (d_stackIdx__ + 1) << stype__(". Semantic TOS value = ", d_val__)
    *(d_vsp__ = &d_valueStack__[d_stackIdx__]) = std::move(d_val__);
}

void \@Base::clearin__()
{
    d_tokenType__ = UNDEFINED__;
    push__(0);
}

void \@Base::checkStackSize()
{
    size_t currentSize = d_stateStack__.size();

    if (static_cast<size_t>(d_stackIdx__ + 1) == currentSize)
    {
        size_t newSize = currentSize + STACK_EXPANSION__;
        d_stateStack__.resize(newSize);
        if (d_valueStack__.capacity() >= newSize)
            d_valueStack__.resize(newSize);
        else
        {
            std::vector<STYPE__> enlarged(newSize);
            for (size_t idx = 0; idx != currentSize; ++idx)
                enlarged[idx] = std::move(d_valueStack__[idx]);
            d_valueStack__.swap(enlarged);
        }
    }
}

void \@Base::pop__(size_t count)
{
$insert 4 debug "\npop " << count << " state(s) " +
    if (d_stackIdx__ < static_cast<int>(count))
    {
$insert 8 debug ": internal error: stack underflow at token " << symbol__(d_token__)
        ABORT();
    }

    d_stackIdx__ -= count;
    d_state__ = d_stateStack__[d_stackIdx__].first;
    d_vsp__ = &d_valueStack__[d_stackIdx__];
$insert 4 debug ", state: " << d_state__ << ", token: " << symbol__(d_token__) << ", stack size: " << (d_stackIdx__ + 1)
$insert 4 LTYPEpop
}

inline size_t \@Base::top__() const
{
    return d_stateStack__[d_stackIdx__].first;
}

void \@::executeAction__(int production)
try
{
$insert 4 debug "\n    (actions for rule " << production <<  stype__(", top value of the semantic stack: ", *d_vsp__) << "..."
$insert executeactioncases
    switch (production)
    {
$insert 8 actioncases
    }
$insert 4 debug "... completed " <<   stype__(", returning semantic value ", *d_vsp__) << ')'
}
catch (std::exception const &exc)
{
$insert 4 debug "exception for rule " << production
    exceptionHandler__(exc);             // user code exception handler
}
catch (Return__ ret)
{
$insert 4 debug "rule " << production << " ends the parsing process"
    if (ret == PARSE_ERROR__)
        return;
    throw;
}

void \@::getToken__()
{ 
    if (d_nextToken__ == _UNDETERMINED_)
    {
        d_token__ = lex();
        if (d_token__ <= 0)
            d_token__ = _EOF_;
$insert 8 debug "got lex()" +
    }
    else
    {
        d_token__ = d_nextToken__;
        d_nextToken__ = _UNDETERMINED_;
$insert 8 debug "return saved" +
    }

$insert 4 debug " token " << symbol__(d_token__) << stype__(", semantic = ", d_val__)
    d_tokenType__ = TERMINAL__;
    ++d_acceptedTokens__;               // accept another token (see
                                        // errorRecover())
    print();
}

SR__ const *\@Base::findToken__() const // find the item defining an action for
{                                       // d_token__
    for (                           // visit all but the last SR entries
        SR__ const *sr = s_state[d_state__], *last = sr + sr->d_lastIdx;
            sr != last;
                ++sr
    )
    {
        if (sr->d_token == d_token__)
            return sr;
    }

    return 0;
}

SR__ const *\@Base::errorItem__()
{
    d_token__ = _error_;
    return findToken__();
}

inline void \@Base::reduce__(PI__ const &pi)
{
    d_token__ = pi.d_nonTerm;
    d_tokenType__ = NON_TERMINAL__;
    pop__(pi.d_size);
}

void \@::action__(SR__ const *elementPtr)
{
    int action = elementPtr->d_action;

    if (action == 0)            // accepting state
    {
$insert 8 debug "\nstate " << d_state__ << " with " << symbol__(d_token__) << ": normal end\n"
        if (d_nErrors__ == 0)
            ACCEPT();
        else
            ABORT();
    }
    
    if (action < 0)             // reduce according to rule -action
    {
        executeAction__(-action);
        reduce__(s_productionInfo[ -action ]);
        return;
    }

    push__(action);

    if (d_tokenType__ == TERMINAL__)        // terminal tokens are consumed.
    {
$insert 8 debug "   (consumed token " << symbol__(d_token__) << ')'
        d_tokenType__ = UNDEFINED__;
    }
}

void \@::errorRecovery__()
{
    // When an error has occurred, pop elements off the stack until the top
    // state has an error-item. If none is found, the default recovery
    // mode (which is to abort) is activated. 
    //
    // If EOF is encountered without being appropriate for the current state,
    // then the error recovery will fall back to the default recovery mode.
    // (i.e., parsing terminates)

$insert 4 debug "\nStarting error recovery in state " << d_state__ << " with token " << symbol__(d_token__)
    if (d_acceptedTokens__ >= d_requiredTokens__)// only generate an error-
    {                                           // message if enough tokens 
        ++d_nErrors__;                          // were accepted. Otherwise
        error();                                // simply skip input
    }

                                                // find the topmost ERR_ITEM
    while (not (s_state[top__()]->d_type & ERR_ITEM))
        pop__();

    SR__ const *elementPtr = errorItem__();

    std::unordered_set<int> &us = s_errorLA[ elementPtr->d_error ];

    do
        getToken__();
    while (us.find(d_token__) == us.end()); // find a continuation

$insert 4 debug "error recovered in state " << d_state__ << " with token " << symbol__(d_token__)
    action__(elementPtr);                   // perform the matching action
}

bool \@::defaultReduce__()
{
    SR__ const *sr = s_state[ d_state__ ];

$insert 4 debug "\n    state " << d_state__ << ": no action for token " << symbol__(d_token__)

    if (sr->d_type < DEF_RED)    // no default reduce
    {
$insert 8 debug "no default reduction in state " << d_state__
        return false;
    }

$insert 4 debug "\n    default reduction: state " << d_state__

    int action = -sr[ sr->d_lastIdx ].d_action;

    if (d_tokenType__ == TERMINAL__)    // push-back retrieved token
    {
        d_nextToken__ = d_token__;
$insert 8 debug "       saving available token " << symbol__(d_token__)
    }

    executeAction__(action);
    reduce__(s_productionInfo[ action ]);
    
$insert 4 debug "default reduction completed"
    return true;
}

void \@::nextCycle__()
{
$insert 4 debug ' '
    if (d_tokenType__ == UNDEFINED__)
        getToken__();

                                        // is there an action for this token?
    if (SR__ const *elementPtr = findToken__())   
        action__(elementPtr);           // yes: perform the action

    else if (not defaultReduce__())     // no default reduction?
    {
                                        // if a token can be requested:
        if (s_state[ d_state__ ]->d_type & REQ_TOKEN)
        {
$insert 12 debug "get token in state " << d_state__
            getToken__();               // get it.

                                        // find an action for this token    
            if (SR__ const *elementPtr = findToken__())   
            {
                action__(elementPtr);   // found one: perform the action
                return;
            }
        }
        errorRecovery__();              // no default reduction, no token:
                                        // recover from error
    }
}

int \@::parse()
try 
{
$insert 4 debug "parse(): starts"
    clearin__();                            // clear the tokens.

    while (true)
    {
        nextCycle__();
    }
}
catch (Return__ retValue)
{
$insert 4 debug "parse(): returns " << retValue
    return retValue;
}

$insert namespace-close


