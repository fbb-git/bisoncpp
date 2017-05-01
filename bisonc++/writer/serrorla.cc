#include "writer.ih"

void Writer::sErrorLA() const
{
    *d_out << "\n"
        "// State info and SR__ transitions for each state.\n"
        "\n"
        "std::unordered_set<int> s_errorLA[] =\n"
        "{\n"
        "    {},\n";

    size_t idx = 0;
    for_each(
        State::begin(), State::end(),
        [&](State const *state)
        {
            errorLAset(&idx, state, *d_out);    // write this State's _error_ 
        }                                       // LA set, if it is an ERROR 
    );                                          // state

    *d_out << "};\n"
              "\n";
}
