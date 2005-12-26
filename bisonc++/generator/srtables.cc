#include "generator.ih"

void Generator::srTables(ostream &out) const
{
    out << "\n"
        "// State info and SR transitions for each state.\n"
        "\n";

    State::WSAContext context = {d_baseclassScope, out};

    for_each(d_itemSets.states().begin(), d_itemSets.states().end(),
                Wrap1c<State, State::WSAContext>
                          (&State::writeStateArray, context));
    out << endl;
}
