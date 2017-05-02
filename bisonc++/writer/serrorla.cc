#include "writer.ih"

void Writer::sErrorLA() const
{
    LAsetVector laSets;

    for_each(
        State::begin(), State::end(),
        [&](State *state)
        {
            errorLAset(laSets, state);  // determine this State's _error_ 
        }                               // LA set if it is an ERR_ITEM state
    );


    *d_out << "\n"
        "// State info and SR__ transitions for each state.\n"
        "\n"
        "std::unordered_set<int> s_errorLA[] =\n"
        "{\n";

    size_t idx = -1;
    for (auto const &set: laSets)
    {
        *d_out << "    {";
        set.listElements(*d_out, ", ");
        *d_out << "},     // " << ++idx << '\n';
    }

    *d_out << "};\n"
              "\n";
}




