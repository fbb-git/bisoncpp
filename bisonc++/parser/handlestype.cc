#include "parser.ih"

// See 'README.dollar' in this directory for a description of the actions
// involved at these alternatives.

void Parser::handleSTYPE(Block &block, AtDollar const &atd) 
{
    if (d_semType != POLYMORPHIC)
    {
        emsg << '`' << &d_rules.lastProduction() << 
                "':  $$(...) requires %polymorphic" << endl;
        return;
    }

    string const &stype = d_rules.sType();

    if (stype.empty())
    {
        emsg <<  '`' << &d_rules.lastProduction() << 
                "':  $$(...) requires a tagged left-hand side non-terminal" <<
                                                                    endl;
        return;
    }

    string replacement = s_semanticValue;

    replacement += 
        stype == "STYPE__"?
            " = ("s
        :
            ".assign<Tag__::" + d_rules.sType() + ">(";

                                        // replace $$ by the semantic value
    block.replace(atd.pos(), atd.length(), replacement);
}




