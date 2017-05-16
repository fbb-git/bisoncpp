#include "parser.ih"

int Parser::lex()
{
    std::string word;

    std::cin >> word;
    if (std::cin.eof())
        return 0;
    if (isdigit(word[0]))
        return NR;
    
    return word[0];
}
