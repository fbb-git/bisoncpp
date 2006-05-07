// $insert class.ih
#include "parser.ih"


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

    // $insert staticdata
    
// Productions Info Records:
PI s_productionInfo[] = 
{
     {0, 0}, // not used: reduction values are negative
     {260, 2}, // 1: expressions -> expressions evaluate
     {260, 1}, // 2: expressions -> prompt
     {261, 2}, // 3: evaluate -> alternative prompt
     {262, 0}, // 4: prompt -> <empty>
     {263, 2}, // 5: alternative -> expression EOLN
     {263, 2}, // 6: alternative -> 'q' done
     {263, 1}, // 7: alternative -> EOLN
     {263, 2}, // 8: alternative -> error EOLN
     {265, 0}, // 9: done -> <empty>
     {264, 3}, // 10: expression -> expression '+' expression
     {264, 3}, // 11: expression -> expression '-' expression
     {264, 3}, // 12: expression -> expression '*' expression
     {264, 3}, // 13: expression -> expression '/' expression
     {264, 2}, // 14: expression -> '-' expression
     {264, 2}, // 15: expression -> '+' expression
     {264, 3}, // 16: expression -> '(' expression ')'
     {264, 1}, // 17: expression -> NUMBER
     {266, 1}, // 18: expressions_$ -> expressions
};

// State info and SR transitions for each state.


SR s_0[] =
{
    {{NORMAL}, {-3}}, // REDUCES
    {{260}, {1}}, // expressions
    {{262}, {2}}, // prompt
    {{0}, {-4}} // DEFAULT_REDUCTION
};

SR s_1[] =
{
    {{HAS_ERROR_ITEM}, {12}}, // ACCEPTS
    {{_error_}, {3}},
    {{ParserBase::EOLN}, {4}},
    {{ParserBase::NUMBER}, {5}},
    {{'+'}, {6}},
    {{'-'}, {7}},
    {{261}, {8}}, // evaluate
    {{263}, {9}}, // alternative
    {{264}, {10}}, // expression
    {{'q'}, {11}},
    {{'('}, {12}},
    {{_EOF_}, { PARSE_ACCEPT }},
    {{0}, {0}}
};

SR s_2[] =
{
    {{NORMAL}, {-1}}, // REDUCES
    {{0}, {-2}} // DEFAULT_REDUCTION
};

SR s_3[] =
{
    {{IS_ERROR_STATE}, {2}}, // SHIFTS
    {{ParserBase::EOLN}, {13}},
    {{0}, {0}}
};

SR s_4[] =
{
    {{NORMAL}, {-1}}, // REDUCES
    {{0}, {-7}} // DEFAULT_REDUCTION
};

SR s_5[] =
{
    {{NORMAL}, {-1}}, // REDUCES
    {{0}, {-17}} // DEFAULT_REDUCTION
};

SR s_6[] =
{
    {{NORMAL}, {6}}, // SHIFTS
    {{ParserBase::NUMBER}, {5}},
    {{'+'}, {6}},
    {{'-'}, {7}},
    {{264}, {14}}, // expression
    {{'('}, {12}},
    {{0}, {0}}
};

SR s_7[] =
{
    {{NORMAL}, {6}}, // SHIFTS
    {{ParserBase::NUMBER}, {5}},
    {{'+'}, {6}},
    {{'-'}, {7}},
    {{264}, {15}}, // expression
    {{'('}, {12}},
    {{0}, {0}}
};

SR s_8[] =
{
    {{NORMAL}, {-1}}, // REDUCES
    {{0}, {-1}} // DEFAULT_REDUCTION
};

SR s_9[] =
{
    {{NORMAL}, {-2}}, // REDUCES
    {{262}, {26}}, // prompt
    {{0}, {-4}} // DEFAULT_REDUCTION
};

SR s_10[] =
{
    {{NORMAL}, {6}}, // SHIFTS
    {{ParserBase::EOLN}, {27}},
    {{'+'}, {16}},
    {{'-'}, {17}},
    {{'*'}, {18}},
    {{'/'}, {19}},
    {{0}, {0}}
};

SR s_11[] =
{
    {{NORMAL}, {-2}}, // REDUCES
    {{265}, {28}}, // done
    {{0}, {-9}} // DEFAULT_REDUCTION
};

SR s_12[] =
{
    {{NORMAL}, {6}}, // SHIFTS
    {{ParserBase::NUMBER}, {5}},
    {{'+'}, {6}},
    {{'-'}, {7}},
    {{264}, {24}}, // expression
    {{'('}, {12}},
    {{0}, {0}}
};

SR s_13[] =
{
    {{NORMAL}, {-1}}, // REDUCES
    {{0}, {-8}} // DEFAULT_REDUCTION
};

SR s_14[] =
{
    {{NORMAL}, {-1}}, // REDUCES
    {{0}, {-15}} // DEFAULT_REDUCTION
};

