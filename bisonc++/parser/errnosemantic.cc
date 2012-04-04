#include "parser.ih"

void Parser::errNoSemantic(char const *label, std::string const &tag) const
{
    emsg << &d_rules.lastProduction() << ":\n"
            "\tno semantic " << label << " `" << tag << '\'' << endl;
}
