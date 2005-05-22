#include "scanner.ih"

string const &Scanner::canonicalQuote() 
{
    ostringstream oss;
    oss << "'\\x" << setfill('0') << setw(2) << 
            hex << d_number << "'";
    return d_canonicalQuote = oss.str();
}
