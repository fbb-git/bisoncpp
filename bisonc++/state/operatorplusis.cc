#include "state.ih"

void State::operator+=(Item const &item) 
{
    if (find(d_kernel.begin(), d_kernel.end(), item) == d_kernel.end())
        d_kernel.push_back(item);
}
