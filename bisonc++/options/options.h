#ifndef INCLUDED_OPTIONS_
#define INCLUDED_OPTIONS_

#include <string>
#include <bobcat/a2x>

class Options
{
    std::string const *d_matched;

    std::string d_fileName;                 // the name of the current file
    size_t d_lineNr;                        // the current line nr.

    std::string d_baseClassHeaderPath;
    std::string d_baseClassSkeleton;
    std::string d_classHeaderPath;
    std::string d_className;
    std::string d_classSkeleton;
    std::string d_field;                    // %union field in <type> specs.
    std::string d_genericFilename;
    std::string d_implementationHeaderPath;
    std::string d_implementationSkeleton;
    std::string d_locationDecl;
    std::string d_matchedTextFunction;
    std::string d_nameSpace;
    std::string d_parsefunSkeleton;
    std::string d_parsefunSource;
    std::string d_preInclude;
    std::string d_printFunction;            // set by --print or %print
    std::string d_scannerInclude;
    std::string d_scannerTokenFunction;
    std::string d_skeletonDirectory;
    std::string d_stackDecl;
    std::string d_targetDirectory;
    std::string d_verboseName;

    bool        d_debug;
    bool        d_errorVerbose;
    bool        d_flexcpp;
    bool        d_generateBaseclass;
    bool        d_lines;
    bool        d_lspNeeded;
    bool        d_negativeDollarIndices;
    bool        d_typeDirective;            // true following %type
    bool        d_unionDeclared;            // see setuniondecl.cc

    size_t      d_requiredTokens;

    static char s_defaultBaseclassSkeleton[];
    static char s_defaultClassName[];
    static char s_defaultClassSkeleton[];
    static char s_defaultImplementationSkeleton[];
    static char s_defaultParsefunSkeleton[];
    static char s_defaultParsefunSource[];
    static char s_defaultSkeletonDirectory[];

    static Options s_options;

    public:
        static Options &instance();

        Options(Options const &other) = delete;

        void setMatched(std::string const &matched);

        void setAccessorVariables();
        void setBaseClassHeaderPath();
        void setClassHeaderPath();
        void setClassName();
        void setDebug();
        void setExpectedConflicts();
        void setGenericFilename();
        void setImplementationHeader();
        void setImplementationHeaderPath();
        void setLines();
        void setLines(bool yesNo);
        void setLocationDecl(std::string const &block);
        void setLspNeeded();
        void setLtype();

        void setName(std::string *target, char const *extension);

        void setNameSpace();
        void setNegativeDollarIndices();
        void setParsefunSource(int type);
        void setPreInclude();
        void setPrecedence(int type);
        void setPrint();
        void setRequiredTokens();
        void setScannerInclude();
        void setScannerTokenFunction();
        void setScannerMatchedTextFunction();
        void setStype();
        void setTargetDirectory(std::string const &name);
        void setUnionDecl(std::string const &block);
        void setUnionDecl();
        void setVerbosity();            // Prepare Msg for verbose output

        void finalizeAccessorVariables();

        void showFilenames() const;


        bool debug() const;
        bool errorVerbose() const;
        bool lines() const;
        bool lspNeeded() const;

        size_t requiredTokens() const;

        std::string const &baseclassSkeleton() const;
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

    private:
        Options();

        void delimit(std::string *target, char const *declTxt);
        std::string undelimit();
        void assign(std::string *target, char const *declTxt);

//        void setPath(std::string *dest, int optChar, bool targetDirOption, 
//                      char const *optionName, std::string const &className, 
//                      char const *suffix);
};

inline void Options::setBaseClassHeaderPath()
{
    assign(&d_baseClassHeaderPath, "baseclass-header");
}

inline void Options::setClassHeaderPath()
{
    assign(&d_classHeaderPath, "class-header");
}

inline void Options::setClassName()
{
    assign(&d_className, "class-name");
}

inline void Option::seGenericFilename()
{
    assign(&d_genericFilename, "filenames");
}

inline void Options::setFlexcpp()
{
    d_flexcpp = true;
}

inline void Option::setImplementationHeaderPath()
{
    assign(&d_implementationHeaderPath, "implementation-header");
}

inline void Option::setLines()
{
    d_lines = true;
}

inline void Options::setLspNeeded()
{
    d_lspNeeded = true;
}

inline void Options::setNameSpace(string const &name)
{
    assign(&d_nameSpace, name, "namespace");
}

inline void Options::setNegativeDollarIndices()
{
    d_negativeDollarIndices = true;
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
    delimit(&d_preInclude, "baseclass-preinclude");
}

inline void Options::setRequiredTokens()
{
    d_requiredTokens = FBB::A2x(spec);
}

inline void Options::setScannerInclude()
{
    delimit(&d_scannerInclude, "scanner");
}

inline void Options::setScannerTokenFunction()
{
    assign(&d_scannerTokenFunction, "scanner-token-function");
}

inline void Options::setScannerMatchedTextFunction()
{
    assign(&d_scannerMatchedTextFunction, "scanner-matched-text-function");
}

inline void Options::setScannerMatchedTextFunction()
{
    assign(&d_scannerMatchedTextFunction, "scanner-matched-text-function");
}

inline std::string const &Options::baseclassSkeleton() const
{
    return d_baseclassSkeleton;
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

inline bool Options::lspNeeded() const
{
    return d_lspNeeded;
}

inline std::string const &Options::ltype() const
{
    return d_locationDecl;
}

inline std::string const &Options::matchedTextFunction() const
{
    return d_matchedTextFunction;
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

inline void Options::setScannerInclude()
{
    validateInclude(&d_scannerInclude);
}

inline void Options::setScannerTokenFunction()
{
    definePathname(&d_scannerTokenFunction, 0);
}

inline std::string const &Options::stype() const
{
    return d_stackDecl;
}

#endif





