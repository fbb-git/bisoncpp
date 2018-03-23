#include "generator.ih"

void Generator::executeActionCases(ostream &out) const
{
    if (!d_genDebug)
        return;

    key(out);

    out << R"(
    if (d_actionCases_)
        s_out_ << "executeAction case " << production << '\n' << dflush_;
)";
}
