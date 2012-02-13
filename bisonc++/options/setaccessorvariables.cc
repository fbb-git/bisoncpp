#include "options.ih"

void Options::setAccessorVariables()
{
    if (d_arg.option('d'))
        d_debug = true;

    if (d_arg.option(0, "error-verbose"))
        d_errorVerbose = true;

    if (d_arg.option(0, "flexcpp"))
        d_flexcpp = true;

    if (d_arg.option(0, "no-lines"))
        d_lines = false;

    if (d_className.empty())
        d_className = s_defaultClassName;

    d_arg.option(&d_genericFilename, 'f');

    string filename = d_genericFilename.size() ? 
                            d_genericFilename 
                        :
                            String::lc(d_className);

    d_arg.option(&d_preInclude, 'H');
    addIncludeQuotes(&d_preInclude);

    bool targetDirOption =      // true if --target-directory was specified
        d_arg.option(&d_targetDirectory, "target-directory");

    if (d_targetDirectory.empty())
        d_targetDirectory = s_defaultTargetDirectory;
    else
        cleanDir(d_targetDirectory);


    setPath(&d_baseClassHeader, 'b', targetDirOption, "baseclass-header", 
            filename, "base.h");


    d_arg.option(&d_implementationHeader, 'i'))
    addIncludeQuotes(&d_implementationHeader);

    d_arg.option(&d_nameSpace, 'n');

    setPath(&d_parsefunSource, 'p', targetDirOption, "parsefun-source",
            s_defaultParsefunSource, "");

    d_arg.option(&d_printFunction, "print");
    d_printFunction = undelimit(d_printFunction);

    string nTokens;
    if (d_arg.option(&nTokens, "required-tokens"))
        d_requiredTokens = A2x(nTokens);
    
    d_arg.option(&d_scannerInclude, 's');
    addIncludeQuotes(&d_scannerInclude);

    d_arg.option(&d_scannerTokenFunction, "scanner-token-function");
    d_scannerTokenfunction = 
            d_scannerTokenfunction.empty() ?
                s_defaultScannerTokenFunction
            :
                undelimit(d_scannerTokenFunction;

    d_arg.option(&d_scannerMatchedTextFunction, 
                                            "scanner-matched-text-function");
    d_scannerMatchedTextfunction = 
            d_scannerMatchedTextfunction.empty() ?
                s_defaultScannerMatchedTextFunction
            :
                undelimit(d_scannerMatchedTextFunction;

    if (d_printFunction.empty())
        d_printFunction = d_scannerMatchedTextFunction;

     d_arg.option(&skeletonDir, 'S');
        d_arg.option(&d_targetDirectory, "target-directory");

    if (d_targetDirectory.empty())
        d_targetDirectory = s_defaultTargetDirectory;
    else
        cleanDir(d_targetDirectory);

//
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

    // Paths


//

//    setPath(&d_classHeaderPath, 'c', targetDirOption, "class-header", 
//            className, ".h");
//
//
//    setPath(&d_implementationHeaderPath, 'i', targetDirOption, 
//            "implementation-header", className, ".ih");
//
//    setPath(&d_lexSourcePath, 'l', targetDirOption, 
//            "lex-source", String::lc(d_lexFunctionName), ".cc");

}




