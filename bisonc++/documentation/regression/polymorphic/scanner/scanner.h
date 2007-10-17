#ifndef _SCANNER_H_
#define _SCANNER_H_

#include "../semval/semval.h"

#if ! defined(_SKIP_YYFLEXLEXER_) && ! defined(_SYSINC_FLEXLEXER_H_)
#include <FlexLexer.h>
#define _SYSINC_FLEXLEXER_H_
#endif
    
class Scanner: public yyFlexLexer
{
    SemVal *d_semval;

    public:
        Scanner(SemVal *semval);
        int yylex();
};

inline Scanner::Scanner(SemVal *semval)
:
    d_semval(semval)
{}

#endif



