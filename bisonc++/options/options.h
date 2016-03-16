#ifndef INCLUDED_OPTIONS_
#define INCLUDED_OPTIONS_

#include <string>
#include <set>

namespace FBB
{
    class Arg;
}

struct Options
{
    enum TriVal
    {
        UNKNOWN,
        OFF,
        ON
    };

    struct OptInfo
    {
        TriVal      triVal;
        std::string filename;
        size_t      lineNr;
    };

    private:
        enum PathType
        {
            FILENAME,
            PATHNAME
        };

        FBB::Arg &d_arg;
    
        std::string const *d_matched;
    
//        std::string d_fileName;             // the name of the current file
//        size_t d_lineNr;                    // the current line nr.
    
        OptInfo d_constructorChecks{UNKNOWN, "", 0};
        OptInfo d_warnTagMismatches{OFF, "", 0};

        bool        d_debug             = false;
        bool        d_defaultActions    = true;
        bool        d_errorVerbose      = false;
        bool        d_flex              = false;
        bool        d_lines             = true;
        bool        d_lspNeeded         = false;
        bool        d_polymorphic       = false;
        bool        d_printTokens       = false;
        bool        d_strongTags        = true;
    
        size_t      d_requiredTokens = 0;

        std::set<std::string> d_warnOptions;// contains the names of options 
                                            // for which Generator may warn
                                            // if specified for already
                                            // existing .h or .ih files

        std::string d_baseClassHeader;
        std::string d_baseClassSkeleton;
        std::string d_polymorphicCodeSkeleton;
        std::string d_polymorphicInline;
        std::string d_polymorphicSkeleton;
        std::string d_classHeader;
        std::string d_className;
        std::string d_classSkeleton;
        std::string d_genericFilename;
        std::string d_implementationHeader;
        std::string d_implementationSkeleton;
        std::string d_locationDecl;
        std::string d_nameSpace;
        std::string d_parsefunSkeleton;
        std::string d_parsefunSource;
        std::string d_preInclude;
        std::string d_scannerInclude;
        std::string d_scannerMatchedTextFunction;
        std::string d_scannerTokenFunction;
        std::string d_scannerClassName;
        std::string d_skeletonDirectory;
        std::string d_stackDecl;
        std::string d_targetDirectory;
        std::string d_verboseName;
    
        static char s_defaultBaseClassSkeleton[];
        static char s_defaultPolymorphicCodeSkeleton[];
        static char s_defaultPolymorphicSkeleton[];
        static char s_defaultClassName[];
        static char s_defaultClassSkeleton[];
        static char s_defaultImplementationSkeleton[];
        static char s_defaultParsefunSkeleton[];
        static char s_defaultParsefunSource[];
        static char s_defaultSkeletonDirectory[];
        static char s_defaultTargetDirectory[];
        static char s_defaultScannerClassName[];
        static char s_defaultScannerMatchedTextFunction[];
        static char s_defaultScannerTokenFunction[];
        static char s_YYText[];
        static char s_yylex[];
    
        static Options *s_options;

    public:
        static Options &instance();

        Options(Options const &other) = delete;

        void setMatched(std::string const &matched);

        void setAccessorVariables();

        bool specified(std::string const &option) const;

        void setBaseClassHeader();
        void setClassHeader();
        void setClassName();
        void setDebug();
        void setErrorVerbose();
        void setFlex();
        void setGenericFilename();
        void setImplementationHeader();
        void setLocationDecl(std::string const &block);
        void setLspNeeded();
        void setLtype();
        void setNamespace();
        void setParsefunSource();
        void setPolymorphicDecl();
        void setPreInclude();
        void setPrintTokens();
        void setRequiredTokens(size_t nRequiredTokens);
        void setScannerClassName();
        void setScannerInclude();
        void setScannerMatchedTextFunction();
        void setScannerTokenFunction();
        void setStype();
        void setTargetDirectory();
        void setUnionDecl(std::string const &block);
        void setVerbosity();            // Prepare Msg for verbose output
        void setWarnTagMismatches(TriVal value, std::string const &filename,
                                  size_t lineNr);
        void setConstructorChecks(TriVal value, std::string const &filename,
                                  size_t lineNr);

