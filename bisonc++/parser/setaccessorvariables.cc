#include "parser.ih"

// the default is overruled by the grammar specification, which in turn is
// overruled by the command-line. So,
//  If the command-line is not set and if the data-member is empty, use the
// default

void Parser::setAccessorVariables() 
{
    string skeletonDir;

     d_arg.option(&skeletonDir, 'S');

    if (d_className.empty())
        d_className = s_defaultClassName;

    if (!d_arg.option(&d_baseclassSkeleton, 'B'))
        d_baseclassSkeleton =   skeletonDir.empty() ?
                                    s_defaultBaseclassSkeleton
                                :
                                    skeletonDir + BISONCPPBASE_H;

    if (!d_arg.option(&d_classSkeleton, 'C'))
        d_classSkeleton =   skeletonDir.empty() ?
                                s_defaultClassSkeleton
                            :    
                                skeletonDir + BISONCPP_H;

    if (!d_arg.option(&d_implementationSkeleton, 'I'))
        d_implementationSkeleton =  skeletonDir.empty() ? 
                                        s_defaultImplementationSkeleton
                                    :    
                                        skeletonDir + BISONCPP_IH;

    if (!d_arg.option(&d_parsefunSkeleton, 'P'))
        d_parsefunSkeleton =    skeletonDir.empty() ?
                                    s_defaultParsefunSkeleton
                                :    
                                    skeletonDir + BISONCPP_CC;
    if 
    (
        !d_arg.option(&d_parsefunSource, 'p')
        &&
        d_parsefunSource.empty()
    )
        d_parsefunSource = s_defaultParsefunSource;

    if 
    (
        !d_arg.option(&d_baseclassHeader, 'b')
        &&
        d_baseclassHeader.empty()
    )
        setName(&d_baseclassHeader, "base.h");

    if 
    (
        !d_arg.option(&d_classHeader, 'c')
        &&
        d_classHeader.empty()
    )
        setName(&d_classHeader, ".h");

    if 
    (
        !d_arg.option(&d_implementationHeader, 'i')
        &&
        d_implementationHeader.empty()
    )
        setName(&d_implementationHeader, ".ih");
}




