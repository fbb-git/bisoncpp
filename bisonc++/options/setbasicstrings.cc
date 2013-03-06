#include "options.ih"

bool Options::setBasicStrings()
{
    if (d_arg.option(0, 'n'))
        fmsg << "Option --namespace discontinued. "
                                    "Use the %namespace directive instead";

        // classname can only be followed by IDENTIFIERs, so no undelimit is 
        // required.

    d_arg.option(&d_className, "class-name");
    if (d_className.empty())
        d_className = s_defaultClassName;



    d_scannerTokenFunction = setOpt("scanner-token-function",
                                    d_flex ?
                                        s_yylex
                                    :
                                        s_defaultScannerTokenFunction); 

    d_scannerMatchedTextFunction = setOpt("scanner-matched-text-function",
                                    d_flex ?
                                        s_YYText
                                    :
                                        s_defaultScannerMatchedTextFunction); 

    string nTokens;
    if (d_arg.option(&nTokens, "required-tokens"))
        d_requiredTokens = A2x(nTokens);
    
    d_arg.option(&d_genericFilename, 'f');
    if (d_genericFilename.empty())
        d_genericFilename = d_className;

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