SR s_15[] =
{
    {{NORMAL}, {-1}}, // REDUCES
    {{0}, {-14}} // DEFAULT_REDUCTION
};

SR s_16[] =
{
    {{NORMAL}, {6}}, // SHIFTS
    {{ParserBase::NUMBER}, {5}},
    {{'+'}, {6}},
    {{'-'}, {7}},
    {{264}, {20}}, // expression
    {{'('}, {12}},
    {{0}, {0}}
};

SR s_17[] =
{
    {{NORMAL}, {6}}, // SHIFTS
    {{ParserBase::NUMBER}, {5}},
    {{'+'}, {6}},
    {{'-'}, {7}},
    {{264}, {21}}, // expression
    {{'('}, {12}},
    {{0}, {0}}
};

SR s_18[] =
{
    {{NORMAL}, {6}}, // SHIFTS
    {{ParserBase::NUMBER}, {5}},
    {{'+'}, {6}},
    {{'-'}, {7}},
    {{264}, {22}}, // expression
    {{'('}, {12}},
    {{0}, {0}}
};

SR s_19[] =
{
    {{NORMAL}, {6}}, // SHIFTS
    {{ParserBase::NUMBER}, {5}},
    {{'+'}, {6}},
    {{'-'}, {7}},
    {{264}, {23}}, // expression
    {{'('}, {12}},
    {{0}, {0}}
};

SR s_20[] =
{
    {{NORMAL}, {5}}, // SHIFTS
    {{'+'}, {16}},
    {{'-'}, {17}},
    {{'*'}, {18}},
    {{'/'}, {19}},
    {{0}, {-10}} // DEFAULT_REDUCTION
};

SR s_21[] =
{
    {{NORMAL}, {5}}, // SHIFTS
    {{'+'}, {16}},
    {{'-'}, {17}},
    {{'*'}, {18}},
    {{'/'}, {19}},
    {{0}, {-11}} // DEFAULT_REDUCTION
};

SR s_22[] =
{
    {{NORMAL}, {5}}, // SHIFTS
    {{'+'}, {16}},
    {{'-'}, {17}},
    {{'*'}, {18}},
    {{'/'}, {19}},
    {{0}, {-12}} // DEFAULT_REDUCTION
};

SR s_23[] =
{
    {{NORMAL}, {5}}, // SHIFTS
    {{'+'}, {16}},
    {{'-'}, {17}},
    {{'*'}, {18}},
    {{'/'}, {19}},
    {{0}, {-13}} // DEFAULT_REDUCTION
};

SR s_24[] =
{
    {{NORMAL}, {6}}, // SHIFTS
    {{'+'}, {16}},
    {{'-'}, {17}},
    {{'*'}, {18}},
    {{'/'}, {19}},
    {{')'}, {25}},
    {{0}, {0}}
};

SR s_25[] =
{
    {{NORMAL}, {-1}}, // REDUCES
    {{0}, {-16}} // DEFAULT_REDUCTION
};

SR s_26[] =
{
    {{NORMAL}, {-1}}, // REDUCES
    {{0}, {-3}} // DEFAULT_REDUCTION
};

SR s_27[] =
{
    {{NORMAL}, {-1}}, // REDUCES
    {{0}, {-5}} // DEFAULT_REDUCTION
};

SR s_28[] =
{
    {{NORMAL}, {-1}}, // REDUCES
    {{0}, {-6}} // DEFAULT_REDUCTION
};


// State array:
SR *s_state[] =
{
  s_0,  s_1,  s_2,  s_3,  s_4,  s_5,  s_6,  s_7,  s_8,  s_9,
  s_10,  s_11,  s_12,  s_13,  s_14,  s_15,  s_16,  s_17,  s_18,  s_19,
  s_20,  s_21,  s_22,  s_23,  s_24,  s_25,  s_26,  s_27,  s_28,
};


} // anonymous namespace ends


// If the parser call uses arguments, then provide an overloaded function.
// The code below doesn't rely on parameters, so no arguments are required.
// Furthermore, parse uses a function try block to allow us to do
// ACCEPT and ABORT from anywhere, even from within members called
// by actions, simply throwing the appropriate exceptions.

ParserBase::ParserBase()
:
    d_stackIdx(-1),
    // $insert debuginit
    d_debug(false),
    d_nErrors(0),
    d_token(_UNDETERMINED_),
    d_nextToken(_UNDETERMINED_)
{}

void ParserBase::clearin()
{
    d_token = d_nextToken = _UNDETERMINED_;
}

void ParserBase::ABORT() const throw(Return) 
{
    throw PARSE_ABORT;
}

void ParserBase::ACCEPT() const throw(Return)
{
    throw PARSE_ACCEPT;
}

void ParserBase::ERROR() const throw(ErrorRecovery)
{
    throw UNEXPECTED_TOKEN;
}


