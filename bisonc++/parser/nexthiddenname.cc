#include "parser.ih"

string Parser::nextHiddenName() 
{
    s_hiddenName.clear();
    s_hiddenName.str("");
    s_hiddenName << "#" << setfill('0') << setw(4) << ++s_nHidden;

    return s_hiddenName.str();    
}
