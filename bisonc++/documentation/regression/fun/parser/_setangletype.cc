#include "parser.ih"

void Parser::setAngleType()
{
    string type = d_scanner.matched();

    if (type == "rad")
    {
        cout << "Angles in radians\n";        
        d_angleType = RADIANS;
    }
    else if (type == "deg")
    {
        cout << "Angles in 360-degrees circles\n";        
        d_angleType = DEG360;
    }
    else 
    {
        cout << "Angles in 400-degrees circles\n";        
        d_angleType = DEG400;
    }
}
