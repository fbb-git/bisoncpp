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
    enum StateType       // modify state/data.cc when this enum changes
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
            int         d_token;
        };
        union
        {
            int _field_2_;

            int d_lastIdx;          // if negative, the state uses SHIFT
            int d_action;           // may be negative (reduce), 
                                    // postive (shift), or 0 (accept)
            unsigned d_errorState;  // used with Error states
        };
        // The FIRST element of SR arrays uses `d_type', defining the state's
        // type, and `d_lastIdx' containing the last element's index. 
        // The LAST element of SR arrays uses `d_token' containing the last
        // retrieved token (or _UNDETERMINED_ immediately following a SHIFT)
        // to speed up the (linear) seach. 
        // Except for the first element of SR arrays, the field `d_action' is
        // used to determine what to do next. If positive, it represents the
        // next state (used with SHIFT); if zero, it indicates `ACCEPT', if
        // negative, -d_action represents the number of the rule to reduce to.
        //
        // `lookup()' tries to find d_token in the current SR array. This may
        // succeed, even with token _UNDETERMINED_, if the current state
        // features a default reduce. If it fails, `nextToken()' is called
        // once to obtain the next token. If that token isn't found,
        // UNEXPECTED_TOKEN is thrown, which is then caught by the
        // error-recovery function. 
        //
        // The error-recovery function will pop elements off the stack until a
        // state having type HAS_ERROR_ITEM is found. In these states, input
        // can be SHIFT-ed repeatedly until a token is retrieved which is
        // found in the error state's SR table. In that case error recovery is
        // successful and the token is returned to the `parse()'
        // function. Since the stack has now been reduced to a state having an 
        // `error . TOKEN' item, TOKEN will be found in the current state, and
        // thus parsing may continue.
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

    bool retry = false;
    while (true)
    {
$insert 4 debug "In state " << d_state << " token = " << symbol(d_token)

        lastElementPtr->d_token = d_token;  // set search-token
        
        SR *elementPtr = sr + 1;
        while (elementPtr->d_token != d_token)
            ++elementPtr;
    
        if 
        (
            elementPtr != lastElementPtr    // found the token
            ||                      
            lastElementPtr->d_action < 0    // or a (default) reduction at
        )                                   // the last element)
        {
$insert 4 debug "lookup() returns " << elementPtr->d_action
            return elementPtr->d_action;    // then return the required action
        }

        if (!retry)
        {
$insert 8 debug " No token " << symbol(d_token) << ". Trying next token"
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
    // state has an error-item. If none is found, the default recovery
    // mode (which is to abort) is activated. 
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

    d_token = _error_;                      // specify _error_ as next token
    push(lookup());                         // push the error state

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
            lookup();
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
    // Initially, state 0 is pushed on the stack, and d_token is defined as
    // _UNDETERMINED_. 
    // The stack's top element is always used to access the current state's
    // SR_ array. 
    // Then, in an eternal loop:
    //  1.  The current token is stored in the final element's d_token
    //      field of the state's SR_ array.
    //  2.  The current token is located in the state's SR_ array
    //  3. If the token is found at the last element (so, the token wasn't
    //     really found since we've put it there intially) and the last
    //     element's action field is negative, a default reduce is
    //     performed. Otherwise, nextToken() is called ONCE to obtain the next
    //     token. If that token isn't found either, error-recovery starts.
    //  4. In general, if d_token was found:
    //  4a. Positive d_action values indicate `SHIFT': the next state is
    //     returned as d_action. It is pushed on the stack and d_token is set
    //     to _UNDETERMINED_ again.
    //  4b. Negative d_action values indicate `REDUCE': -d_action indicates
    //     the rule to reduce to, and:
    //          1. the rule's action is executed
    //          2. #-elements of the rule to reduce to are popped off
    //             the stack, the rule's LHS becomes the current token
    //  4c. Zero d_action values indicate `PARSE_ACCEPT': parse() returns 
    //      `ACCEPT', indicating successful parsing.
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
            int action = lookup();          // lookup token in d_state

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



