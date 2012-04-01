#include "parser.ih"

Parser::PolyType Parser::polyType() const
{
    string const &defaultType = d_rules.sType();    // get the rule's default
                                                    // type

    if (defaultType.empty())        // no default type
    {
        wmsg << d_rules.name() << ": using untyped polymorphic value" <<
                endl;

        return UNTYPED;        
    }

    if (defaultType == "STYPE__")   // default is STYPE__ 
        return STYPED;
                                    // existing polymorphic type
    if (d_polymorphic.find(defaultType) != d_polymorphic.end())
        return TYPED;
                                    // no such polymorphic type
    emsg << "no such semantic type identifier `" << defaultType << '\'' <<
            endl;

    return UNTYPED;
}
