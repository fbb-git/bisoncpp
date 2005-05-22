#include "scanner.ih"

void Scanner::unexpectedEOF() 
{
    lineMsg() << "Unexpected EOF" << fatal;
}
