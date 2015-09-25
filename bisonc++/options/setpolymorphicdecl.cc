#include "options.ih"

// define the polymorphic semantic value type, embedded in a shared_ptr

void Options::setPolymorphicDecl()
{
    if (isFirstStypeDefinition())
        d_stackDecl = "    typedef Meta__::SType STYPE__;\n";

    d_polymorphic = true;
}

