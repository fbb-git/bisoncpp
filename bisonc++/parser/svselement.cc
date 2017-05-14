#include "parser.ih"

    // note: 2nd arg. is the production rule's element NUMBER, not index.
string Parser::svsElement(int nElements, int nr) const
{
    ostringstream os;
    os << s_semanticValueStack << indexToOffset(nr, nElements) << ')';

    return os.str();
}
