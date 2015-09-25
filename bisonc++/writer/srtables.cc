#include "writer.ih"

void Writer::srTables() const
{
    *d_out << "\n"
        "// State info and SR__ transitions for each state.\n"
        "\n";

    TableSupport support;

    support <<  "    { { "  
            <<  "}, { "  
            <<  "} }, ";

    Table   table(support, 3, Table::ROWWISE);

    table << Align(2, std::left);

    for_each(
        State::begin(), State::end(),
        [&](State const *state)
        {
            srTable(state, d_baseclass, table, *d_out);
        }
    );

    *d_out << '\n';
}
