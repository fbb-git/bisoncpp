#include "scanner.ih"

void Scanner::unget()
{
    d_ungotText = d_text;
    d_ungotNumber = d_number;
    d_ungotToken = d_token;
}
