#include "options.ih"

// define the polymorphic semantic value type, embedded in a shared_ptr

void Options::setPolymorphicDecl()
{
    if (isFirstStypeDefinition())
        d_stackDecl = "    typedef Meta_::SType STYPE_;\n";

    d_polymorphic = true;
}

