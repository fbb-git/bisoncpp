#include "state.ih"

// struct StatusOrReduce
// {
//     Reductions &reductions;
//     ShiftReduce::Status status;
// };

void State::setStatusOrReduce(ActionTable::value_type const &action, 
                              StatusOrReduce &context)
{
    ShiftReduce const &sr = action.second;
    
    if (sr.accept())
        reinterpret_cast<int &>(context.status) |= ShiftReduce::ACCEPT;
    else if (sr.shift())
        reinterpret_cast<int &>(context.status) |= ShiftReduce::SHIFT;
    else // sr.reduce()
        context.reductions.insert(action.first, sr.production());
         // insert Terminal const * (action.first) and 
         //                                     Production rule to reduce to
}
