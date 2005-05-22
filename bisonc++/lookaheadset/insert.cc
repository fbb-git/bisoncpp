#include "lookaheadset.ih"

ostream &LookaheadSet::insert(ostream &out) const
{
    out << "{ ";

    Element::SDContext context = {out, " "};

    for_each(begin(), end(),
        Wrap1<Element const *, Element::SDContext>
                  (&Element::sDisplay, context));

    if (d_EOF)
        out << "<EOF> ";

    out << "}";

    return out;
}
