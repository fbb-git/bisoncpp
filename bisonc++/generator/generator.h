#ifndef _INCLUDED_GENERATOR_
#define _INCLUDED_GENERATOR_

#include <vector>
#include <unordered_map>
#include <string>
#include <iosfwd>

#include <bobcat/arg>
#include <bobcat/stat>

#include "../writer/writer.h"

class Terminal;
class Rules;
class Options;

class Generator
{
    typedef void (Generator::*Inserter)(std::ostream &) const;
    typedef std::unordered_map<std::string, Inserter>     Map;

    typedef Map::value_type                     MapValue;
    typedef Map::const_iterator                 MapConstIter;

    FBB::Arg   &d_arg;

    mutable FBB::Stat   d_stat;

    Rules const &d_rules;
    Options &d_options;

    std::string d_baseClassScope;
    std::string const &d_nameSpace;
    std::string const &d_matchedTextFunction;
    std::string const &d_tokenFunction;
    std::string d_nameSpacedClassname;

    mutable std::string d_key;          // extracted at $insert statements
    mutable size_t d_indent;

    mutable std::string d_line;
    bool d_genDebug;
    bool d_printTokens;
    bool d_threadSafe;

    std::unordered_map<std::string, std::string> const &d_polymorphic; 

    mutable Writer d_writer;                // maintains its own const-ness

    static Map s_insert;
    static char const *s_atFlag;            // \@ flag in skeletons

    struct At;
    typedef std::vector<At> AtVector;

    struct AtBool;
    typedef std::vector<AtBool> AtBoolVector;

    static AtBoolVector s_atBol;     // no typo: Bol = Begin of line
    static AtVector s_at;

    public:
        Generator(Rules const &rules, 
             std::unordered_map<std::string, std::string> const &polymorphic); 

        bool conflicts() const;
        void baseClassHeader() const;
        void classHeader() const;
        void implementationHeader() const;
        void parseFunction() const;

    private:
        static std::string filename(std::string const &path);

        void filter(std::istream &in, std::ostream &out, 
                                        bool header = true) const;

        void insert(std::ostream &out) const;
        void key(std::ostream &out) const;          // show which $insert is
                                                    // called, just before the
                                                    // generated code 

        bool errExisting(std::string const &fileName, 
                         std::string const &option,
                         std::string const &regex) const;
        bool grep(std::string const &fileName, std::string const &regex) 
                                                                        const;


        void actionCases(std::ostream &out) const;
        void baseClass(std::ostream &out) const;
        void classH(std::ostream &out) const;
        void classIH(std::ostream &out) const;
        void debug(std::ostream &out) const;
        void debugIncludes(std::ostream &out) const;
        void debugFunctions(std::ostream &out) const;
        void debugDecl(std::ostream &out) const;
        void debugLookup(std::ostream &out) const;
        void defaultActionReturn(std::ostream &out) const;
        void errorVerbose(std::ostream &out) const;
        void executeActionCases(std::ostream &out) const;
        void idOfTag(std::ostream &out) const;
        void lex(std::ostream &out) const;
        void ltype(std::ostream &out) const;
        void ltypeData(std::ostream &out) const;
        void ltypeClear(std::ostream &out) const;
        void ltypePop(std::ostream &out) const;
        void ltypePush(std::ostream &out) const;
        void ltypeResize(std::ostream &out) const;
        void ltypeStack(std::ostream &out) const;
        void namespaceClose(std::ostream &out) const;
        void namespaceOpen(std::ostream &out) const;
        void namespaceUse(std::ostream &out) const;
        void polymorphic(std::ostream &out) const;
        void polyIncludes(std::ostream &out) const;
        void polymorphicCode(std::ostream &out) const;
        void polymorphicSpecializations(std::ostream &out) const;
        void preIncludes(std::ostream &out) const;
        void print(std::ostream &out) const;
        void prompt(std::ostream &out) const;
        void baseClassCode(std::ostream &out) const;

        void scannerH(std::ostream &out) const;
        void scannerObject(std::ostream &out) const;
        void staticData(std::ostream &out) const;
        void stype(std::ostream &out) const;
        void tokens(std::ostream &out) const;
        void warnTagMismatches(std::ostream &out) const;

        void ifInsertStype(bool &accept) const;
        void ifPrintTokens(bool &accept) const;
        void ifLtype(bool &accept) const;
        void atElse(bool &accept) const;
        void atEnd(bool &accept) const;

        std::string const &atTokenFunction() const;
        std::string const &atMatchedTextFunction() const;
        std::string const &atLtype() const;
        std::string const &atNameSpacedClassname() const;
        std::string const &atClassname() const;

        void replaceBaseFlag(std::string &line) const;
        void replaceAtKey(std::string &line, size_t pos) const;

        static void selectSymbolic(Terminal const *terminal, 
                                   Terminal::ConstVector &symbolicTokens);
        static void replace(std::string &str, char ch, 
                       std::string const &replacement);
        void insert(std::ostream &out, size_t indent, char const *skel) const;
        void bolAt(std::ostream &out, std::string &line, std::istream &in,
                                                        bool &accept) const;

        template <typename AtType> 
        typename std::vector<AtType>::const_iterator find(
            std::string const &line, 
            size_t pos, 
            std::vector<AtType> const &atVector
        ) const;
};

#endif
