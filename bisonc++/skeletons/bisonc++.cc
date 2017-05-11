// base/comment
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
// Last element:    {set to d_token,    action to perform}
//      }

$insert debugincludes
// base/declarations

namespace // anonymous
{
    char const author[] = "Frank B. Brokken (f.b.brokken@rug.nl)";

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
            int d_type;
            int d_token;
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

// base/base1

// If the parsing function call uses arguments, then provide an overloaded
// function.  The code below doesn't rely on parameters, so no arguments are
// required.  Furthermore, parse uses a function try block to allow us to do
// ACCEPT and ABORT from anywhere, even from within members called by actions,
// simply throwing the appropriate exceptions.

\@Base::\@Base()
:
$insert 4 baseclasscode
}

// base/checkstacksize
void \@Base::checkStackSize()
{
    size_t currentSize = d_stateStack.size();

    if (static_cast<size_t>(stackSize__()) == currentSize)
        d_stateStack.resize(currentSize + STACK_EXPANSION__);
}

// base/done
void \@Base::done__()
{
$insert 4 debug "\nstate " << d_state << " with " << symbol__(token__()) << ": normal end\n"
    if (d_recovery)
        ABORT();
    else
        ACCEPT();
}
// base/error
void \@Base::error__()
{
    int lastToken = d_token;            // give the unexpected token a
                                        // chance to be processed
                                        // again.

    pushToken__(_error_);               // specify _error_ as next token
    push(lookup__());                   // push the error state

    d_token = lastToken;                // reactivate the unexpected
                                        // token (we're now in an
                                        // ERROR state).

    d_recovery = true;

    d_token = lastToken;

    if (d_skipToken)
    {
//$insert 8 debug "cannot process " << symbol__(d_token) << ", requesting the next token"

        d_token = _FORCED_GET_;
    }
    d_skipToken = not d_skipToken;
}



// base/lex
void \@Base::lex__(int token)
{
    d_token = token;
    if (d_token <= 0)
        d_token = _EOF_;

    ++d_acceptedTokens__;
    d_terminalToken = true;
}
    
// base/lookup
int \@Base::lookup__() const    // find the item with an action for d_token
{
    SR__ const *sr = s_state[d_state];
    SR__ const *last = sr + sr->d_lastIdx;

    for ( ; ++sr != last; )           // visit all but the last SR entries
    {
        if (sr->d_token == token__())
            return sr->d_action;
    }

$insert 4 debug "state " << d_state << ": " +
    if (sr->d_action < 0)
    {   // the compound stmnt is here to accomodate an optional debug stmnt
$insert 8 debug "reduce"
        return sr->d_action;
    }

$insert 4 debug "no action for token " << symbol__(token__())
    throw UNEXPECTED_TOKEN__;
}
// base/pop
void \@Base::pop__(size_t count)
{
$insert 4 debug "\n pop " << count << " state(s)" +
    if (d_stackIdx < static_cast<int>(count))
    {
$insert 8 debug ":internal error: stack underflow at token " << symbol__(token__())
        ABORT();
    }

    d_stackIdx -= count;

    d_state =  top().first;
    d_vsp -= count;

$insert 4 debug ", top state now: " << d_state << ", stack size: " << stackSize__()
}
// base/poptoken
void \@Base::popToken__()
{
    d_token = d_next.first;
    d_val__ = std::move(d_next.second);

    d_next.first = _UNDETERMINED_;
}
// base/push
void \@Base::push(size_t state)
{
$insert 4 debug "\nPUSH: " +
    checkStackSize();

    ++d_stackIdx;
    top() = StatePair{ d_state = state, std::move(d_val__) };

    d_vsp = &top();

$insert push
}

// base/pushtoken
void \@Base::pushToken__(int token)
{
    d_next = ValuePair{ d_token, std::move(d_val__) };
    d_token = token;
}
// base/recovering
bool \@Base::recovering__()
{
    if (not d_recovery)
        return false;

    if (d_token != _UNDETERMINED_)
        pushToken__(d_token);

    return true;
}

