#include "parser.ih"

string Parser::dollarTypedDollarUnion(std::string const &unionField) const
{
    string ret;

    switch (semTagDTDU(unionField))
    {
        case UNTYPED:
            noAutoWarning("field");
            ret = "." + unionField;
        break;

        case DELTATYPED:
            autoOverrideWarning("field", unionField);
            ret = "." + unionField;
        break;

        case TYPED:
            ret = "." + d_rules.sType();
        // FALLING THROUGH

        default:
        break;
    }

    return ret;
}
