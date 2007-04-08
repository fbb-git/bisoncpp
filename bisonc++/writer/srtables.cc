#include "writer.ih"

void Writer::srTables() const
{
    *d_out << "\n"
        "// State info and SR transitions for each state.\n"
        "\n";

    Support support;

    support <<  "    { { "  
            <<  "}, { "  
            <<  "} }, ";

    Table   table(support, 3, Table::ROWWISE);

    table << Align(2, std::left);

    SRContext context = {d_baseclass, table, *d_out};

    for_each(State::begin(), State::end(),
             FnWrap1c<State const *, SRContext &>(srTable, context));

    *d_out << endl;
}
