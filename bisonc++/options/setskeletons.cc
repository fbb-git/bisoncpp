#include "options.hh"

void Options::setSkeletons()
{
    if (!d_arg.option(&d_baseClassSkeleton, 'B'))
        d_baseClassSkeleton = 
                            d_skeletonDirectory + s_defaultBaseClassSkeleton;

    if (!d_arg.option(&d_classSkeleton, 'C'))
        d_classSkeleton = d_skeletonDirectory + s_defaultClassSkeleton;

    if (!d_arg.option(&d_implementationSkeleton, 'I'))
        d_implementationSkeleton =  
                        d_skeletonDirectory + s_defaultImplementationSkeleton;

    if (!d_arg.option(&d_parsefunSkeleton, 'P'))
        d_parsefunSkeleton = d_skeletonDirectory + s_defaultParsefunSkeleton;

    if (!d_arg.option(&d_polymorphicSkeleton, 'M'))
        d_polymorphicSkeleton = 
                        d_skeletonDirectory + s_defaultPolymorphicSkeleton;

    if (!d_arg.option(&d_polymorphicInlineSkeleton, 'm'))
        d_polymorphicInlineSkeleton = d_skeletonDirectory + 
                                      s_defaultPolymorphicInlineSkeleton;
}
