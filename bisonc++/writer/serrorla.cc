#include "writer.ih"

void Writer::sErrorLA() const
{
    *d_out << "\n"
        "// State info and SR__ transitions for each state.\n"
        "\n"
        "std::unordered_set<int> s_errorLA[] =\n"
        "{\n"
        "    {},\n";

    for_each(
        State::begin(), State::end(),
        [&](State const *state)
        {
            errorLAset(state, *d_out);
        }
    );

    *d_out << "};\n"
              "\n";
}
