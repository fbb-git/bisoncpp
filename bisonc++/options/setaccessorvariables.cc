#include "options.ih"

void Options::setAccessorVariables()
{
//    return !d_arg.option(0, "no-lines") &&
//        (d_arg.option('l') || d_lines);

//    if (d_arg.option(&d_preInclude, 'H'))
//        addIncludeQuotes(&d_preInclude);
//    
//    if (d_arg.option(&d_implementationHeader, 'i'))
//        addIncludeQuotes(&d_implementationHeader);
//    
//    if (d_arg.option(&d_scannerInclude, 's'))
//        addIncludeQuotes(&d_scannerInclude);
//
//    d_arg.option(&d_matchedTextFunction, "print");

//    d_arg.option(&d_nameSpace, 'n');
//    d_arg.option(&d_parsefunSource, 'p');
//    d_arg.option(&d_genericFilename, 'f');

//    if (!d_arg.option(&nTokens, "required-tokens"))
//        d_requiredTokens = d_scanner.number();
//
//
//    string skeletonDir;
//
//     d_arg.option(&skeletonDir, 'S');
//
//    if (d_className.empty())
//        d_className = s_defaultClassName;
//
//    if (!d_arg.option(&d_baseclassSkeleton, 'B'))
//        d_baseclassSkeleton =   skeletonDir.empty() ?
//                                    s_defaultBaseclassSkeleton
//                                :
//                                    skeletonDir + BISONCPPBASE_H;
//
//    if (!d_arg.option(&d_classSkeleton, 'C'))
//        d_classSkeleton =   skeletonDir.empty() ?
//                                s_defaultClassSkeleton
//                            :    
//                                skeletonDir + BISONCPP_H;
//
//    if (!d_arg.option(&d_implementationSkeleton, 'I'))
//        d_implementationSkeleton =  skeletonDir.empty() ? 
//                                        s_defaultImplementationSkeleton
//                                    :    
//                                        skeletonDir + BISONCPP_IH;
//
//    if (!d_arg.option(&d_parsefunSkeleton, 'P'))
//        d_parsefunSkeleton =    skeletonDir.empty() ?
//                                    s_defaultParsefunSkeleton
//                                :    
//                                    skeletonDir + BISONCPP_CC;
//    if 
//    (
//        !d_arg.option(&d_parsefunSource, 'p')
//        &&
//        d_parsefunSource.empty()
//    )
//        d_parsefunSource = s_defaultParsefunSource;
//
//    if 
//    (
//        !d_arg.option(&d_baseclassHeader, 'b')
//        &&
//        d_baseclassHeader.empty()
//    )
//        setName(&d_baseclassHeader, "base.h");
//
//    if 
//    (
//        !d_arg.option(&d_classHeader, 'c')
//        &&
//        d_classHeader.empty()
//    )
//        setName(&d_classHeader, ".h");
//
//    if 
//    (
//        !d_arg.option(&d_implementationHeader, 'i')
//        &&
//        d_implementationHeader.empty()
//    )
//        setName(&d_implementationHeader, ".ih");
//
//    Arg &arg = Arg::instance();
//
//    if (d_className.empty())
//        d_className = s_defaultClassName;
//
//    if (d_lexFunctionName.empty())
//        d_lexFunctionName = s_defaultLexFunctionName;
//
//    arg.option(&d_nameSpace, 'n');  // -n overrules %namespace spec in lexer
//
//    // Skeletons
//    if (!arg.option(&d_skeletonDirectory, 'S') && d_skeletonDirectory.empty())
//        d_skeletonDirectory = s_defaultSkeletonDirectory;
//
//    if (!arg.option(&d_baseClassSkeleton, 'B'))
//        d_baseClassSkeleton      = d_skeletonDirectory + FLEXCPPBASE_H;
//
//    if (!arg.option(&d_classSkeleton, 'C'))
//        d_classSkeleton          = d_skeletonDirectory + FLEXCPP_H;
//
//    if (!arg.option(&d_implementationSkeleton, 'I'))
//        d_implementationSkeleton = d_skeletonDirectory + FLEXCPP_IH;
//
//    if (!arg.option(&d_lexSkeleton, 'L'))
//        d_lexSkeleton            = d_skeletonDirectory + FLEXCPP_CC;
//
//    if (arg.option(0, "interactive")) // does not overwrite %option when no
//        d_interactive = true;         // --interactive is supplied
//
//    d_debugAll |= arg.option('d');         // debug facility requested
//
//    if (arg.option(0, "lines"))             // --lines overrules 
//        d_lines = true;                     // --no-lines
//    else if (arg.option(0, "no-lines"))
//        d_lines = false;
//
//    // Paths
//
//    bool targetDirOption = arg.option(&d_targetDirectory, "target-directory");
//
//    if (d_targetDirectory.length() && *d_targetDirectory.rbegin() != '/')
//        d_targetDirectory += '/';
//
//    string className = String::lc(d_className);
//
//    if (!targetDirOption && d_targetDirectory.empty())
//        d_targetDirectory = s_defaultTargetDirectory;
//
//    setPath(&d_classHeaderPath, 'c', targetDirOption, "class-header", 
//            className, ".h");
//
//    setPath(&d_baseClassHeaderPath, 'b', targetDirOption, "base-class-header", 
//            className, "base.h");
//
//    setPath(&d_implementationHeaderPath, 'i', targetDirOption, 
//            "implementation-header", className, ".ih");
//
//    setPath(&d_lexSourcePath, 'l', targetDirOption, 
//            "lex-source", String::lc(d_lexFunctionName), ".cc");

}




