#include "generator.ih"

void Generator::executeActionCases(ostream &out) const
{
    if (!d_genDebug)
        return;

    key(out);

    out << R"(
    if (d_actionCases__)
        s_out__ << "executeAction case " << production << '\n' << dflush__;
)";
}
