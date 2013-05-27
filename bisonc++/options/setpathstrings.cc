#include "options.ih"

void Options::setPathStrings()
{
    setPath(&d_baseClassHeader, 'b', d_genericFilename, "base.h");

    setPath(&d_classHeader, 'c', d_genericFilename, ".h");

    setPath(&d_implementationHeader, 'i', d_genericFilename, ".ih");

    setPath(&d_parsefunSource, 'p', s_defaultParsefunSource, "");
}
