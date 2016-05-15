#include "generator.ih"

void Generator::staticData(ostream &out) const
{
    d_writer.useStream(out);

    key(out);

    out << R"(
    enum                        // size to expand the state-stack with when
    {                           // full
        STACK_EXPANSION__ = )" << d_options.stackExpansion() << R"(
    };
)";

    d_writer.productions();
    d_writer.srTables();
    d_writer.statesArray();

    if (d_genDebug || d_printTokens)
        d_writer.symbolicNames();

    out << "} // anonymous namespace ends\n"
            "\n";
}

