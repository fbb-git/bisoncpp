#include "writer.ih"

void Writer::reductions(Table &table, State const &state)
{
    return;
    cerr << "State: " << state.idx() << ", default reduction: " <<
            state.defaultReduction() << '\n';
    for 
    (
        size_t idx = 0, 
                defaultReduction = state.defaultReduction(),
                nReductions = state.reductions();
            idx != nReductions;
                ++idx
    )
    {
        if (idx != defaultReduction)
        {
            cerr << "   Insert non default reduction " << idx << '\n';
            reduction(table, *state.reduction(idx));
        }
    }
}
