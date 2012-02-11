#include "options.ih"

void Options::setLexFunctionName(string const &name)
{
    if (d_lexFunctionName.size())
        cerr << "%lex-function-name (--lex-function-name) "
                                                    "multiply specified\n";
    else
        d_lexFunctionName = undelimit(name);
}
