#include "scanner.ih"

void Scanner::checkZeroNumber() 
{
    if (d_number == 0)
        emsg << "Quoted constant " << d_matched << " equals zero" << endl;
}
