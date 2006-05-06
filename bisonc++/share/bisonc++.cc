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
        // type, and `d_lastIdx' containing the last element's index. If
        // d_lastIdx is negative then the state needs a token: if in this
        // state d_token is _UNDETERMINED_, nextToken() will be called 
    
        // The LAST element of SR arrays uses `d_token' containing the last
        // retrieved token (or _UNDETERMINED_ immediately following a SHIFT)
        // to speed up the (linear) seach. 
        // Except for the first element of SR arrays, the field `d_action' is
        // used to determine what to do next. If positive, it represents the
        // next state (used with SHIFT); if zero, it indicates `ACCEPT', if
        // negative, -d_action represents the number of the rule to reduce to.
        //
        // `lookup()' tries to find d_token in the current SR array. If it
        // fails, and there is no default reduction UNEXPECTED_TOKEN is
        // thrown, which is then caught by the error-recovery function. 
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
    d_token(_UNDETERMINED_),
    d_nextToken(_UNDETERMINED_)
{}

void @Base::clearin()
{
    d_token = d_nextToken = _UNDETERMINED_;
}

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
$insert 4 debug "Pop " << count << " elements from stack containing " +
$insert 4 debug (d_stackIdx + 1)
    if (d_stackIdx < static_cast<int>(count))
    {
$insert 8 debug "Stack underflow, aborting"
        ABORT();
    }

    d_stackIdx -= count;
    d_state = d_stateStack[d_stackIdx];
    d_vsp = &d_valueStack[d_stackIdx];
$insert 4 LTYPEpop
$insert 4 debug  "Popped " << count << " elements off the state stack."
$insert 4 debug  "Next state: " << d_state
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
    if (d_nextToken == _UNDETERMINED_)
    {
        d_nextToken = lex();
$insert 8 debug "Retrieved next token " << symbol(d_nextToken)
    }
    print();
    if (d_nextToken <= 0)
        d_nextToken = _EOF_;
    d_token = d_nextToken;
$insert 4 debug "Using next token: " << symbol(d_token)
}

// if the final transition is negative, then we should reduce by the rule
// given by its positive value
int @::lookup()
{
    SR *sr = s_state[d_state];

    int lastIdx = sr->d_lastIdx;        // sentinel-index in the SR_ array

    if (lastIdx < 0)                    // only (maybe) obtain next token
        lastIdx = -lastIdx;             // if the state uses a terminal-token
    else if (d_token == _UNDETERMINED_) // shift and no token is available
        nextToken();

    SR *lastElementPtr = sr + lastIdx;

$insert 4 debug "State " << d_state << " lookup token " << symbol(d_token)

    lastElementPtr->d_token = d_token;  // set search-token
    
    SR *elementPtr = sr + 1;
    while (elementPtr->d_token != d_token)
        ++elementPtr;

    if (elementPtr == lastElementPtr)   // reached the last element
    {
        if (elementPtr->d_action < 0)   // default reduction
        {
$insert 8 debug "Default reduction to rule " << -elementPtr->d_action
            return elementPtr->d_action;                
        }
$insert 8 debug "No action for " << symbol(d_token) << ", error recovery."
        // No default reduction, so token not found, so error.
        throw UNEXPECTED_TOKEN;
    }

    // not at the last element, if non-negative and if 
    // d_token == d_nextToken token has been processed, and nextToken()
    // can be called. 

    if (elementPtr->d_action <= 0)       // a reduction or ACCEPT is found
    {
$insert 8 debug "Reduction to rule " << -elementPtr->d_action
        return elementPtr->d_action;
    }

    if (d_token == d_nextToken)         // token was processed
    {
$insert 8 debug "Processed " << symbol(d_token)
        d_nextToken = _UNDETERMINED_;
    }
    d_token = d_nextToken;
$insert 4 debug "Next state " << elementPtr->d_action << ", token " +
$insert 4 debug symbol(d_token)
    return elementPtr->d_action;
}

    // When an error has occurred, pop elements off the stack until the top
    // state has an error-item. If none is found, the default recovery
    // mode (which is to abort) is activated. 
    //
    // If EOF is encountered without being appropriate for the current state,
    // then the error recovery will fall back to the default recovery mode.
    // (i.e., parsing terminates)
