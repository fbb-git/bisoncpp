$insert class.ih
$insert debugincludes
#include <unordered_set>

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
    enum StateType      // modify statetype/data.cc when this enum changes
    {
        NORMAL,
        ERR_ITEM,       // from here: StateType values are bit-flags
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
            int d_token;
        };
        union
        {
            int _field_2_;

            int d_lastIdx;          // with s_X[0]: last s_X[] element

            int d_action;           // postive (shift), or 0 (accept)
                                    // s_X[ s_X[ lastIdx ] ].d_action: if 
                                    // negative: rule to reduce to
        };
        size_t d_error = 0;         // Idx in s_errorLA__, used by 
    };                              // error-states

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
    d_acceptedTokens__(d_requiredTokens__),
    d_token__(_UNDETERMINED_),
    d_nextToken__(_UNDETERMINED_)
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

void \@Base::print__()
{
$insert print
}

void \@Base::clearin__()
{
    d_tokenType__ = UNDEFINED__;
    push__(0);
}

void \@Base::checkStackSize()
{
std::cerr << "checkStackSize__()" << '\n';
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

void \@Base::push__(size_t state)
{
std::cerr << "push__()" << '\n';
    checkStackSize();

    size_t previous = 
            d_stackIdx__ == -1 ? 0 : d_stateStack__[d_stackIdx__].second;
    ++d_stackIdx__;
    d_stateStack__[d_stackIdx__] = 
            std::pair<size_t, size_t>{d_state__ = state, previous};

$insert 4 LTYPEpush
$insert 4 debug  "\npush state " << state << stype__(". Semantic TOS value = ", d_val__, ".") << ". Stack size: " << (d_stackIdx__ + 1)

    *(d_vsp__ = &d_valueStack__[d_stackIdx__]) = std::move(d_val__);
}

void \@Base::pop__(size_t count)
{
std::cerr << "pop__()" << '\n';

$insert 4 debug "removing " << count << " elements from the state-stack. New stack size: " << (d_stackIdx__ + 1 - count)
    if (d_stackIdx__ < static_cast<int>(count))
    {
$insert 8 debug "Terminating parse(): stack underflow at token " << symbol__(d_token__) << '\n'
        ABORT();
    }

    d_stackIdx__ -= count;
    d_state__ = d_stateStack__[d_stackIdx__].first;
    d_vsp__ = &d_valueStack__[d_stackIdx__];
$insert 4 LTYPEpop
$insert debug "new state: " << d_state__ << ", with token: " << symbol__(d_token__) << stype__(", semantic: ", *d_vsp__)
}

inline size_t \@Base::top__() const
{
std::cerr << "top__()" << '\n';
    return d_stateStack__[d_stackIdx__].first;
}

void \@::executeAction__(int production)
try
{
std::cerr << "executeAction__()" << '\n';

$insert 4 debug "executing the action block of rule " << production <<  stype__(", top value of the semantic stack: ", *d_vsp__)
$insert executeactioncases
    switch (production)
    {
$insert 8 actioncases
    }

$insert 4 debug "executed the action block of rule " << production <<  stype__(", returning semantic value ", *d_vsp__) << '\n'
}
catch (std::exception const &exc)
{
    exceptionHandler__(exc);             // user code exception handler
}
catch (Return__ ret)
{
    if (ret == PARSE_ERROR__)
        return;
    throw;
}

void \@::getToken__()
{ 
std::cerr << "getToken__()" << '\n';

    if (d_nextToken__ == _UNDETERMINED_)
        d_token__ = lex();
    else
    {
        d_token__ = d_nextToken__;
        d_nextToken__ = _UNDETERMINED_;
    }

    d_tokenType__ = TERMINAL__;
    ++d_acceptedTokens__;               // accept another token (see
                                        // errorRecover())
    if (d_token__ <= 0)
        d_token__ = _EOF_;

    print();
$insert 4 debug "   got " << symbol__(d_token__) << stype__(", semantic = ", d_val__)
}

SR__ const *\@Base::findToken__() const // find the item defining an action for
{                                       // d_token__
std::cerr << "findToken__()" << ", state = " << d_state__ << '\n';

    for (                           // visit all but the last SR entries
        SR__ const *sr = s_state[d_state__], *last = sr + sr->d_lastIdx;
            sr != last;
                ++sr
    )
    {
        if (sr->d_token == d_token__)
            return sr;
    }
    return 0;
}

SR__ const *\@Base::errorItem__()
{
std::cerr << "errorItem__()" << '\n';
    d_token__ = _error_;
    return findToken__();
}

inline void \@Base::reduce__(PI__ const &pi)
{
    d_token__ = pi.d_nonTerm;
    d_tokenType__ = NON_TERMINAL__;
    pop__(pi.d_size);

$insert 4 debug "\nreduce by rule " << (&pi - s_productionInfo) << ". Next token: " << symbol__(d_token__) << stype__(", semantic = ", d_val__)
}

void \@::action__(SR__ const *elementPtr)
{
//    std::cerr << "action__(elementPtr)" << '\n';

    int action = elementPtr->d_action;

    if (action == 0)            // accepting state
    {
        if (d_nErrors__ == 0)
            ACCEPT();
        else
            ABORT();
    }
    
    if (action < 0)             // reduce according to rule -action
    {
        executeAction__(-action);
        reduce__(s_productionInfo[ -action ]);
        return;
    }

    push__(action);

    if (d_tokenType__ == TERMINAL__)        // terminal tokens are consumed.
        d_tokenType__ = UNDEFINED__;
}

void \@::errorRecovery__()
{
    // When an error has occurred, pop elements off the stack until the top
    // state has an error-item. If none is found, the default recovery
    // mode (which is to abort) is activated. 
    //
    // If EOF is encountered without being appropriate for the current state,
    // then the error recovery will fall back to the default recovery mode.
    // (i.e., parsing terminates)

std::cerr << "errorRecovery__()" << '\n';

    if (d_acceptedTokens__ >= d_requiredTokens__)// only generate an error-
    {                                           // message if enough tokens 
        ++d_nErrors__;                          // were accepted. Otherwise
        error();                                // simply skip input
    }

                                                // find the topmost ERR_ITEM
    while (not (s_state[top__()]->d_type & ERR_ITEM))
        pop__();

    SR__ const *elementPtr = errorItem__();

    std::unordered_set<int> &us = s_errorLA[ elementPtr->d_error ];

    do
        getToken__();
    while (us.find(d_token__) == us.end()); // find a continuation
        
    action__(elementPtr);                   // perform the matching action
}

bool \@::defaultReduce__()
{
std::cerr << "defaultReduce__()" << '\n';

    SR__ const *sr = s_state[ d_state__ ];

std::cerr << "In state " << d_state__ << ": type = " << (int)
sr->d_type << ", DEF_RED = " << (int)DEF_RED << '\n';

    if (sr->d_type < DEF_RED)    // no default reduce
        return false;

    int action = -sr[ sr->d_lastIdx ].d_action;

    if (d_tokenType__ == TERMINAL__)    // push-back retrieved token
        d_nextToken__ = d_token__;

    executeAction__(action);
    reduce__(s_productionInfo[ action ]);
    
    return true;
}

void \@::nextCycle__()
{
std::cerr << "nextCycle__()" << '\n';

    if (d_tokenType__ == UNDEFINED__)
        getToken__();

                                        // is there an action for this token?
    if (SR__ const *elementPtr = findToken__())   
        action__(elementPtr);           // yes: perform the action

    else if (not defaultReduce__())     // no default reduction?
    {
                                        // if a token can be requested:
        if (s_state[ d_state__ ]->d_type & REQ_TOKEN)
        {
            getToken__();               // get it.

                                        // find an action for this token    
            if (SR__ const *elementPtr = findToken__())   
            {
                action__(elementPtr);   // found one: perform the action
                return;
            }
        }
        errorRecovery__();              // no default reduction, no token:
                                        // recover from error
    }
}

int \@::parse()
try 
{
std::cerr << "parse()" << '\n';
$insert 4 debug "parse(): Parsing starts"
    clearin__();                            // clear the tokens.

    while (true)
    {
$insert 8 debug ' '
        nextCycle__();
    }
}
catch (Return__ retValue)
{
$insert 4 debug "parse(): returns " << retValue
    return retValue;
}

$insert namespace-close


