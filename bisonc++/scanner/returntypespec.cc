#include "scanner.ih"

void Scanner::returnTypeSpec()
{
    string trimmed = String::trim(matched());
    
    push(trimmed.back());       // return '%' or ';' for renewed scanning

    trimmed.resize(trimmed.length() - 1);
    
    setMatched(String::trim(trimmed));

    begin(StartCondition__::INITIAL);

    leave(Parser::IDENTIFIER);
}
