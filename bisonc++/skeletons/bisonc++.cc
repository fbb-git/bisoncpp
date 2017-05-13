// base/comment

$insert class.ih

// The FIRST element of SR arrays shown below uses `d_type', defining the
// state's type, and `d_lastIdx' containing the last element's index. If
// d_lastIdx contains the REQ_TOKEN bitflag (see below) then the state needs
// a token: if in this state d_token__ is _UNDETERMINED_, nextToken() will be
// called

// The LAST element of SR arrays uses `d_token' containing the last retrieved
// token to speed up the (linear) seach.  Except for the first element of SR
// arrays, the field `d_action' is used to determine what to do next. If
// positive, it represents the next state (used with SHIFT); if zero, it
// indicates `ACCEPT', if negative, -d_action represents the number of the
// rule to reduce to.

// `lookup()' tries to find d_token__ in the current SR array. If it fails, and
// there is no default reduction UNEXPECTED_TOKEN__ is thrown, which is then
// caught by the error-recovery function.

// The error-recovery function will pop elements off the stack until a state
// having bit flag ERR_ITEM is found. This state has a transition on _error_
// which is applied. In this _error_ state, while the current token is not a
// proper continuation, new tokens are obtained by nextToken(). If such a
// token is found, error recovery is successful and the token is
// handled according to the error state's SR table and parsing continues.
// During error recovery semantic actions are ignored.

// A state flagged with the DEF_RED flag will perform a default
// reduction if no other continuations are available for the current token.

// The ACCEPT STATE never shows a default reduction: when it is reached the
// parser returns ACCEPT(). During the grammar
// analysis phase a default reduction may have been defined, but it is
// removed during the state-definition phase.

// So:
//      s_x[] = 
//      {
//                  [_field_1_]         [_field_2_]
//
// First element:   {state-type,        idx of last element},
// Other elements:  {required token,    action to perform},
//                                      ( < 0: reduce, 
//                                          0: ACCEPT,
//                                        > 0: next state)
// Last element:    {set to d_token__,    action to perform}
//      }

// When the --thread-safe option is specified, all static data are defined as
// const. If --thread-safe is not provided, the state-tables are not defined
// as const, since the lookup() function below will modify them

// base/declarations
$insert debugincludes

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
    enum StateType       // modify statetype/data.cc when this enum changes
    {
        NORMAL,
        ERR_ITEM,
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
            int       d_token;
        };
        union
        {
            int _field_2_;

            int d_lastIdx;          // if negative, the state uses SHIFT
            int d_action;           // may be negative (reduce), 
                                    // postive (shift), or 0 (accept)
        };
    };

$insert 4 staticdata 

$insert namespace-open

$insert polymorphicCode

// If the parsing function call (i.e., parse()' needs arguments, then provide
// an overloaded function.  The code below doesn't rely on parameters, so no
// arguments are required.  Furthermore, parse uses a function try block to
// allow us to do ACCEPT and ABORT from anywhere, even from within members
// called by actions, simply throwing the appropriate exceptions.


// base/base1
\@Base::\@Base()
:
$insert 4 baseclasscode
}

// base/clearin
void \@Base::clearin__()
{
    d_nErrors__ = 0;
    d_stackIdx = -1;
    d_stateStack.clear();
    d_token__ = _UNDETERMINED_;
    d_next__ = TokenPair{ _UNDETERMINED_, STYPE__{} };
    d_recovery__ = false;
    d_acceptedTokens__ = d_requiredTokens__;
    d_val__ = STYPE__{};

    push__(0);
}

// base/debugfunctions
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

// base/lookup
int \@Base::lookup__() const
{
    // if the final transition is negative, then we should reduce by the rule
    // given by its positive value.

    SR__ const *sr = s_state[d_state__];
    SR__ const *last = sr + sr->d_lastIdx;

    for ( ; ++sr != last; )           // visit all but the last SR entries
    {
        if (sr->d_token == d_token__)
            return sr->d_action;
    }

    if (sr == last)   // reached the last element
    {
        if (sr->d_action < 0)   // default reduction
        {
$insert 12 debug "\nLOOKUP: [" << d_state__ << ", " << symbol__(d_token__) << "] -> default reduce using rule " << -sr->d_action
            return sr->d_action;                
        }

        // No default reduction, so token not found, so error.
        throw UNEXPECTED_TOKEN__;
    }

    // not at the last element: inspect the nature of the action
    // (< 0: reduce, 0: ACCEPT, > 0: shift)

    int action = sr->d_action;

$insert 0 debuglookup

    return action;
}

