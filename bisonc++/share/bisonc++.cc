$insert class.ih

$insert debugincludes

namespace // anonymous
{
    enum ReservedTokens
    {
       PARSE_ACCEPT     = 0,   // `ACCEPT' TRANSITION
       _UNDETERMINED_   = -2,
       _EOF_            = -1,
       _error_          = 256,
    };
    enum StateType       // modify data.cc when this enum changes
    {
        NORMAL,
        HAS_ERROR_ITEM,
        IS_ERROR_STATE,
    };    
    struct PI   // Production Info
    {
        unsigned d_nonTerm; // identification number of this production's
                            // non-terminal 
        unsigned d_size;    // number of elements in this production 
    };

    struct SR   // Shift Reduce info
    {
        union
        {
            int _field_1_;      // initializer, allowing initializations 
                                // of the SR s_[] arrays
            StateType   d_type;
            unsigned    d_symbol;  
            int         d_token;
        };
        union
        {
            int _field_2_;

            int d_lastIdx;          // if negative, the state uses SHIFT
            int d_action;           // may be negative (reduce), 
                                    // postive (shift) or 0 (accept)
            unsigned d_errorState;  // used with Error states
        };
        // identification number (value) of a terminal
        // (action table) or non-terminal (goto table). In
        // SR arrays d_symbol of the first SR element defines the state's
        // type, while d_action holds the last element's index. The field
        // d_symbol of the last element of an SR array will contain the
        // last retrieved token and is used to speed up the seach. If the
        // last element's d_action field is non-negative, it is the state
        // to go to when an error is encountered. In that case, the stack
        // is reduced to this state (so, to 0 at the stacktop with with
        // s_0, etc.) and the indicated state is pushed on the stack,
        // representing shifting `error'. Then, the error routine will
        // continue to retrieve tokens from the input until the next
        // transition is possible from that state, and thus error recovery
        // has been performed
        // So:
        //      s_x[] = 
        //      {
        //          {state-type,        idx of last element},
        //          {symbol,            < 0: reduce, >= 0: next state},
        //          ...
        //          {set to last retrieved token, 
        //                              next state if >= 0 on error},
        //      }
    };

$insert 4 staticdata 

} // anonymous namespace ends

$insert namespace-open

// If the parser call uses arguments, then provide an overloaded function.
// The code below doesn't rely on parameters, so no arguments are required.
// Furthermore, parse uses a function try block to allow us to do
// ACCEPT and ABORT from anywhere, even from within members called
// by actions, simply throwing the appropriate exceptions.

@Base::@Base()
:
    d_stackIdx(-1),
$insert 4 debuginit
    d_nErrors(0),
    d_token(_UNDETERMINED_)
{}

void @Base::ABORT() const throw(Return) 
{
$insert 4 debug "Parsing unsuccessful (ABORT)"
    throw PARSE_ABORT;
}

void @Base::ACCEPT() const throw(Return)
{
$insert 4 debug "Parsing successful (ACCEPT)"
    throw PARSE_ACCEPT;
}

void @Base::ERROR() const throw(ErrorRecovery)
{
$insert 4 debug "Forced error condition"
    throw UNEXPECTED_TOKEN;
}

void @Base::clearin()
{
    d_token = _UNDETERMINED_;
}

$insert debugfunctions

void @Base::push(unsigned state)
{
    if (static_cast<unsigned>(d_stackIdx + 1) == d_stateStack.size())
    {
        unsigned newSize = d_stackIdx + 5;
        d_stateStack.resize(newSize);
        d_valueStack.resize(newSize);
$insert 8 LTYPEresize
    }
    ++d_stackIdx;
    d_stateStack[d_stackIdx] = d_state = state;
    *(d_vsp = &d_valueStack[d_stackIdx]) = d_val;
$insert 4 LTYPEpush
$insert 4 debug  "Pushed state " << state
}

void @Base::pop(unsigned count)
{
    d_stackIdx -= count;
    d_state = d_stateStack[d_stackIdx];
    d_vsp = &d_valueStack[d_stackIdx];
$insert 4 LTYPEpop
$insert 4 debug  "Popped " << count << " elements off the state stack." +
$insert 4 debug  " Next state: " << d_state
}

unsigned @Base::top() const
{
    if (d_stackIdx < 0)
    {
$insert 8 debug "Internal error: stack underflow"
        throw DEFAULT_RECOVERY_MODE;
    }

    return d_stateStack[d_stackIdx];
}

unsigned @Base::reduce(PI const &pi)
{
$insert 4 debug "Reduce according to production " << (&pi - s_productionInfo)

    pop(pi.d_size);

$insert 4 debug "Reduced to non-terminal " << pi.d_nonTerm +
$insert 4 debug ". Next token: " << symbol(pi.d_nonTerm)

    return pi.d_nonTerm;
}

