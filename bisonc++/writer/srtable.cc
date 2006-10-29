#include "writer.ih"

void Writer::srTable(State const *sp, SRContext &context)
{
    bool acceptState = sp->isAcceptState();
    bool tokenNeeded = sp->terminalTransitions() || acceptState;
                            
            
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
            "}, // " <<
                    (
                        acceptState ? "ACCEPTING STATE" :
                        tokenNeeded ? "SHIFTING STATE"  :
                                      "REDUCING STATE"
                    ) << "\n";

    transitions(sp->next(), context.out);   // Write all transitions.

    if (acceptState)
        context.out << "    { {" << Rules::eofTerminal() << 
                                                "}, { PARSE_ACCEPT }},\n";

    reductions(context.out, *sp);        

    if 
    (
        StateItem const *defaultReduction = 
                         sp->reduction(sp->defaultReduction())
    )
         context.out << "    { {  0}, {" << 
                setw(4) << -static_cast<int>(defaultReduction->nr()) << "} }"
                                              "  // DEFAULT REDUCTION\n";
    else
         context.out << "    { {  0}, {   0} }  // SEARCH SENTINEL\n";


    context.out << "};\n";
}