// base/reduce
void \@Base::reduce__(int rule)
{
    PI__ const &pi = s_productionInfo[rule];

    d_token = pi.d_nonTerm;
    d_terminalToken = false;

$insert 4 debug "setting reduced token to " << symbol__(d_token)
    pop__(pi.d_size);
}
// base/reset
void \@Base::reset__()
{
    d_nErrors__ = 0;

    d_stackIdx = -1;
    d_stateStack.clear();
    d_state = 0;

    d_acceptedTokens__ = d_requiredTokens__;
    d_token = _UNDETERMINED_;
    d_val__ = STYPE__{};

    d_next.first = _UNDETERMINED_;
    d_skipToken = false;
    d_recovery = false;

    push(0);
}
// base/setdebug
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

// base/shift
void \@Base::shift__(int nextState)
{
    push(nextState);
    popToken__();               // token processed

    if (d_recovery and d_terminalToken)
    {
        d_recovery = false;
        d_skipToken = false;
    }
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

$insert 4 debug "\nERROR recovery in state " << state__() << " with token " << symbol__(token__())

                                                // only generate an error-
                                                // message if enough tokens 
                                                // were accepted. Otherwise
                                                // simply skip input
    if (terminalToken__() and d_acceptedTokens__ >= d_requiredTokens__)
    {                                           // message if enough tokens 
        ++d_nErrors__;                          // were accepted. Otherwise
        error();                                // simply skip input
$insert 8 errorverbose
    }

                                                // find the topmost ERR_ITEM
    while (not (s_state[top__().first]->d_type & ERR_ITEM))
        pop__();

$insert 4 debug "\n    found error state " << state__() << ", providing token _error_"

    error__();                                  // continue at _error_

    // In the error state, looking up a token allows the parsing process to 
    // continue. Continuation may be possible following multiple reductions,
    // but eventually a terminal token shift will be used, requiring the 
    // next terminal token. If a retrieved token doesn't match, the error
    // recovery catch ensures that next token is requested in the subsequent
    // nextCycle call.
}


// derived/executeaction
void \@::executeAction__(int production)
try
{
$insert 4 debug "\nREDUCE:\n    (actions for rule " << production << stype__(", stack top semantic value: ", vs__(0))
$insert executeactioncases
    switch (production)
    {
$insert 8 actioncases
    }
$insert 4 debug "... completed" << stype__(", returning semantic value ", vs__(0)) << ')'
}
catch (std::exception const &exc)
{
    exceptionHandler(exc);
}
// derived/gettoken
inline void \@::getToken__()
{ 
    lex__(lex());
$insert 4 debug "\nGETTOKEN returns token " << symbol__(token__())
}
// derived/needtoken
bool \@::needToken__()
{
    if (token__() == _FORCED_GET_)
        return true;

    if (not (s_state[state__()]->d_type & REQ_TOKEN))
        return false;

    if (token__() != _UNDETERMINED_)        // no need for a token: got one
        return false;                       // already

    if (nextToken__() != _UNDETERMINED_)
    {
        popToken__();                       // consume pending token
$insert 8 debug "nextToken(): popped " << symbol__(token__()) << stype__(", semantic = ", d_val__)
        return false;
    }
    return true;
}
// derived/nextcycle
void \@::nextCycle__()
try
{
$insert prompt
    if (needToken__())
        getToken__();

    int action = lookup__();        // may throw to errorRecovery

    if (action == 0)                // parsing ends (accept or abort)
        done__();

    if (action > 0)                 // push the next state
        shift__(action);

    else                            // or reduce
    {
        if (not recovering__())
            executeAction__(-action);

        reduce__(-action);    // or reduce
    }
}
catch (ErrorRecovery__)
{
    errorRecovery__();
}



// derived/parse
int \@::parse()
try 
{ 
    // If the parse function call uses arguments, then provide an overloaded
    // function, calling this one.  This member function uses a function try
    // block so ACCEPT and ABORT calls from anywhere, even from within members
    // called by actions, are caught here.

$insert 4 debug "Parsing starts"
    reset__();                              // clear the tokens.

    while (true)
        nextCycle__();
}
catch (Return__ retValue)
{
$insert 4 debug "parse(): returns " << retValue << " or " << d_nErrors__
    return retValue or d_nErrors__;
}

$insert namespace-close
// derived/print
void \@::print__() const
{
$insert print    
}
