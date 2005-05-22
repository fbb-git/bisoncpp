#include "followset.ih"

ostream &FollowSet::ostrInsert(ostream &out) const
{
    out << "{ ";

    Element::SDContext context = {out, " "};

                            // passing Element const *
    for_each(begin(), end(), 
        Wrap1<Element const *, Element::SDContext>
             (&Element::sDisplay, context));

    if (d_EOF)
        out << "<EOF> ";

    out << "}";

    return out;
}
