#include "writer.ih"

void Writer::srTable(State const *sp, SRContext &context)
{
    bool acceptState = sp->isAcceptState();
    bool tokenNeeded = sp->terminalTransitions() || acceptState;

    string stateType;
    string endText;

    if (acceptState)
    {
        stateType = "ACCEPTING";
        endText   = "ACCEPTING STATE SENTINEL";
    }
    else if (tokenNeeded)
    {
        stateType = "SHIFTING";
        endText   = "SEARCH SENTINEL";
    }
    else
    {
        stateType = "REDUCING";
        endText   = "DEFAULT REDUCTION";
    }
    
    context.out << "\n"                     // Write the table header
        "SR s_" << sp->idx() << "[] =\n"
        "{\n" <<
        "    {"
                "{" << 
                    sp->typeName() << 
                "}, "
                "{" << 
                    (tokenNeeded ? "" : "-") <<
                    sp->transitions() + sp->reductionsLAsize() + 
                    acceptState + 1 <<
                "}"
            "}, // " << stateType << " STATE\n";

    transitions(sp->next(), context.out);   // Write all transitions.

    if (acceptState)
        context.out << "    { {" << Rules::eofTerminal() << 
                                                "}, { PARSE_ACCEPT }},\n";
    reductions(context.out, *sp);        

    StateItem const *defaultReduction = 
                         sp->reduction(sp->defaultReduction());

    if (defaultReduction && not acceptState)
         context.out << "    { {  0}, {" << 
                setw(4) << -static_cast<int>(defaultReduction->nr()) << "} }";
    else
         context.out << "    { {  0}, {   0} }";

    context.out << "  // " << endText << "\n" 
                   "};\n";
}




