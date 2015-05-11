#include "state.ih"

void State::computeLAsets() 
{
    for_each(d_itemVector.begin(), d_itemVector.begin() + d_nKernelItems,
        [&](StateItem &kernelItem)
        {
            distributeLAsetOf(kernelItem);
        }
    );

        cout << "\nFinal LA sets:\n";
        for (auto const &stItem: d_itemVector)
            cout << stItem << ", LA set: " << stItem.lookaheadSet() << '\n';
}
