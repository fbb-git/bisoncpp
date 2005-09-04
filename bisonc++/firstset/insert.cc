#include "firstset.ih"


ostream &FirstSet::insert(ostream &out) const
{
    out << "{ ";

    Element::SDContext context = {out, " "};

                                // passing Element const * values
    for_each(begin(), end(), 
        Wrap1c<Element, Element::SDContext>
                  (&Element::sDisplay, context));

    if (d_epsilon)
        out << "<e> ";

    out << "}";

    return out;
}
