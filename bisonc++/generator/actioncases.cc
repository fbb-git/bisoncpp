#include "generator.ih"

void Generator::actionCases(ostream &out) const
{
    key(out);
    out << '\n';

    if (d_arg.option('D'))      // no decoration of the parse tree
    {
        out << setw(d_indent) << "" << 
                "// inserting actioncases suppressed by option "
                                                        "--no-decoration\n";
        return;
    }

    vector<Production const *> const &productions = d_rules.productions();

    for (auto prod: productions)
        Production::insertAction(prod, out, d_options.lines(), d_indent);
}







