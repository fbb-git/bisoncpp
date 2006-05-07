#ifndef _SCANNER_H_
#define _SCANNER_H_

#if ! defined(_SKIP_YYFLEXLEXER_) && ! defined(_SYSINC_FLEXLEXER_H_)
#include <FlexLexer.h>
#define _SYSINC_FLEXLEXER_H_
#endif

    
class Scanner: public yyFlexLexer
{
    public:
        int yylex();
};

#endif



