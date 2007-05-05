$insert class.ih

// The FIRST element of SR arrays shown below uses `d_type', defining the
// state's type, and `d_lastIdx' containing the last element's index. If
// d_lastIdx contains the REQ_TOKEN bitflag (see below) then the state needs
// a token: if in this state d_token is _UNDETERMINED_, nextToken() will be
// called

// The LAST element of SR arrays uses `d_token' containing the last retrieved
// token to speed up the (linear) seach.  Except for the first element of SR
// arrays, the field `d_action' is used to determine what to do next. If
// positive, it represents the next state (used with SHIFT); if zero, it
// indicates `ACCEPT', if negative, -d_action represents the number of the
// rule to reduce to.

// `lookup()' tries to find d_token in the current SR array. If it fails, and
// there is no default reduction UNEXPECTED_TOKEN is thrown, which is then
// caught by the error-recovery function.

// The error-recovery function will pop elements off the stack until a state
// having bit flag ERR_ITEM is found. This state has a transition on _error_
// which is applied. In this _error_ state, while the current token is not a
// proper continuation, new tokens are obtained by nextToken(). If such a
// token is found, error recovery is successful and the token is
// handled according to the error state's SR table and parsing continues.

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
// Last element:    {set to d_token,    action to perform}
//      }

$insert debugincludes

namespace // anonymous
{
    char author[] = "Frank B. Brokken (f.b.brokken@rug.nl)";

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
    struct PI   // Production Info
    {
        size_t d_nonTerm; // identification number of this production's
                            // non-terminal 
        size_t d_size;    // number of elements in this production 
    };

    struct SR   // Shift Reduce info, see its description above
    {
        union
        {
            int _field_1_;      // initializer, allowing initializations 
                                // of the SR s_[] arrays
            int d_type;
            int d_token;
        };
        union
        {
            int _field_2_;

