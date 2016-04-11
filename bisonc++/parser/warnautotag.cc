#include "parser.ih"

string Parser::warnAutoTag(bool midRule, AtDollar const &atd, 
                            char const *label) const
{
    string tag = productionTag(atd.nr());        // get the element's tag

    if (midRule and not tag.empty())
    {            
        stdWmsg(atd) << " auto " << label << " `" << tag << 
                            "' not used in mid-rule action" << endl;
        tag.clear();
    }
    return tag;
}