// base/pop
void \@Base::pop__(size_t count)
{
$insert 4 debug "pop " << count << " elements from the stack having size " << (d_stackIdx + 1)
    if (d_stackIdx < static_cast<int>(count))
    {
$insert 8 debug "Terminating parse(): state stack underflow  at token " << symbol__(d_token__)
        ABORT();
    }

    d_stackIdx -= count;
    d_state__ = d_stateStack[d_stackIdx].first;
    d_vsp__ = &d_stateStack[d_stackIdx];

$insert 4 LTYPEpop
$insert 4 debug "next: [" << d_state__ << ", " << symbol__(d_token__) << ']' << stype__(". Semantic: ", vs__(0))
}

// base/poptoken
void \@Base::popToken__()
{
    d_token__ = d_next__.first;
    d_val__ = std::move(d_next__.second);

    d_next__.first = _UNDETERMINED_;
}

// base/push
void \@Base::push__(size_t state)
{
    size_t currentSize = d_stateStack.size();
    if (static_cast<size_t>(d_stackIdx + 1) == currentSize)
    {
        size_t newSize = currentSize + STACK_EXPANSION__;
        d_stateStack.resize(newSize);
$insert 8 LTYPEresize
    }

$insert 4 LTYPEpush

    ++d_stackIdx;
    d_stateStack[d_stackIdx] = 
                    StatePair{ d_state__ = state, std::move(d_val__) };

    d_vsp__ = &d_stateStack[d_stackIdx];

    if (d_stackIdx == 0)
    {
$insert 4 debug  "\nPUSH 0 (initializing the state stack)"
    }
    else
    {
$insert 4 debug  "\nPUSH:   [" << (d_vsp__ - 1)->first << ", " << symbol__(d_token__) << "] -> " << state << stype__(" (semantic TOS = ", d_val__, ")")
    }
}

// base/pushtoken
void \@Base::pushToken__(int token)
{
    d_next__ = TokenPair{ d_token__, std::move(d_val__) };
    d_token__ = token;
}

// base/redotoken
void \@Base::redoToken__()
{
    if (d_token__ != _UNDETERMINED_)
        pushToken__(d_token__);
}

// base/reduce
void \@Base::reduce__(int rule)
{
    PI__ const &pi = s_productionInfo[rule];

    d_token__ = pi.d_nonTerm;
$insert 4 debug "rule " << (&pi - s_productionInfo) << ": pop " << pi.d_size << " elements. Next will be: [" << d_stateStack[d_stackIdx - pi.d_size].first << ", " << symbol__(d_token__) << ']'
    pop__(pi.d_size);

    d_terminalToken__ = false;
}

// base/shift
void \@Base::shift__(int action)
{
    push__(action);
    popToken__();               // token processed

    if (d_recovery__ and d_terminalToken__)
    {
$insert 8 debug "ERROR RECOVERED: next state " << action
        d_recovery__ = false;
        d_acceptedTokens__ = 0;
    }
}

// base/top
inline size_t \@Base::top__() const
{
    return d_stateStack[d_stackIdx].first;
}

// derived/errorrecovery
void \@::errorRecovery__()
{
    // When an error has occurred, pop elements off the stack until the top
    // state has an error-item. If none is found, the default recovery
    // mode (which is to abort) is activated. 
    //
    // If EOF is encountered without being appropriate for the current state,
    // then the error recovery will fall back to the default recovery mode.
    // (i.e., parsing terminates)

$insert 4 debug "\nERROR:  [" << top__() << ", " << symbol__(d_token__) << "] -> ??. Errors: " << (d_nErrors__ + 1)


    if (d_acceptedTokens__ >= d_requiredTokens__)// only generate an error-
    {                                           // message if enough tokens 
        ++d_nErrors__;                          // were accepted. Otherwise
        error();                                // simply skip input
$insert 8 errorverbose
    }

    // get the error state
    while (not (s_state[top__()][0].d_type & ERR_ITEM))
    {
$insert 8 debug "pop state: " << top__() << " (not an ERROR state)"
        pop__();
    }
$insert 4 debug "Reached ERROR state " << top__()

    // In the error state, looking up a token allows us to proceed.
    // Continuation may be require multiple reductions, but eventually a
    // terminal-token shift is used. See nextCycle__ for details.

    int lastToken = d_token__;                  // give the unexpected token a
                                                // chance to be processed
                                                // again.

    pushToken__(_error_);                       // specify _error_ as next token
    push__(lookup__());                         // push the error state

    d_token__ = lastToken;                      // reactivate the unexpected
                                                // token (we're now in an
                                                // ERROR state).

    d_recovery__ = true;
}

