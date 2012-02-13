#ifndef INCLUDED_OPTIONS_
#define INCLUDED_OPTIONS_

#include <string>
#include <bobcat/a2x>

namespace FBB
{
    class Arg;
}

class Options
{
    FBB::Arg &d_arg;

    std::string const *d_matched;

    std::string d_fileName;                 // the name of the current file
    size_t d_lineNr;                        // the current line nr.

    bool        d_debug;
    bool        d_errorVerbose;
    bool        d_flexcpp;
    bool        d_lines;

    size_t      d_requiredTokens;

    std::string d_baseClassHeader;
    std::string d_baseClassSkeleton;
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
    std::string d_printFunction;            // set by --print or %print
    std::string d_scannerInclude;
    std::string d_scannerMatchedTextFunction;
    std::string d_scannerTokenFunction;
    std::string d_skeletonDirectory;
    std::string d_stackDecl;
    std::string d_targetDirectory;
    std::string d_verboseName;


	static char s_defaultClassName[];
	static char s_defaultParsefunSource[];
	static char s_defaultTargetDirectory[];
    static char s_defaultBaseClassSkeleton[];
    static char s_defaultClassName[];
    static char s_defaultClassSkeleton[];
    static char s_defaultImplementationSkeleton[];
    static char s_defaultParsefunSkeleton[];
    static char s_defaultParsefunSource[];
    static char s_defaultSkeletonDirectory[];

// std::string Options::classHeaderName() const
// {
//     size_t pos = d_classHeaderPath.rfind('/');
// 
//     return pos == string::npos ? 
//                         d_classHeaderPath 
//                     :
//                         d_classHeaderPath.substr(pos + 1);
// }

    static Options s_options;

    public:
        static Options &instance();

        Options(Options const &other) = delete;

        void setMatched(std::string const &matched);

        void setAccessorVariables();
        void setBaseClassHeader();
        void setClassHeader();
        void setClassName();
        void setDebug();
        void setErrorVerbose();
        void setFlexcpp();
        void setGenericFilename();
        void setImplementationHeader();
        void setLines();
        void setLines(bool yesNo);
        void setLocationDecl(std::string const &block);
        void setLtype();
        void setNamespace();
        void setParsefunSource();
        void setPreInclude();
        void setPrint();
        void setRequiredTokens();
        void setScannerInclude();
        void setScannerTokenFunction();
        void setScannerMatchedTextFunction();
        void setSkeletonDirectory();
        void setStype();
        void setTargetDirectory();
        void setUnionDecl(std::string const &block);
        void setVerbosity();            // Prepare Msg for verbose output

        void finalizeAccessorVariables();

        void showFilenames() const;


        bool debug() const;
        bool errorVerbose() const;
        bool lines() const;

        size_t requiredTokens() const;

        std::string const &baseClassSkeleton() const;
        std::string const &baseClassHeader() const;
        std::string const &classHeader() const;
        std::string const &className() const;
        std::string const &classSkeleton() const;
        std::string const &implementationHeader() const;
        std::string const &implementationSkeleton() const;
        std::string const &ltype() const;
        std::string const &matchedTextFunction() const;
        std::string const &nameSpace() const;
        std::string const &parseSkeleton() const;
        std::string const &parseSource() const;
        std::string const &preInclude() const;
        std::string const &scannerInclude() const;
        std::string const &scannerTokenFunction() const;
        std::string const &stype() const;

        static std::string undelimit(std::string const &str);

    private:
        Options();

        void cleanDir(string &dir);     // undelimit and append / if missing
        void addIncludeQuotes(string &target);

        void assign(std::string *target, char const *declTxt);

        void setPath(std::string *dest, int optChar, bool targetDirOption, 
                      char const *optionName, std::string const &className, 
                      char const *suffix);
};

inline void Options::setBaseClassHeader()
{
    assign(&d_baseClassHeader, "baseclass-header");
}

inline void Options::setClassHeader()
{
    assign(&d_classHeader, "class-header");
}

inline void Options::setClassName()
{
    assign(&d_className, "class-name");
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
    assign(&d_genericFilename, "filenames");
}

inline void Options::setFlexcpp()
{
    d_flexcpp = true;
}

inline void Options::setImplementationHeader()
{
    assign(&d_implementationHeader, "implementation-header");
}

inline void Options::setLines()
{
    d_lines = true;
}

inline void Options::setNamespace()
{
    assign(&d_nameSpace, "namespace");
}

inline void Options::setParsefunSource()
{
    assign(&d_parsefunSource, "parsefun-source");
}

inline void Options::setPrint()
{
    assign(&d_printFunction, "print");
}

inline void Options::setPreInclude()
{
    assign(&d_preInclude, "baseclass-preinclude");
}

inline void Options::setScannerInclude()
{
    assign(&d_scannerInclude, "scanner");
}

inline void Options::setScannerTokenFunction()
{
    assign(&d_scannerTokenFunction, "scanner-token-function");
}

inline void Options::setScannerMatchedTextFunction()
{
    assign(&d_scannerMatchedTextFunction, "scanner-matched-text-function");
}

inline void Options::setSkeletonDirectory()
{
    assign(&d_skeletonDirectory, "skeleton-directory (-S)");
}


inline void Options::setTargetDirectory()
{
    assign(&d_targetDirectory, "target-directory");
}

inline std::string const &Options::baseClassHeader() const
{
    return d_baseClassHeader;
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

inline std::string const &Options::ltype() const
{
    return d_locationDecl;
}

inline std::string const &Options::matchedTextFunction() const
{
    return d_scannerMatchedTextFunction;
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

inline std::string const &Options::scannerInclude() const
{
    return d_scannerInclude;
}

inline std::string const &Options::scannerTokenFunction() const
{
    return d_scannerTokenFunction;
}

inline size_t Options::requiredTokens() const
{
    return d_requiredTokens;
}

inline std::string const &Options::stype() const
{
    return d_stackDecl;
}

#endif





