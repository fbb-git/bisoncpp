#include "scanner.ih"

namespace {
    char const *nameOf[] = 
    {
        "UNAVAILABLE",
        "BASECLASS_HEADER",
        "BASECLASS_PREINCLUDE",
        "CLASS_HEADER",
        "DEBUGFLAG",
        "ENDFILE",
        "ERROR_VERBOSE",
        "EXPECT",
        "FILENAMES",
        "IDENTIFIER",
        "ILLEGAL",
        "IMPLEMENTATION_HEADER",
        "LEFT",
        "LOCATIONSTRUCT",
        "LSP_NEEDED",
        "LTYPE",
        "NAMESPACE",
        "NEG_DOLLAR",
        "NONASSOC",
        "NUMBER",
        "PARSEFUN_SOURCE",
        "CLASS_NAME",
        "PREC",
        "QUOTE",
        "RIGHT",
        "START",
        "STYPE",
        "TOKEN",
        "TWO_PERCENTS",
        "TYPE",
        "TYPENAME",
        "UNION",
        "STRING",
        "WS",
        "RULE",
    };

//    void showToken(size_t/*unsigned*/ token)
//    {
//
//        cout << "lex() returns ";
//        if (isprint(token))
//            cout << "char: `" << static_cast<char>(token) << "'";
//        else if (token < 256)
//            cout << "ascii " << token;
//        else
//            cout << "token " << nameOf[token - 256];
//        cout << endl;
//    }

}

int Scanner::lex() 
{
    if (d_ungotToken != UNAVAILABLE)    // return any ungot tokens we may
    {                                   // have
        d_text = d_ungotText;
        d_number = d_ungotNumber;

        d_token = d_ungotToken;
        d_ungotToken = UNAVAILABLE;
        return d_token;
    }

    d_token = yylex();
    Msg::setLine(yylineno);
    d_text = yytext;

    switch (d_token)
    {
        case 0:
        return ENDFILE;

        default:
//            showToken(d_token);
        return d_token;
    }
}
