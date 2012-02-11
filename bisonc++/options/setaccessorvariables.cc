#include "options.ih"

void Options::setAccessorVariables()
{
    Arg &arg = Arg::instance();

    if (d_className.empty())
        d_className = s_defaultClassName;

    if (d_lexFunctionName.empty())
        d_lexFunctionName = s_defaultLexFunctionName;

    arg.option(&d_nameSpace, 'n');  // -n overrules %namespace spec in lexer

    // Skeletons
    if (!arg.option(&d_skeletonDirectory, 'S') && d_skeletonDirectory.empty())
        d_skeletonDirectory = s_defaultSkeletonDirectory;

    if (!arg.option(&d_baseClassSkeleton, 'B'))
        d_baseClassSkeleton      = d_skeletonDirectory + FLEXCPPBASE_H;

    if (!arg.option(&d_classSkeleton, 'C'))
        d_classSkeleton          = d_skeletonDirectory + FLEXCPP_H;

    if (!arg.option(&d_implementationSkeleton, 'I'))
        d_implementationSkeleton = d_skeletonDirectory + FLEXCPP_IH;

    if (!arg.option(&d_lexSkeleton, 'L'))
        d_lexSkeleton            = d_skeletonDirectory + FLEXCPP_CC;

    if (arg.option(0, "interactive")) // does not overwrite %option when no
        d_interactive = true;         // --interactive is supplied

    d_debugAll |= arg.option('d');         // debug facility requested

    if (arg.option(0, "lines"))             // --lines overrules 
        d_lines = true;                     // --no-lines
    else if (arg.option(0, "no-lines"))
        d_lines = false;

    // Paths

    bool targetDirOption = arg.option(&d_targetDirectory, "target-directory");

    if (d_targetDirectory.length() && *d_targetDirectory.rbegin() != '/')
        d_targetDirectory += '/';

    string className = String::lc(d_className);

    if (!targetDirOption && d_targetDirectory.empty())
        d_targetDirectory = s_defaultTargetDirectory;

    setPath(&d_classHeaderPath, 'c', targetDirOption, "class-header", 
            className, ".h");

    setPath(&d_baseClassHeaderPath, 'b', targetDirOption, "base-class-header", 
            className, "base.h");

    setPath(&d_implementationHeaderPath, 'i', targetDirOption, 
            "implementation-header", className, ".ih");

    setPath(&d_lexSourcePath, 'l', targetDirOption, 
            "lex-source", String::lc(d_lexFunctionName), ".cc");

}
