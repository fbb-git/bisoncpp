#include "parser.ih"

string Parser::svsElement(int nElements, AtDollar const &atd) const
{
    ostringstream os;
    os << s_semanticValueStack << "[" << 
                                indexToOffset(atd.nr(), nElements) << "]";
    return os.str();
}
