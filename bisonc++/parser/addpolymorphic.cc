#include "parser.ih"

void Parser::addPolymorphic(string const &tag, string const &typeSpec) 
{
    if (d_semType != POLYMORPHIC)
        return;

    if (typeSpec == "STYPE__")
        emsg << "Polymorphic type cannot be STYPE__" << endl;
    else if (d_polymorphic.find(tag) != d_polymorphic.end())
        emsg << "Polymorphic semantic tag `" << tag << "' multiply defined" <<
                endl;
    else
        d_polymorphic[tag] = typeSpec; 
}
