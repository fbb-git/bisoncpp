#include "parser.ih"

string Parser::warnAutoTag(bool midRule, AtDollar const &atd) const
{
    string tag = productionTag(atd.nr());        // get the element's tag

    if (midRule and not tag.empty())
    {            
        stdWmsg(atd) << " auto " << s_autoTypeLabel[d_semType] << " `" << 
                            tag << "' ignored in mid-rule action" << endl;
        tag.clear();
    }

    return tag;
}
