#include "parser.ih"

Parser::PolyType Parser::polyType(string const &specifiedType) const
{
    string const &defaultType = d_rules.sType();    // get the rule's default
                                                    // type

    // A specific type was provided (as in $<TYPE>$

    auto iter = d_polymorphic.find(specifiedType);

    if (iter == d_polymorphic.end())        // unknown type was specified
    {
        emsg << "no such semantic type identifier `" << specifiedType << 
                '\'' << endl;
        return UNTYPED;
    }

    if (defaultType.empty())                // no default type association
    {                                       // warn, but use <specificType>
        noDefaultTypeWarning();
        return DELTATYPED;
    }

    if 
    (
        defaultType == "STYPE__"            // auto is generic (STYPE__),
        ||
        defaultType == specifiedType        // or specified the auto type
    )
        return DELTATYPED;                  // use the specifiedType


    wmsg << "production rule \n"<< 
            "\t`" << &d_rules.lastProduction() << " ':\n"
            "\tforcing `%type <" << specifiedType << ">' instead of (auto) "
            "`%type <" << defaultType << ">'" << endl;

    return DELTATYPED;
}
