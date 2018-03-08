#ifndef _INCLUDED_MYSCANNER_H_
#define _INCLUDED_MYSCANNER_H_

#if ! defined(_SKIP_YYFLEXLEXER_) && ! defined(_SYSINC_FLEXLEXER_H_)
#include <FlexLexer.h>
#define _SYSINC_FLEXLEXER_H_
#endif

class MyScanner: public yyFlexLexer
{
    public:
        int yylex();
};

#endif
