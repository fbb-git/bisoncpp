// $insert class.ih
#include "Parser.ih"


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
            int d_negProductionNr;  // if positive, use d_nextState
            unsigned d_nextState;   
                            // negative: negative rule number to reduce to
                            // otherwise: next state
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

    // $insert staticdata
    
// Productions Info Records:
PI s_productionInfo[] = 
{
     {0, 0}, // not used: reduction values are negative
     {262, 0}, //     1: input ->    <empty>
     {262, 2}, //     2: input -> input line
     {263, 1}, //     3: line -> '\n'
     {263, 2}, //     4: line -> exp '\n'
     {263, 2}, //     5: line -> error '\n'
     {264, 1}, //     6: exp -> NUM
     {264, 3}, //     7: exp -> exp '+' exp
     {264, 3}, //     8: exp -> exp '-' exp
     {264, 3}, //     9: exp -> exp '*' exp
     {264, 3}, //     10: exp -> exp '/' exp
     {264, 2}, //     11: exp -> '-' exp
     {264, 3}, //     12: exp -> exp '^' exp
     {264, 3}, //     13: exp -> '(' exp ')'
     {265, 1}, //     14: input_$ -> input
};

// State info and SR transitions for each state.


SR s_0[] =
{
    {NORMAL, -2},
    {262, 1}, // input
    {0, -1} // DEFAULT_REDUCTION
};

SR s_1[] =
{
    {HAS_ERROR_ITEM, 9}, // SHIFTS
    {_error_, 2},
    {_EOF_, PARSE_ACCEPT},
    {ParserBase::NUM, 3},
    {'-', 4},
    {'\n', 6},
    {'(', 8},
    {263, 5}, // line
    {264, 7}, // exp
    {0, 0}
};

SR s_2[] =
{
    {IS_ERROR_STATE, 2}, // SHIFTS
    {'\n', 9},
    {0, 0}
};

SR s_3[] =
{
    {NORMAL, -1},
    {0, -6} // DEFAULT_REDUCTION
};

SR s_4[] =
{
    {NORMAL, 5}, // SHIFTS
    {ParserBase::NUM, 3},
    {'-', 4},
    {'(', 8},
    {264, 10}, // exp
    {0, 0}
};

SR s_5[] =
{
    {NORMAL, -1},
    {0, -2} // DEFAULT_REDUCTION
};

SR s_6[] =
{
    {NORMAL, -1},
    {0, -3} // DEFAULT_REDUCTION
};

SR s_7[] =
{
    {NORMAL, 7}, // SHIFTS
    {'-', 11},
    {'+', 12},
    {'*', 13},
    {'/', 14},
    {'^', 15},
    {'\n', 16},
    {0, 0}
};

SR s_8[] =
{
    {NORMAL, 5}, // SHIFTS
    {ParserBase::NUM, 3},
    {'-', 4},
    {'(', 8},
    {264, 17}, // exp
    {0, 0}
};

SR s_9[] =
{
    {NORMAL, -1},
    {0, -5} // DEFAULT_REDUCTION
};

SR s_10[] =
{
    {NORMAL, 2}, // SHIFTS
    {'^', 15},
    {0, -11} // DEFAULT_REDUCTION
};

SR s_11[] =
{
    {NORMAL, 5}, // SHIFTS
    {ParserBase::NUM, 3},
    {'-', 4},
    {'(', 8},
    {264, 18}, // exp
    {0, 0}
};

SR s_12[] =
{
    {NORMAL, 5}, // SHIFTS
    {ParserBase::NUM, 3},
    {'-', 4},
    {'(', 8},
    {264, 19}, // exp
    {0, 0}
};

SR s_13[] =
{
    {NORMAL, 5}, // SHIFTS
    {ParserBase::NUM, 3},
    {'-', 4},
    {'(', 8},
    {264, 20}, // exp
    {0, 0}
};

SR s_14[] =
{
    {NORMAL, 5}, // SHIFTS
    {ParserBase::NUM, 3},
    {'-', 4},
    {'(', 8},
    {264, 21}, // exp
    {0, 0}
};

SR s_15[] =
{
    {NORMAL, 5}, // SHIFTS
    {ParserBase::NUM, 3},
    {'-', 4},
    {'(', 8},
    {264, 22}, // exp
    {0, 0}
};

SR s_16[] =
{
    {NORMAL, -1},
    {0, -4} // DEFAULT_REDUCTION
};

