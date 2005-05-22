#include "parser.ih"

void Parser::setAccessorVariables() 
{
    if (d_className.empty())
        d_className = s_defaultClassName;

    if (d_baseclassSkeleton.empty())
        d_baseclassSkeleton = s_defaultBaseclassSkeleton;

    if (d_classSkeleton.empty())
        d_classSkeleton = s_defaultClassSkeleton;

    if (d_implementationSkeleton.empty())
        d_implementationSkeleton = s_defaultImplementationSkeleton;

    if (d_parsefunSkeleton.empty())
        d_parsefunSkeleton = s_defaultParsefunSkeleton;

    if (d_parsefunSource.empty())
        d_parsefunSource = s_defaultParsefunSource;

    setName(&d_baseclassHeader, "base.h");
    setName(&d_classHeader, ".h");
    setName(&d_implementationHeader, ".ih");
}