        void unsetDefaultActions();
        void unsetLines();
        void unsetStrongTags();

        void showFilenames() const;


        bool printTokens() const;
        bool debug() const;
        bool defaultActions() const;
        bool errorVerbose() const;
        bool lines() const;
        bool lspNeeded() const;
        bool polymorphic() const;
        bool strongTags() const;

        OptInfo const &warnTagMismatches() const;
        OptInfo const &constructorChecks() const;  

        size_t requiredTokens() const;

        std::string const &baseClassSkeleton() const;
        std::string const &baseClassHeader() const;
        std::string baseclassHeaderName() const;
        std::string const &classHeader() const;
        std::string const &className() const;
        std::string const &classSkeleton() const;
        std::string const &implementationHeader() const;
        std::string const &implementationSkeleton() const;
        std::string const &ltype() const;
        std::string const &nameSpace() const;
        std::string const &parseSkeleton() const;
        std::string const &parseSource() const;
        std::string const &preInclude() const;
        std::string const &polymorphicCodeSkeleton() const;
        std::string const &polymorphicSkeleton() const;
        std::string const &scannerClassName() const;
        std::string const &scannerInclude() const;
        std::string const &scannerMatchedTextFunction() const;
        std::string const &scannerTokenFunction() const;
        std::string const &skeletonDirectory() const;
        std::string const &stype() const;

        static std::string undelimit(std::string const &str);

    private:
        Options();

            // called by setAccessorVariables()
        void setBooleans();
        void setBasicStrings();
        void setOpt(std::string *destVar, char const *opt, 
                    std::string const &defaultSpec);

        void setQuotedStrings();
        void setPathStrings();  // called by setAccessorVariables,
                                // called by parser.cleanup(). 
                                // inspected Option values
                                // may NOT have directory separators.
        void setSkeletons();
        
                             // undelimit and if append append / if missing
        void cleanDir(std::string &dir, bool append); 
        void addIncludeQuotes(std::string &target);

        std::string const &accept(PathType pathType, char const *declTxt);
        void assign(std::string *target, PathType pathType, 
                    char const *declTxt);

        void setPath(std::string *dest, int optChar, 
                      std::string const &defaultFilename, 
                      char const *defaultSuffix,
                      char const *optionName);

        bool isFirstStypeDefinition() const;
};

inline bool Options::debug() const
{
    return d_debug;
}

inline bool Options::defaultActions() const
{
    return d_defaultActions;
}

inline Options::OptInfo const &Options::warnTagMismatches() const
{
    return d_warnTagMismatches;
}

inline Options::OptInfo const &Options::constructorChecks() const
{
    return d_constructorChecks;
}

inline std::string const &Options::baseClassHeader() const
{
    return d_baseClassHeader;
}

inline std::string const &Options::skeletonDirectory() const
{
    return d_skeletonDirectory;
}

inline std::string const &Options::baseClassSkeleton() const
{
    return d_baseClassSkeleton;
}

inline std::string const &Options::classHeader() const
{
    return d_classHeader;
}

inline std::string const &Options::className() const
{
    return d_className;
}

inline std::string const &Options::classSkeleton() const
{
    return d_classSkeleton;
}

inline bool Options::errorVerbose() const
{
    return d_errorVerbose;
}

inline std::string const &Options::implementationHeader() const
{
    return d_implementationHeader;
}

inline std::string const &Options::implementationSkeleton() const
{
    return d_implementationSkeleton;
}

inline bool Options::lines() const
{
    return d_lines;
}

inline bool Options::lspNeeded() const
{
    return d_lspNeeded;
}

inline bool Options::polymorphic() const
{
    return d_polymorphic;
}

inline std::string const &Options::ltype() const
{
    return d_locationDecl;
}

