#include "writer.ih"

void Writer::srTables() const
{
    TableSupport support;

    support <<  "    { { "  
            <<  "}, { "  
            <<  "}"
            <<  " }, ";

    Table   table(support, 4, Table::ROWWISE);

    table << Align(3, std::left);

    size_t errorLAidx = 0;

    for_each(
        State::begin(), State::end(),
        [&](State const *state)
        {
            srTable(&errorLAidx, state, d_baseclass, table, *d_out);
        }
    );

    *d_out << '\n';
}
