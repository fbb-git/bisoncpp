#include "parser.hh"

void Parser::ShowVar::operator()(SymbolMap::value_type &v)
{
    cout << v.first << ": " << d_value[v.second] << 
        " (" << d_value[v.second].tagName() << ")" << endl;
}
