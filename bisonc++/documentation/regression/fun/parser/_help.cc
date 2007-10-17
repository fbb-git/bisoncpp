#include "parser.ih"

void Parser::help()
{
    cout << 
        "Operators:\n"
        "   = += -= *= /= %= &= ^= |= <<= >>=\n"
        "   |\n"
        "   ^\n"
        "   &\n"
        "   << >>\n"
        "   + -\n"
        "   * / %\n"
        "   (typecast)  - (unary)\n"
        "Angle specification selectors: deg (= 360), grad (=400), rad\n"
        "Unary functions: abs, sqrt, exp, log, ln, log10,\n"
        "                 sin, cos, tan asin, acos, atan\n"
        "Binary function: pow\n"
        "Data types: char, int, double\n"
        "Variables are automatically defined when used, initialized to 0\n"
        "General usage: exit, quit, help, ?, list\n";
}





