#include "parser.ih"

void Parser::noSemanticTag(std::string const &tag) const
{
    emsg << &d_rules.lastProduction() << ":\n"
            "\tno such semantic type identifier `" << tag << '\'' << endl;
}
