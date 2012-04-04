#include "parser.ih"

string Parser::returnPolymorphic(Block const &block, 
                                 AtDollar const &atd) const
{
    string ret;

    if (callsMember("type", atd))
        return ret;

    switch (semTagPolymorphic(atd))
    {
        case AUTO:          // use the %type specified semantic value
            ret = ".get<" + d_rules.sType() + ">()";
        break;

        case INVALID_AUTO:
            errInvalidAuto(atd);
        break;

        case INVALID_EXPLICIT:  // invalid explicit semval requested: error
            errInvalidExplicit(atd);
        break;

        case EXPLICIT_OVERRIDE: // override %type, warn
            warnExplicitOverride("tag", atd);
            ret = ".get<" + atd.id() + ">()"
        break;

        case RAW_NOAUTO:    // raw sem. value, no %type spec. warning
            warnNoTypeSpec("tag", atd);
        break;
        
        case RAW_OVERRIDE:  // raw semantic value requested: warn
            warnRawOverride("tag", atd);
        break;

        case EXPLICIT_NOAUTO:    // explicit requested, warn no %type spec.
            warnExplicitNoAuto("tag", atd);
            ret = ".get<" + atd.id() + ">()"
        break;

        case RAW:           // use the raw semantic value
        break;
    };

    return ret;
}

