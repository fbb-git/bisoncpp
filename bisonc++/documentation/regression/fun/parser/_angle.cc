#include "parser.ih"

double Parser::angle(double radians)    // convert radians to angle type 
{
    return 
        d_angleType == RADIANS  ?   radians                 :
        d_angleType == DEG360   ?   180 / M_PI * radians    :
                                    200 / M_PI * radians;
}