void @::errorRecovery()
try
{
    ++d_nErrors;

    error("Syntax error");
$insert 4 debug d_nErrors << " error(s) so far. State = " << top()

    while (s_state[top()][0].d_type != HAS_ERROR_ITEM)
    {
$insert 8 debug "pop state " << top()
        pop();
    }

    d_token = _error_;                      // specify _error_ as next token
    push(lookup());                         // push the error state

    // In the error state, lookup a token with which we can proceed.
    // It may be a reduce, but normally a shift is indicated
    // If a token is seen which doesn't fit, the catch below will catch the
    // execption thrown by lookup()

    while (true)
    {
            // if on entry here token is already EOF then we've probably been 
            // here before: _error_ accepts EOF, but the state using
            // error nevertheless doesn't. In that case parsing terminates 
        if (d_token == _EOF_)
        {
$insert 12 debug "End of input unexpectedly reached"
            throw DEFAULT_RECOVERY_MODE;
        }
        try
        {
            clearin();
            int action = lookup();

            if (action > 0)                 // push a new state
            {
$insert 16 debug "Recovery: push state " << action << ", token cleared "
                push(action);
            }
            else if (action < 0)
            {
                executeAction(-action);     // the error's action

                                            // next token is the rule's LHS
                d_token = reduce(s_productionInfo[-action]); 
$insert 16 debug "Recovery: reduce by rule " << -action << ", token = " +
$insert 16 debug symbol(d_token)
            }
$insert 12 debug "Error recovery successful"
            return;
        }
        catch (...)
        {
        }
    }
}
catch (ErrorRecovery)       // This means: DEFAULT_RECOVERY_MODE
{
    ABORT();
}

    // The parsing algorithm:
    // Initially, state 0 is pushed on the stack, and d_token is initialized 
    // the first token on the input.
    // The stack's top element is always used to access the current state's
    // SR_ array. 
    // Then, in an eternal loop:
    //  1.  d_token is stored in the final element's d_token
    //      field of the state's SR_ array.
    //  2.  The current token is looked up in the state's SR_ array
    //  3. If the token is found at the last element (so, the token wasn't
    //     really found since we've put it there intially) and the last
    //     element's action field is negative, a default reduce is
    //     performed, and the returned action is the rule to reduce to. This
    //     results in d_token receiving the token value of the rule's LHS
    //     token.
    //  4. If the token is found at an earlier element, the result may also be
    //     a reduce, which is handled as described in 3.
    //  5. If the action is 0, the input is accepted, and parsing stops.
    //  6. If the action is positive, a SHIFT is required. However, d_token
    //     must be reassigned first. If the d_token is equal to d_nextToken,
    //     d_nextToken has been processed, and another token can be
    //     retrieved. Otherwise, d_nextToken is reassigned to d_token.
    //  7. An error occurs if d_token is not found, and the state has no
    //     default reduction
int @::parse()
try 
{
$insert 4 debug "Parsing starts"
    push(0);                                // initial state
    d_nextToken = _UNDETERMINED_;           // First token may not yet be 
                                            // required
    while (true)
    {
        try
        {
            int action = lookup();          // lookup d_token in d_state

            if (action > 0)                 // push a new state
            {
                push(action);
                d_token = _UNDETERMINED_;   // try to process the next token
$insert 16 debug "push state " << action << ", token now " << symbol(d_token)
            }
            else if (action < 0)
            {
                executeAction(-action);
                                            // next token is the rule's LHS
                d_token = reduce(s_productionInfo[-action]); 
$insert 16 debug "reduce by rule " << -action << ", token = " +
$insert 16 debug symbol(d_token)
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
$insert 4 debug "parse() returns " << retValue
    return retValue;
}

$insert namespace-close