            int d_lastIdx;          // if negative, the state uses SHIFT
            int d_action;           // may be negative (reduce), 
                                    // postive (shift), or 0 (accept)
            size_t d_errorState;  // used with Error states
        };
    };

$insert 4 staticdata 

$insert namespace-open

// If the parsing function call uses arguments, then provide an overloaded
// function.  The code below doesn't rely on parameters, so no arguments are
// required.  Furthermore, parse uses a function try block to allow us to do
// ACCEPT and ABORT from anywhere, even from within members called by actions,
// simply throwing the appropriate exceptions.

\@Base::\@Base()
:
    d_stackIdx(-1),
$insert 4 debuginit
    d_nErrors(0),
    d_token(_UNDETERMINED_),
    d_nextToken(_UNDETERMINED_)
{}

$insert debugfunctions

void \@Base::clearin()
{
    d_token = d_nextToken = _UNDETERMINED_;
}

void \@Base::push(size_t state)
{
    if (static_cast<size_t>(d_stackIdx + 1) == d_stateStack.size())
    {
        size_t newSize = d_stackIdx + 5;
        d_stateStack.resize(newSize);
        d_valueStack.resize(newSize);
$insert 8 LTYPEresize
    }
    ++d_stackIdx;
    d_stateStack[d_stackIdx] = d_state = state;
    *(d_vsp = &d_valueStack[d_stackIdx]) = d_val;
$insert 4 LTYPEpush
$insert 4 debug  "push(state " << state << ")"
}

void \@Base::pop(size_t count)
{
$insert 4 debug "pop(" << count << ") from stack having size " << (d_stackIdx + 1)
    if (d_stackIdx < static_cast<int>(count))
    {
        std::cerr << "\n"
            "Terminating parse(): unrecoverable input error at token " << 
            symbol(d_token) << "\n";
        ABORT();
    }

    d_stackIdx -= count;
    d_state = d_stateStack[d_stackIdx];
    d_vsp = &d_valueStack[d_stackIdx];
$insert 4 LTYPEpop
$insert 4 debug "pop(): next state: " << d_state << ", token: " << symbol(d_token)
}

inline size_t \@Base::top() const
{
    return d_stateStack[d_stackIdx];
}

inline void \@Base::checkEOF() const
{
    if (d_token == _EOF_)
    {
$insert 8 debug "errorRecovery(): unexpected End of input"
        throw DEFAULT_RECOVERY_MODE;
    }
}

inline void \@Base::reduce(PI const &pi)
{
    d_token = pi.d_nonTerm;

$insert 4 debug "reduce(): by rule " << (&pi - s_productionInfo) +
$insert 4 debug " to N-terminal " << symbol(d_token)

    pop(pi.d_size);
}

void \@::executeAction(int production)
{
$insert 4 debug "executeAction(): of rule " << production << " ..."
    switch (production)
    {
$insert 8 actioncases
    }
$insert 4 debug "... action of rule " << production << " completed"
}

// If d_token is _UNDETERMINED_ then if d_nextToken is _UNDETERMINED_ another
// token is obtained from lex(). Then d_nextToken is assigned to d_token.
void \@::nextToken()
{
    if (d_token != _UNDETERMINED_)          // no need for a token: got one
        return;                             // already

    if (d_nextToken == _UNDETERMINED_)
    {
        d_nextToken = lex();
$insert 8 debug "nextToken(): retrieved d_nextToken " << symbol(d_nextToken)
    }
    print();
    if (d_nextToken <= 0)
        d_nextToken = _EOF_;

    d_token = d_nextToken;
$insert 4 debug "nextToken(): using token " << symbol(d_token)
}

// if the final transition is negative, then we should reduce by the rule
// given by its positive value
int \@::lookup(bool recovery)
{
    SR *sr = s_state[d_state];

    int lastIdx = sr->d_lastIdx;        // sentinel-index in the SR_ array

    SR *lastElementPtr = sr + lastIdx;

    lastElementPtr->d_token = d_token;  // set search-token
    
    SR *elementPtr = sr + 1;            // start the search at s_xx[1]
    while (elementPtr->d_token != d_token)
        ++elementPtr;

$insert 8 debug ""

    if (elementPtr == lastElementPtr)   // reached the last element
    {
        if (elementPtr->d_action < 0)   // default reduction
        {
$insert 8 debug "lookup(" << d_state << ", " << symbol(d_token) +
$insert 8 debug "): Default reduction by rule " << -elementPtr->d_action
            return elementPtr->d_action;                
        }
$insert 8 debug "lookup(" << d_state << ", " << symbol(d_token) << "): Not " +
$insert 8 debug "found. " << (recovery ? "Continue" : "Start") << " error recovery." 

        // No default reduction, so token not found, so error.
        throw UNEXPECTED_TOKEN;
    }

    // not at the last element: inspect the nature of the action
    // (< 0: reduce, 0: ACCEPT, > 0: shift)

    int action = elementPtr->d_action;

    if (action < 0)             // a reduction is found
    {
$insert 8 debug "lookup(" << d_state << ", " << symbol(d_token) +
$insert 8 debug "): Reduce by rule " << -action
    }
    else if (action == 0)
    {
$insert 8 debug "lookup(" << d_state << ", " << symbol(d_token) << "): ACCEPT"
    }
    else 
    {
$insert 8 debug "lookup(" << d_state << ", " << symbol(d_token) +
$insert 8 debug "): Shift " << action << " (" << symbol(d_token) << " processed)"
    }
    return action;
}

