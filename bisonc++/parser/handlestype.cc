#include "parser.ih"

// See 'README.dollar' in this directory for a description of the actions
// involved at these alternatives.

//FBB: see returnPolymorphic and substitutedollar

void Parser::handleSTYPE(Block &block, AtDollar const &atd) 
{
    string const &stype = d_rules.sType();

    if (d_semType != POLYMORPHIC)
    {
        emsg << '`' << &d_rules.lastProduction() << 
                "':  $$(...) requires %polymorphic" << endl;
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




