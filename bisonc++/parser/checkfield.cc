#include "parser.ih"

void Parser::checkField(std::string const &field)
{
    string msg;

	switch (d_semType)
    {
        case SINGLE:
            msg = "%type not available for %stype semantic values";
        break;

        case POLYMORPHIC:
            if 
            (
                field != s_stype        // STYPE__ is OK
                &&
                d_polymorphic.find(field) == d_polymorphic.end()
            )
                msg = "no polymorphic tag `" +  field + '\'';
        break;

        case UNION:
        {
            Pattern pattern("\\b" + field + "\\b");
            if (not (pattern << d_options.stype()))
                msg = "no union field `" + field + '\'';
            break;
        }
    }

    if (not msg.empty())
        emsg << msg << endl;

    d_field = field;            
}
