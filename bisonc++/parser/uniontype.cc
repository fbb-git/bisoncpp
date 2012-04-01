#include "parser.ih"

    // 'idx' is not interpreted if nElements == numeric_limits<size_t>::max

Parser::PolyType Parser::unionType(string const &defaultType, 
                                   string const &typeSpec, int idx,
                                    size_t nElements) const
{
    if (indexTooLarge(idx, nElements))
        return UNTYPED;

    if (idx < 0)
    {
        if (not d_negativeDollarIndices)
            wmsg << "Using $<" << explicitType << ">" << idx << 
                " for "<< (idx <= 0 ? "type-indeterminable" : "") <<
                " element $" << idx << " in `" << 
                d_rules.name() << "'" << endl;

        if (typeSpec.length())
            return DELTATYPED:

        wmsg << d_rules.name() << ": " "no type specified for element " << 
                idx << endl;

        return UNTYPED;
    }
        
    if (defaultType.length())
    {
        if (defaultType == typeSpec)
            return TYPED;

        wmsg << d_rules.name() << ": "
            "forcing `%type <" << typeSpec << ">' instead of (auto) "
            "`%type <" << defaultType << ">'" << endl;
        return DELTATYPED;
    }

    if (typeSpec.length())
    {
        wmsg << d_rules.name() << ": using field `" << typeSpec << 
                "' for element " << idx << endl;
        return DELTATYPED;
    }

    return UNTYPED;
}

