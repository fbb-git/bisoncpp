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

    if (stype.empty())
    {
        emsg << '`' << &d_rules.lastProduction() << 
                "':  $$(...) requires %type-tagged production rules" << endl;
        return;
    }

    string replacement = s_semanticValue;
    replacement += ".assign<Tag__::" + d_rules.sType() + ">(";

                                        // replace $$ by the semantic value
    block.replace(atd.pos(), atd.length(), replacement);
}




