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

// base/consumed
void \@Base::consumed()
{
    if (d_reducedToken != _UNDETERMINED_)
        d_reducedToken = _UNDETERMINED_;
    else
        d_token = _UNDETERMINED_;
}

// base/done
void \@Base::done__()
{
$insert 4 debug "\nstate " << d_state << " with " << symbol__(token__()) << ": normal end\n"
    if (d_nErrors__ == 0)
        ACCEPT();
    else
        ABORT();
}
// base/error
void \@Base::error__()
{
$insert 4 debug "\nERROR with d_recovery " << d_recovery

    if (not d_recovery)
        d_recovery = true;
    else
    {
$insert 8 debug "cannot process " << symbol__(d_token) << ", requesting the next token"
        d_token = _UNDETERMINED_;
    }

    d_reducedToken = _error_;
}
// base/findtoken
SR__ const *\@Base::findToken__() const // find the item defining an 
{                                       // action for token__()
    SR__ const *sr = s_state[d_state];
    SR__ const *last = sr + sr->d_lastIdx;

    for ( ; ++sr != last; )           // visit all but the last SR entries
    {
        if (sr->d_token == token__())
            return sr;
    }

$insert 4 debug "state " << d_state << ": " +
    if (sr->d_action < 0)
    {   // the compound stmnt is here to accomodate an optional debug stmnt
$insert 8 debug "reduce"
    }
    else 
    {
$insert 8 debug "no action for token " << symbol__(token__())
        sr = 0;
    }
       
    return sr;
}
// base/newtoken
void \@Base::newToken__(int lexToken)
{
    if (d_recovery)                     // when recovering fm an error:
        d_recovery = d_token != _EOF_;  // if the current token isn't EOF 
                                        // then there is another token and
                                        // recovery is complete. If _EOF_
                                        // was already encountered then
                                        // there's no new token, so d_recovery
                                        // isn't reset.
    d_token = lexToken;

    if (d_token <= 0)
        d_token = _EOF_;

    ++d_acceptedTokens__;           // accept another token (see
                                    // errorRecovery())
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

    d_state =  top__<0>();
    d_vsp -= count;

$insert 4 debug ", top state now: " << d_state << ", stack size: " << stackSize__()
}
// base/push
void \@Base::push__(size_t state)
{
$insert 4 debug "\nPUSH: " +
    checkStackSize();

    if (++d_stackIdx > 0)
    {
        top__<0>() = top__<0>(1);
        top__<1>() = top__<1>(1);
        top__<2>() = top__<2>(1);
        top__<3>() = STYPE__{};
    }

    top__<0>() = d_state = state;
    d_vsp = &top();
    top__<3>() = std::move(d_val__);
$insert push
    consumed();
}

// base/reduce
void \@Base::reduce__(PI__ const &pi)
{
    d_reducedToken = pi.d_nonTerm;
$insert 4 debug "setting reduced token to " << symbol__(d_reducedToken)
    size_t msgIdx = top__<1>();
    pop__(pi.d_size);
    top__<1>() = msgIdx;
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
    d_reducedToken = _UNDETERMINED_;
    d_recovery = false;

    d_val__ = STYPE__{};

    push__(0);
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

// base/trydefaultreduce
SR__ const *\@Base::tryDefaultReduce__() const
{
    if (token__() != _UNDETERMINED_)        // tokens are waiting
        return 0;

    SR__ const *sr = s_state[d_state];

    if (sr->d_type == DEF_RED)
    {
$insert 8 debug "state " << d_state << ": default reduce"
        return  sr + sr->d_lastIdx;
    }
    return 0;
}
// derived/errorrecovery
void \@::errorRecovery__()
{
$insert 4 debug "\nERROR recovery in state " << state__() << " with token " << symbol__(token__())

    if (d_acceptedTokens__ > d_requiredTokens__)// only generate an error-
    {                                           // message if enough tokens 
        ++d_nErrors__;                          // were accepted. Otherwise
        error();                                // simply skip input
        d_acceptedTokens__ = 0;
    }

                                                // find the topmost ERR_ITEM
    while (not (s_state[top__<0>()]->d_type & ERR_ITEM))
        pop__();

$insert 4 debug "\n    found error state " << state__() << ", providing token _error_"

    top__<1>() = top__<2>();                    // reset orig. error msg. idx

    error__();                                  // continue at _error_
}
// derived/executeaction
void \@::executeAction__(int production)
try
{
$insert 4 debug "\nREDUCE:\n    (actions for rule " << production << stype__(", stack top semantic value: ", top__<3>())
$insert executeactioncases
    switch (production)
    {
$insert 8 actioncases
    }
$insert 4 debug "... completed" << stype__(", returning semantic value ", d_val__) << ')'
}
catch (std::exception const &exc)
{
    exceptionHandler(exc);
}
// derived/gettoken
void \@::getToken__()
{ 
    if (token__() == _UNDETERMINED_)
    {
        newToken__(lex());
$insert print
    }

$insert 4 debug "getToken: token " << symbol__(token__()) << ", text: " << d_scanner.matched()
}
// derived/nextcycle
void \@::nextCycle__()
{
$insert prompt
    SR__ const *sr = tryDefaultReduce__();

    if (sr == 0)
    {
        getToken__();
        sr = findToken__(); 
    }

    if (sr == 0)                // no action: recovery
    {
        errorRecovery__();
        return;
    }

    int action = sr->d_action;

    if (action == 0)            // accepting state
        done__();

    if (action > 0)             // push the next state
        push__(action);
    else
    {
        executeAction__(-action);
        reduce__(s_productionInfo[ -sr->d_action ]);    // or reduce
    }
}
// derived/parse
int \@::parse()
try 
{
$insert 4 debug "parsing starts"
    reset__();                              // clear the tokens.

    while (true)
        nextCycle__();
}
catch (Return__ retValue)
{
$insert 4 debug "parse(): returns " << retValue
    return retValue;
}

$insert namespace-close
// derived/print
void \@::print__() const
{
$insert print    
}
