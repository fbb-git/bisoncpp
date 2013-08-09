#include "options.ih"

void Options::setPathStrings()
{
    setPath(&d_baseClassHeader, 'b', d_genericFilename, "base.h",
            "baseclass-header");

    setPath(&d_classHeader, 'c', d_genericFilename, ".h", "class-header");

    setPath(&d_implementationHeader, 'i', d_genericFilename, ".ih",
                                                    "implementation-header");

    setPath(&d_parsefunSource, 'p', s_defaultParsefunSource, "",
                                                    "parsefun-source");
}
