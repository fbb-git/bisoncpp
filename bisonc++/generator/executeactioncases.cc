#include "generator.ih"

void Generator::executeActionCases(ostream &out) const
{
    if (d_debug || not d_arg.option('a'))
        return;

    key(out);

    out << R"(
    std::cerr << "executeAction case " << production << '\n';
)";
}
