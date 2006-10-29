#include "writer.ih"

void Writer::reductions(ostream &out, State const &state)
{
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
            reduction(out, *state.reduction(idx));
    }
}
