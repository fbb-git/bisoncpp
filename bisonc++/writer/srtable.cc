#include "writer.ih"

void Writer::srTable(State const *sp, SRContext &context)
{
    bool acceptState = sp->isAcceptState();

    StateItem const *defaultReduction = 
                         sp->reduction(sp->defaultReduction());

        // A token is needed if there are terminaltransitions or multiple
        // reductions (or for the accept state, set at state/define.cc)
    bool tokenNeeded = sp->terminalTransitions() || sp->reductions() > 1;

    int stateType = sp->type();

    if (tokenNeeded)
        stateType |= State::REQ_TOKEN;

    if (defaultReduction)
        stateType |= State::DEF_RED;


    context.out << "\n"                     // Write the table header
        "SR s_" << sp->idx() << "[] =\n"
        "{\n";

    context.table.clear();

    context.table << State::typeName(stateType) << 
            sp->transitions() + sp->reductionsLAsize() + acceptState + 1 <<
            def;

    transitions(context.table, sp->next());

    if (acceptState)
        context.table << Rules::eofTerminal() << "PARSE_ACCEPT" << def;

    reductions(context.table, *sp);        

    context.table << 0 << 
        (defaultReduction ? -static_cast<int>(defaultReduction->nr()) : 0) <<
        def;

    context.out << context.table << "\n"
                   "};\n";
}