    // When an error has occurred, pop elements off the stack until the top
    // state has an error-item. If none is found, the default recovery
    // mode (which is to abort) is activated. 
    //
    // If EOF is encountered without being appropriate for the current state,
    // then the error recovery will fall back to the default recovery mode.
    // (i.e., parsing terminates)
void \@::errorRecovery()
try
{
    ++d_nErrors;

    error("Syntax error");
$insert 4 debug "errorRecovery(): " << d_nErrors << " error(s) so far. State = " << top()

    while (not (s_state[top()][0].d_type & ERR_ITEM))
    {
$insert 8 debug "errorRecovery(): pop state " << top()
        pop();
    }

        // if on entry here token is already EOF then we've probably been 
        // here before: _error_ accepts EOF, but the state using
        // error nevertheless doesn't. In that case parsing terminates 
    checkEOF();

    d_token = _error_;                      // specify _error_ as next token
    push(lookup(true));                     // push the error state

    // In the error state, lookup a token with which we can proceed.
    // It may be a reduce, but normally a shift is indicated
    // If a token is seen which doesn't fit, the catch below will catch the
    // execption thrown by lookup()

    while (true)
    {
            // if on entry here token is already EOF then we've probably been 
            // here before: _error_ accepts EOF, but the state using
            // error nevertheless doesn't. In that case parsing terminates 
        checkEOF();
        try
        {
            d_token = _UNDETERMINED_;
            nextToken();
            int action = lookup(true);
                                            // eat the token
            d_token = d_nextToken = _UNDETERMINED_;

            if (action > 0)                 // push a new state
            {
$insert 16 debug "errorRecovery() SUCCEEDED: push state " << action << ", token cleared "
                push(action);
            }
            else if (action < 0)
            {
                executeAction(-action);     // the error's action

                                            // next token is the rule's LHS
                reduce(s_productionInfo[-action]); 
$insert 16 debug "errorRecovery() SUCCEEDED: reduce by rule " << -action << ", token = " +
$insert 16 debug symbol(d_token)
            }
            return;
        }
        catch (...)
        {
            if (d_token == _EOF_)
                continue;
                                            // eat the token
            d_token = d_nextToken = _UNDETERMINED_;
        }
    }
}
catch (ErrorRecovery)       // This is: DEFAULT_RECOVERY_MODE
{
    ABORT();
}

    // The parsing algorithm:
    // Initially, state 0 is pushed on the stack, and d_token as well as
    // d_nextToken are initialized to _UNDETERMINED_. 
    //
    // Then, in an eternal loop:
    //
    //  1. If a state does not have REQ_TOKEN no token is assigned to
    //     d_token. If the state has REQ_TOKEN, nextToken() is called to
    //      determine d_nextToken and d_token is set to
    //     d_nextToken. nextToken() will not call lex() unless d_nextToken is 
    //     _UNDETERMINED_. 
    //
    //  2. lookup() is called: 
    //     d_token is stored in the final element's d_token field of the
    //     state's SR_ array. 
    //
    //  3. The current token is looked up in the state's SR_ array
    //
    //  4. Depending on the result of the lookup() function the next state is
    //     shifted on the parser's stack, a reduction by some rule is applied,
    //     or the parsing function returns ACCEPT(). When a reduction is
    //     called for, any action that may have been defined for that
    //     reduction is executed.
    //
    //  5. An error occurs if d_token is not found, and the state has no
    //     default reduction. Error handling was described at the top of this
    //     file.

int \@::parse()
try 
{
$insert 4 debug "parse(): Parsing starts"
    push(0);                                // initial state
    clearin();                              // clear the tokens.

    while (true)
    {
        try
        {
            if (s_state[d_state]->d_type & REQ_TOKEN)
                nextToken();                // obtain next token


            int action = lookup(false);     // lookup d_token in d_state

            if (action > 0)                 // SHIFT: push a new state
            {
                push(action);
                if (d_token == d_nextToken) // consumed a terminal token.
                    d_nextToken = _UNDETERMINED_;

                d_token = _UNDETERMINED_;   // try to process the next token
            }
            else if (action < 0)            // REDUCE: execute and pop.
            {
                executeAction(-action);
                                            // next token is the rule's LHS
                reduce(s_productionInfo[-action]); 
            }
            else 
                ACCEPT();
        }
        catch (ErrorRecovery)
        {
            errorRecovery();
        }
    }
}
catch (Return retValue)
{
$insert 4 debug "parse(): returns " << retValue
    return retValue;
}

$insert namespace-close
