#include "parser.ih"

double Parser::radians(double angle)    // convert angles to radians
{
    return
        d_angleType == RADIANS  ?   angle               :
        d_angleType == DEG360   ?   M_PI / 180 * angle  :
                                    M_PI / 200 * angle;
}
