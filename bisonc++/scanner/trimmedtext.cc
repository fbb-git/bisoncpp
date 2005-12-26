#include "scanner.ih"

string const &Scanner::trimmedText()
{
    std::string::size_type
        idx = d_text.find_first_not_of(" \t\r"); // find first non-ws

    if (idx == std::string::npos)               // only ws chars ?
        d_text.clear();                         // remove those
    else
        d_text = d_text.substr(idx, 
                               d_text.find_last_not_of(" \t\r\n") - idx + 1);
    return d_text;
}
