#include "generator.ih"

void Generator::polymorphicImpl(ostream &out) const
{
    if (not d_options.polymorphic())
        return;

    key(out);

    out <<
    "namespace Meta__\n"
    "{\n"
    "   Base::~Base()\n"
    "   {}\n"
    "}\n"
    "\n";
}

