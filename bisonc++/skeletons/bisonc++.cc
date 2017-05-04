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

// If the parsing function call uses arguments, then provide an overloaded
// function.  The code below doesn't rely on parameters, so no arguments are
// required.  Furthermore, parse uses a function try block to allow us to do
// ACCEPT and ABORT from anywhere, even from within members called by actions,
// simply throwing the appropriate exceptions.

\@Base::\@Base()
:
$insert 4 requiredtokens
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

void \@::print__()
{
$insert print
}

void \@Base::push__(size_t state)
{
    checkStackSize();

    if (++d_stackIdx__ > 0)
        top() = d_stateStack__[d_stackIdx__ - 1];

    top__<0>() = d_state__ = state;

$insert 4 debug "\nin state " << top__<0>(1) << "with token: " << symbol__(d_token__) +
$insert 4 debug ": push state " << state << "; stack size = " << (d_stackIdx__ + 1) << stype__(". Semantic TOS value = ", d_val__) << "\n   (consumed token " << symbol__(d_token__) << ')'

    *(d_vsp__ = &d_valueStack__[d_stackIdx__]) = std::move(d_val__);
}

void \@Base::pop__(size_t count)
{
$insert 4 debug "\n pop " << count << " state(s)" +
    if (d_stackIdx__ < static_cast<int>(count))
    {
$insert 8 debug ":internal error: stack underflow at token " << symbol__(d_token__)
        ABORT();
    }

    d_stackIdx__ -= count;
    d_state__ = top__<0>();
    d_vsp__ = &d_valueStack__[d_stackIdx__];
$insert 4 LTYPEpop
$insert 4 debug ", top state now: " << d_state__ << ", stack size: " << (d_stackIdx__ + 1) 
}

void \@Base::reset__()
{
//FBB: define a function to call this, and make it an empty function unless
//      pollymorphic
//    d_s_nErrors__ = Meta__::s_nErrors__;          // save current ptr
//    Meta__::s_nErrors__ = &d_nErrors__;           // set it to d_nErrors__

    d_acceptedTokens__ = d_requiredTokens__;
    d_nErrors__ = 0;

    d_stackIdx__ = -1;
    d_stateStack__.clear();
    d_valueStack__.clear();
    d_tokenStack__ = std::stack<int>{};
    d_state__ = 0;
    d_token__ = _UNDETERMINED_;

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

void \@Base::pushToken__(int token)
{
    d_tokenStack__.push(token);
$insert 4 debug "saved token " << symbol__(token) << ", token stack size: " << d_tokenStack__.size()
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
    exceptionHandler(exc);
}

void \@Base::reduce__(PI__ const &pi)
{
    pushToken__(d_token__);
    pushToken__(pi.d_nonTerm);
    size_t msgIdx = top__<1>();
    pop__(pi.d_size);
    top__<1>() = msgIdx;
}

void \@::getToken__()
{ 
    if (d_tokenStack__.empty())
    {
        d_token__ = lex();
        if (d_token__ <= 0)
            d_token__ = _EOF_;
$insert 8 debug "LEX" +
    }
    else
    {
        d_token__ = d_tokenStack__.top();
        d_tokenStack__.pop();

$insert 8 debug "STACKED" +
    }
$insert 4 debug " token " << symbol__(d_token__) << stype__(", semantic = ", d_val__)

    ++d_acceptedTokens__;               // accept another token (see
                                        // errorRecover())
    print();
}

SR__ const *\@Base::findToken__() const // find the item defining an 
{                                       // action for d_token__
    SR__ const *sr = s_state[d_state__];
    SR__ const *last = sr + sr->d_lastIdx;

    for ( ; sr != last; ++sr)         // visit all but the last SR entries
    {
        if (sr->d_token == d_token__)
            return sr;
    }

$insert 4 debug "state " << d_state__ << ": " +
    if (sr->d_action < 0)
    {
$insert 8 debug "default reduce"
    }
    else 
    {
$insert 8 debug "no action for token " << symbol__(d_token__)
        sr = 0;
    }
       
    return sr;
}

void \@::errorRecovery__()
{
$insert 4 debug "\nStarting error recovery in state " << d_state__ << " with token " << symbol__(d_token__)
    if (d_acceptedTokens__ >= d_requiredTokens__)// only generate an error-
    {                                           // message if enough tokens 
        ++d_nErrors__;                          // were accepted. Otherwise
        error();                                // simply skip input
    }
                                                // find the topmost ERR_ITEM
    while (not (s_state[top__<0>()]->d_type & ERR_ITEM))
        pop__();

    top__<1>() = top__<2>();

    pushToken__(d_token__);
    pushToken__(_error_);

$insert 4 debug "Error recovery: pop to error state: " << d_state__
}

void \@Base::done__()
{
$insert 4 debug "\nstate " << d_state__ << " with " <<  symbol__(d_token__) << ": normal end\n"
    if (d_nErrors__ == 0)
        ACCEPT();
    else
        ABORT();
}

void \@::nextCycle__()
{
//FBB
//    if (d_debug__)
//    {
//        std::string s;
//        std::cout << "? ";
//        getline(std::cin, s);
//    }

$insert 4 debug ' '

    getToken__();

    SR__ const *sr = findToken__(); 

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
//FBB: use a function, see before
//    Meta__::s_nErrors__ = d_s_nErrors__;

$insert 4 debug "parse(): returns " << retValue
    return retValue;
}

$insert namespace-close
