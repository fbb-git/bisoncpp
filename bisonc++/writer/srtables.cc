#include "writer.ih"

void Writer::srTables() const
{
    *d_out << "\n"
        "// State info and SR transitions for each state.\n"
        "\n";

    SRContext context = {d_baseclass, *d_out};

    for_each(State::begin(), State::end(),
             Wrap1c<State, SRContext>(srTable, context));

    *d_out << endl;
}
