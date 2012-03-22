#include "options.ih"

// define the polymorphic semantic value type, embedded in a shared_ptr

void Options::setPolymorphicDecl()
{
    if (isFirstStypeDefinition())
        d_stackDecl = "typedef std::shared_ptr<Base__> STYPE__;\n";

    d_polymorphic = true;
}