void @::executeAction(int production)
{
$insert 4 debug "Executing action of production rule " << production
    switch (production)
    {
$insert 8 actioncases
    }
}

void @::nextToken()
{
    d_token = lex();
    print();
$insert 4 debug "Retrieved token value " << d_token
    if (d_token <= 0)
        d_token = _EOF_;

$insert 4 debug "Next token: " << symbol(d_token)
}

// if the final transition is negative, then we should reduce by the rule
// given by its positive value
int @::lookup()
{
    SR *sr = s_state[d_state];

    int lastIdx = sr->d_lastIdx;        // sentinel-index in the SR_ array

    SR *lastElementPtr = sr + lastIdx;

$insert 4 debug "In state " << d_state << " token = " << symbol(token)

    bool retry = false;
    while (true)
    {
        lastElementPtr->d_token = d_token;  // set search-token
        
        SR *elementPtr = sr + 1;
        while (elementPtr->d_token != token)
            ++elementPtr;
    
        if 
        (
            elementPtr != lastElementPtr    // found the token
            ||                      
            lastElementPtr->d_action        // or a reduction (because it's
        )                                   // the last element)
        {
$insert 4 debug "lookup() returns " << elementPtr->d_action
            return elementPtr->d_action;    // then return the required action
        }

        if (!retry)
        {
$insert 8 debug " token " symbol(d_token) << " not found. Trying next token"
            nextToken();
            retry = true;
            continue;
        }

        // In this case, the state did not have a a default reduce
$insert 8 debug "In state " << d_state << " token " +
$insert 8 debug  symbol(d_token) << " unexpected. Retry exhausted."
        throw UNEXPECTED_TOKEN;
    }
}

    // When an error has occurred, pop elements off the stack until the top
    // state has an error-transition. If none is found, the default recovery
    // mode (which is to abort) is activated. 
    //
    // If an error state is found, then that state's last SR element holds at
    // its d_errorState field the state to go to on `error'.  That state is
    // pushed on the state-stack, to become the next state. 
    //
    // In that state, the token (causing the error) is skipped and subsequent
    // tokens (retrieved from the input) are looked up. If a match is found,
    // then from this point parsing continues. 
    //
    // If EOF is encountered without being appropriate for the current state,
    // then the error recovery will fall back to the default recovery mode.
    // (i.e., parsing terminates)
unsigned @::errorRecovery()
try
{
    ++d_nErrors;

    error("Syntax error");
$insert 4 debug d_nErrors << " error(s) so far"

    while (s_state[top()][0].d_type != HAS_ERROR_ITEM)
        pop();

    push(lookup(_error_));                  // push the error state

    while (true)
    {
            // if on entry here token is already EOF then we've been here 
            // probably before: _error_ accepts EOF, but the state using
            // error nevertheless doesn't. In that case parsing terminates 
        if (d_token == _EOF_)
        {
$insert 16 debug "End of input unexpectedly reached"
            throw DEFAULT_RECOVERY_MODE;
        }
        try
        {
            nextToken();
            lookup(d_token);
$insert 12 debug "Successful error recovery"
            return d_token;
        }
        catch (...)
        {
        }
    }
}
catch (ErrorRecovery)       // This means: DEFAULT_RECOVERY_MODE
{
    ABORT();
    return 0;               // not reached. Inserted to prevent complaints
}                           // from the compiler

    // The parsing algorithm:
    // Initially, state 0 is pushed on the stack, and the first token is
    // obtained. The stack's top element is used to access the current state's
    // SR_ array.
    // Then, in an eternal loop:
    //  1.  The current token is stored in the final element's d_token
    //      field of the state's SR_ array.
    //  2.  The current token is located in the state's SR_ array
    //  3a. At `shift': the next token is retrieved, and the next state is
    //      pushed on the stack
    //  3b. At `reduce': 
    //          1. the rule's action is executed
    //          2. #-elements of the rule to reduce to are popped off
    //             the stack, the rule's lhs becomes the current token
    //  3c. At `PARSE_ACCEPT': parse() returns `ACCEPT'
    //
int @::parse()
try 
{
$insert 4 debug "Parsing starts"
    push(0);                                // initial state
    d_token = _UNDETERMINED_;               // initial token: unknown

    while (true)
    {
        try
        {
            int action = lookup(d_token);   // lookup token in d_state

            if (action > 0)                 // push a new state
            {
$insert 16 debug "SHIFT action"
                push(action);
                d_token = _UNDETERMINED_;   // and reset the token
            }
            else if (action < 0)
            {
$insert 16 debug "REDUCE action"
                executeAction(-action);
                d_token = reduce(s_productionInfo[-action]); 
            }
            else 
                ACCEPT();
        }
        catch (ErrorRecovery)
        {
            d_token = errorRecovery();
        }
    }
}
catch (Return retValue)
{
$insert 4 debug "parse() returns " << retValue
    return retValue;
}

$insert namespace-close