void ParserBase::push(unsigned state)
{
    if (static_cast<unsigned>(d_stackIdx + 1) == d_stateStack.size())
    {
        unsigned newSize = d_stackIdx + 5;
        d_stateStack.resize(newSize);
        d_valueStack.resize(newSize);
    }
    ++d_stackIdx;
    d_stateStack[d_stackIdx] = d_state = state;
    *(d_vsp = &d_valueStack[d_stackIdx]) = d_val;
}

void ParserBase::pop(unsigned count)
{
    if (d_stackIdx < static_cast<int>(count))
    {
        ABORT();
    }

    d_stackIdx -= count;
    d_state = d_stateStack[d_stackIdx];
    d_vsp = &d_valueStack[d_stackIdx];
}

unsigned ParserBase::top() const
{
    if (d_stackIdx < 0)
    {
        throw DEFAULT_RECOVERY_MODE;
    }

    return d_stateStack[d_stackIdx];
}

unsigned ParserBase::reduce(PI const &pi)
{

    pop(pi.d_size);


    return pi.d_nonTerm;
}

void Parser::executeAction(int production)
{
    switch (production)
    {
        // $insert actioncases
        
        case 4:
        {
                prompt();
            }
        break;

        case 5:
        {
                cout << d_vsp[-1] << endl;
            }
        break;

        case 9:
        {
                cout << "Done.\n";
                ACCEPT();
            }
        break;

        case 10:
        {
                d_val = d_vsp[-2] + d_vsp[0];
            }
        break;

        case 11:
        {
                d_val = d_vsp[-2] - d_vsp[0];
            }
        break;

        case 12:
        {
                d_val = d_vsp[-2] * d_vsp[0];
            }
        break;

        case 13:
        {
                d_val = d_vsp[-2] / d_vsp[0];
            }
        break;

        case 14:
        {
                d_val = -d_vsp[0];
            }
        break;

        case 15:
        {
                d_val = d_vsp[0];
            }
        break;

        case 16:
        {
                d_val = d_vsp[-1];
            }
        break;

        case 17:
        {
                d_val = atoi(d_scanner.YYText());
            }
        break;

    }
}

void Parser::nextToken()
{
    if (d_nextToken == _UNDETERMINED_)
    {
        d_nextToken = lex();
    }
    print();
    if (d_nextToken <= 0)
        d_nextToken = _EOF_;
    d_token = d_nextToken;
}

// if the final transition is negative, then we should reduce by the rule
// given by its positive value
int Parser::lookup()
{
    SR *sr = s_state[d_state];

    int lastIdx = sr->d_lastIdx;        // sentinel-index in the SR_ array

    if (lastIdx < 0)                    // only (maybe) obtain next token
        lastIdx = -lastIdx;             // if the state uses a terminal-token
    else if (d_token == _UNDETERMINED_) // shift and no token is available
        nextToken();

    SR *lastElementPtr = sr + lastIdx;


    lastElementPtr->d_token = d_token;  // set search-token
    
    SR *elementPtr = sr + 1;
    while (elementPtr->d_token != d_token)
        ++elementPtr;

    if (elementPtr == lastElementPtr)   // reached the last element
    {
        if (elementPtr->d_action < 0)   // default reduction
        {
            return elementPtr->d_action;                
        }
        // No default reduction, so token not found, so error.
        throw UNEXPECTED_TOKEN;
    }

    // not at the last element, if non-negative and if 
    // d_token == d_nextToken token has been processed, and nextToken()
    // can be called. 

    if (elementPtr->d_action <= 0)       // a reduction or ACCEPT is found
    {
        return elementPtr->d_action;
    }

    if (d_token == d_nextToken)         // token was processed
    {
        d_nextToken = _UNDETERMINED_;
    }
    d_token = d_nextToken;
    return elementPtr->d_action;
}

    // When an error has occurred, pop elements off the stack until the top
    // state has an error-item. If none is found, the default recovery
    // mode (which is to abort) is activated. 
    //
    // If EOF is encountered without being appropriate for the current state,
    // then the error recovery will fall back to the default recovery mode.
    // (i.e., parsing terminates)
void Parser::errorRecovery()
try
{
    ++d_nErrors;

    error("Syntax error");

    while (s_state[top()][0].d_type != HAS_ERROR_ITEM)
    {
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
            throw DEFAULT_RECOVERY_MODE;
        }
        try
        {
            clearin();
            int action = lookup();

            if (action > 0)                 // push a new state
            {
                push(action);
            }
            else if (action < 0)
            {
                executeAction(-action);     // the error's action

                                            // next token is the rule's LHS
                d_token = reduce(s_productionInfo[-action]); 
            }
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
int Parser::parse()
try 
{
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
            }
            else if (action < 0)
            {
                executeAction(-action);
                                            // next token is the rule's LHS
                d_token = reduce(s_productionInfo[-action]); 
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
    return retValue;
}