// derived/executeaction
void \@::executeAction__(int production)
try
{
    if (d_token__ != _UNDETERMINED_)
        pushToken__(d_token__);     // save an already available token
$insert 4 debug "execute action " << production << " ..."
$insert executeactioncases
    switch (production)
    {
$insert 8 actioncases
    }
$insert 4 debug "... completed" << stype__(", semantic: ", vs__(0))
}
catch (std::exception const &exc)
{
    exceptionHandler(exc);
}

// derived/nextcycle
void \@::nextCycle__()
try
{
    if (s_state[d_state__]->d_type & REQ_TOKEN)
        nextToken__();              // obtain next token


    int action = lookup__();        // lookup d_token__ in d_state__

    if (action > 0)                 // SHIFT: push a new state
    {
        shift__(action);
        return;
    }

    if (action < 0)            // REDUCE: execute and pop.
    {
$insert 8 debug "\nREDUCE: rule " << -action

        if (d_recovery__)
            redoToken__();
        else
            executeAction__(-action);
                                            // next token is the rule's LHS
        reduce__(-action); 
        return;
    }

    if (d_recovery__)
        ABORT();
    else 
        ACCEPT();
}
catch (ErrorRecovery__)
{
    if (not d_recovery__)
        errorRecovery__();
    else
    {
        if (d_token__ == _EOF_)
            ABORT();
        popToken__();               // skip the failing token
    }
}


// derived/nexttoken
void \@::nextToken__()
{
    // If d_token__ is _UNDETERMINED_ then if d_nextToken__ is _UNDETERMINED_ 
    // another token is obtained from lex(). Then d_nextToken__ is assigned to
    // d_token__.

    if (d_token__ != _UNDETERMINED_)        // no need for a token: got one
    {
$insert 8 debug "available token " << symbol__(d_token__)
        return;                             // already
    }

    if (d_next__.first != _UNDETERMINED_)
    {
        popToken__();                       // consume pending token
$insert 8 debug "retrieved token " << symbol__(d_token__) << stype__(", semantic = ", d_val__)
    }
    else
    {
        ++d_acceptedTokens__;               // accept another token (see
                                            // errorRecover())
        d_token__ = lex();
        if (d_token__ <= 0)
            d_token__ = _EOF_;
        d_terminalToken__ = true;
        print__();
$insert 8 debug "scanner token " << symbol__(d_token__)
    }
    print();
}

// derived/print
void \@::print__()
{
$insert print
}

// derived/parse
int \@::parse()
try 
{
    // The parsing algorithm:
    // Initially, state 0 is pushed on the stack, and all relevant variables
    // are initialized by Base::clearin__.
    //
    // Then, in an eternal loop:
    //
    //  1. If a state is a REQ_TOKEN type, then the next token is obtained
    //     from nextToken().  This may very well be the currently available
    //     token. When retrieving a terminal token d_terminal is set to true.
    //
    //  2. lookup() is called, d_token__ is looked up in the current state's
    //     SR_ array.
    //
    //  4. Depending on the result of the lookup() function the next state is
    //     shifted on the parser's stack, a reduction by some rule is applied,
    //     or the parsing function returns ACCEPT(). When a reduction is
    //     called for, any action that may have been defined for that
    //     reduction is executed.
    //
    //  5. An error occurs if d_token__ is not found, and the state has no
    //     default reduction.

$insert 4 debug "parse(): Parsing starts"
    clearin__();                            // initialize, push(0)

    while (true)
    {
$insert prompt
        nextCycle__();
    }
}
catch (Return__ retValue)
{
$insert 4 debug "parse(): returns " << retValue << " or " << d_nErrors__ 
    return retValue or d_nErrors__;
}


// derived/tail

$insert namespace-close

