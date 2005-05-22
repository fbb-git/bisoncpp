#include "scanner.ih"

void Scanner::cutColon() 
{
    string::size_type pos = d_text.find_first_of(" \t\n:");

    if (pos != string::npos)
        d_text.resize(pos);
}