inline std::string const &Options::nameSpace() const
{
    return d_nameSpace;
}

inline std::string const &Options::parseSkeleton() const
{
    return d_parsefunSkeleton;
}

inline std::string const &Options::parseSource() const
{
    return d_parsefunSource;
}

inline std::string const &Options::polymorphicCodeSkeleton() const
{
    return d_polymorphicCodeSkeleton;
}

inline std::string const &Options::polymorphicSkeleton() const
{
    return d_polymorphicSkeleton;
}

inline std::string const &Options::preInclude() const
{
    return d_preInclude;
}

inline bool Options::printTokens() const
{
    return d_printTokens;
}

inline size_t Options::requiredTokens() const
{
    return d_requiredTokens;
}

inline std::string const &Options::scannerClassName() const
{
    return d_scannerClassName;
}

inline std::string const &Options::scannerInclude() const
{
    return d_scannerInclude;
}

inline std::string const &Options::scannerMatchedTextFunction() const
{
    return d_scannerMatchedTextFunction;
}

inline std::string const &Options::scannerTokenFunction() const
{
    return d_scannerTokenFunction;
}

inline void Options::setBaseClassHeader()
{
    assign(&d_baseClassHeader, FILENAME, "baseclass-header");
}

inline void Options::setClassHeader()
{
    assign(&d_classHeader, FILENAME, "class-header");
}

inline void Options::setClassName()
{
    assign(&d_className, FILENAME, "class-name");
}

inline void Options::setErrorVerbose()
{
    d_errorVerbose = true;
}

inline void Options::setDebug()
{
    d_debug = true;
}

inline void Options::setGenericFilename()
{
    assign(&d_genericFilename, FILENAME, "filenames");
}

inline void Options::setFlex()
{
    d_flex = true;
}

inline void Options::setImplementationHeader()
{
    assign(&d_implementationHeader, FILENAME, "implementation-header");
}

inline void Options::unsetLines()
{
    d_lines = false;
}

inline void Options::unsetDefaultActions()
{
    d_defaultActions = false;
}

inline void Options::setLspNeeded()
{
    d_lspNeeded = true;
}

inline void Options::setMatched(std::string const &matched)
{
    d_matched = &matched;
}

inline void Options::setNamespace()
{
    assign(&d_nameSpace, FILENAME, "namespace");
}

inline void Options::setParsefunSource()
{
    assign(&d_parsefunSource, FILENAME, "parsefun-source");
}

inline void Options::setPreInclude()
{
    assign(&d_preInclude, PATHNAME, "baseclass-preinclude");
}

inline void Options::setScannerClassName()
{
    assign(&d_scannerClassName, FILENAME, "scanner-class-name");
}

inline void Options::setScannerInclude()
{
    assign(&d_scannerInclude, PATHNAME, "scanner");
}

inline void Options::setScannerMatchedTextFunction()
{
    assign(&d_scannerMatchedTextFunction, 
                                FILENAME, "scanner-matched-text-function");
}

inline void Options::setScannerTokenFunction()
{
    assign(&d_scannerTokenFunction, FILENAME, "scanner-token-function");
}

inline void Options::setTargetDirectory()
{
    assign(&d_targetDirectory, PATHNAME, "target-directory");
}

inline std::string const &Options::stype() const
{
    return d_stackDecl;
}

inline bool Options::strongTags() const
{
    return d_strongTags;
}

inline void Options::setConstructorChecks(TriVal value, 
                                          std::string const &filename,
                                          size_t lineNr)
{
    d_constructorChecks = OptInfo{value, filename, lineNr};
}

inline void Options::setWarnTagMismatches(TriVal value,
                                          std::string const &filename,
                                          size_t lineNr)
{
    d_warnTagMismatches = OptInfo{value, filename, lineNr};
}

inline void Options::unsetStrongTags()
{
    d_strongTags = false;
}

inline bool Options::specified(std::string const &option) const
{
    return d_warnOptions.find(option) != d_warnOptions.end();
}

#endif
