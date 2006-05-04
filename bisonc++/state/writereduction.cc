#include "state.ih"

// struct WRContext                       // writeReductionContext
// {
//     std::ostream &out;
//     int nr;
// };

void State::writeReduction(ReduceMapValue const &reduce, ostream &out)
{
    WRContext context = {out, reduce.first->nr()};
    for_each(reduce.second.begin(), reduce.second.end(),
        Wrap1c<Element, WRContext>(writeReduceAt, context));
}
