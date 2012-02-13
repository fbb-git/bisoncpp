#include "options.ih"

void Options::setPathStrings(bool targetDirOption)
{
    setPath(&d_baseClassHeader, 'b', targetDirOption, "baseclass-header", 
            d_genericFilename, "base.h");

    setPath(&d_classHeader, 'c', targetDirOption, "class-header", 
            d_genericFilename, ".h");

    setPath(&d_implementationHeader, 'i', targetDirOption, 
            "implementation-header", d_genericFilename, ".ih");

    setPath(&d_parsefunSource, 'p', targetDirOption, "parsefun-source",
            s_defaultParsefunSource, "");
}