SR s_17[] =
{
    {NORMAL, 7}, // SHIFTS
    {'-', 11},
    {'+', 12},
    {'*', 13},
    {'/', 14},
    {'^', 15},
    {')', 23},
    {0, 0}
};

SR s_18[] =
{
    {NORMAL, 4}, // SHIFTS
    {'*', 13},
    {'/', 14},
    {'^', 15},
    {0, -8} // DEFAULT_REDUCTION
};

SR s_19[] =
{
    {NORMAL, 4}, // SHIFTS
    {'*', 13},
    {'/', 14},
    {'^', 15},
    {0, -7} // DEFAULT_REDUCTION
};

SR s_20[] =
{
    {NORMAL, 2}, // SHIFTS
    {'^', 15},
    {0, -9} // DEFAULT_REDUCTION
};

SR s_21[] =
{
    {NORMAL, 2}, // SHIFTS
    {'^', 15},
    {0, -10} // DEFAULT_REDUCTION
};

SR s_22[] =
{
    {NORMAL, 2}, // SHIFTS
    {'^', 15},
    {0, -12} // DEFAULT_REDUCTION
};

SR s_23[] =
{
    {NORMAL, -1},
    {0, -13} // DEFAULT_REDUCTION
};


// State array:
SR *s_state[] =
{
  s_0,  s_1,  s_2,  s_3,  s_4,  s_5,  s_6,  s_7,  s_8,  s_9,
  s_10,  s_11,  s_12,  s_13,  s_14,  s_15,  s_16,  s_17,  s_18,  s_19,
  s_20,  s_21,  s_22,  s_23,
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
    d_token(_UNDETERMINED_)
{}

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

void ParserBase::clearin()
{
    d_token = _UNDETERMINED_;
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
#line 21 "grammar"
        { 
                    std::cout << "\t" << d_vsp[-1] << std::endl;
                }
        break;

        case 7:
#line 32 "grammar"
        { 
                    d_val = d_vsp[-2] + d_vsp[0];
                }
        break;

        case 8:
#line 37 "grammar"
        { 
                    d_val = d_vsp[-2] - d_vsp[0];
                }
        break;

        case 9:
#line 42 "grammar"
        { 
                    d_val = d_vsp[-2] * d_vsp[0];
                }
        break;

        case 10:
#line 47 "grammar"
        { 
                    d_val = d_vsp[-2] / d_vsp[0];
                }
        break;

        case 11:
#line 52 "grammar"
        { 
                    d_val = -d_vsp[0];
                }
        break;

        case 12:
#line 58 "grammar"
        { 
                    d_val = pow(d_vsp[-2], d_vsp[0]);
                }
        break;

        case 13:
#line 63 "grammar"
        { 
                    d_val = d_vsp[-1];
                }
        break;

    }
}

int Parser::nextToken()
{
    d_token = lex();
    print();
    if (d_token <= 0)
        d_token = _EOF_;

    return d_token;
}
        
int Parser::lookup(int token)
{
    SR *sr = s_state[d_state];

    int lastIdx = sr->d_lastIdx;

    if (lastIdx < 0)                    // doesn't shift
        lastIdx = -lastIdx;
    else if (token == _UNDETERMINED_)   // shift if token isn't available
        token = nextToken();            // (e.g., following a reduce it *is*
                                        // available)
    SR *last = sr + lastIdx;

    last->d_token = token;              // set search-token
    
    SR *search = sr + 1;
    while (search->d_token != token)
        ++search;

    if (search == last && !last->d_negProductionNr)
    {
        throw UNEXPECTED_TOKEN;
    }

    return search->d_negProductionNr;
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
unsigned Parser::errorRecovery()
try
{
    ++d_nErrors;

    error("Syntax error");

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
            throw DEFAULT_RECOVERY_MODE;
        }
        try
        {
            nextToken();
            lookup(d_token);
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

int Parser::parse()
try 
{
    push(0);                                // initial state

    while (true)
    {
        try
        {
            int action = lookup(d_token);   // d_state, token

            if (action > 0)                 // push a new state
            {
                push(action);
                d_token = _UNDETERMINED_;
            }
            else if (action < 0)
            {
                int saveToken = d_token;
                executeAction(-action);
                push(lookup(reduce(s_productionInfo[-action]))); 
                d_token = saveToken;
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
    return retValue;
}

