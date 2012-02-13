#include "options.ih"

bool Options::setBasicStrings()
{
    d_className = setOpt("class-name", s_defaultClassName);

    d_scannerTokenFunction = setOpt("scanner-token-function",
                                    s_defaultScannerTokenFunction); 

    d_scannerMatchedTextFunction = setOpt("scanner-matched-text-function",
                                    s_defaultScannerMatchedTextFunction); 

    d_scannerPrintFunction = setOpt("print", d_scannerMatchedTextFunction);

    d_arg.option(&d_nameSpace, 'n');

    string nTokens;
    if (d_arg.option(&nTokens, "required-tokens"))
        d_requiredTokens = A2x(nTokens);
    

    d_arg.option(&d_genericFilename, 'f');
    if (d_genericFilename.empty())
        d_genericFilename = String::lc(d_className);

     d_arg.option(&d_skeletonDirectory, 'S');
    if (d_skeletonDirectory.empty())
        d_skeletonDirectory = s_defaultSkeletonDirectory;
    cleanDir(d_skeletonDirectory);

    bool targetDirOption =      // true if --target-directory was specified
       d_arg.option(&d_targetDirectory, "target-directory");

    if (d_targetDirectory.empty())
        d_targetDirectory = s_defaultTargetDirectory;
    else
        cleanDir(d_targetDirectory);

    return targetDirOption;
}
