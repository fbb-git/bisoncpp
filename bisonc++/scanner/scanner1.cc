#include "scanner.ih"

Scanner::Scanner(string const &fname)
:
    d_in(fname.c_str()),
    d_retWS(false),
    d_ungotToken(UNAVAILABLE)
{
    if (!d_in)
        lineMsg() << "Can't read input file `" << fname << "'" <<
                    fatal;

    switch_streams(&d_in, &cerr);
}
