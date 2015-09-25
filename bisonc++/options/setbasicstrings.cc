#include "options.ih"

void Options::setBasicStrings()
{
        // classname/namespace can only be followed by IDENTIFIERs, 
        // so no undelimit is required.

    if (d_arg.option(&d_nameSpace, 'n'))
        d_warnOptions.insert("namespace");

    if (d_arg.option(&d_className, "class-name"))
        d_warnOptions.insert("class-name");
    else if (d_className.empty())           
        d_className = s_defaultClassName;


    if (d_arg.option(&d_scannerClassName, "scanner-class-name"))
        d_warnOptions.insert("scanner-class-name");
    else if (d_scannerClassName.empty()) 
        d_scannerClassName = s_defaultScannerClassName;


    setOpt(&d_scannerTokenFunction, "scanner-token-function",
                                    d_flex ?
                                        s_yylex
                                    :
                                        s_defaultScannerTokenFunction); 

    setOpt(&d_scannerMatchedTextFunction, "scanner-matched-text-function",
                                    d_flex ?
                                        s_YYText
                                    :
                                        s_defaultScannerMatchedTextFunction); 

    string nTokens;
    if (d_arg.option(&nTokens, "required-tokens"))
        d_requiredTokens = stoul(nTokens);
    
    d_arg.option(&d_genericFilename, 'f');
    if (d_genericFilename.empty())
        d_genericFilename = d_className;

     d_arg.option(&d_skeletonDirectory, 'S');
    if (d_skeletonDirectory.empty())
        d_skeletonDirectory = s_defaultSkeletonDirectory;
    cleanDir(d_skeletonDirectory, true);

    d_arg.option(&d_targetDirectory, "target-directory");

    if (not d_targetDirectory.empty())
        cleanDir(d_targetDirectory, true);
}
