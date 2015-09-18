#include "parser.hh"

void Parser::addPolymorphic(string const &tag, string const &typeSpec) 
{
    if (d_semType != POLYMORPHIC)
        return;

    if (d_polymorphic.find(tag) != d_polymorphic.end())
        emsg << "Polymorphic semantic tag `" << tag << "' multiply defined" <<
                endl;
    else
        d_polymorphic[tag] = typeSpec; 
}
