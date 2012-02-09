/*
                              bisonc++.cc
*/

#include "bisonc++.h"

using namespace std;
using namespace FBB;

namespace 
{
    Arg::LongOption longOptions[] = 
    {
        {"analyze-only", 'A'},

        {"baseclass-preinclude", 'H'},
        {"baseclass-skeleton", 'B'},
        {"class-skeleton", 'C'},
        {"implementation-skeleton", 'I'},
        {"parsefun-skeleton", 'P'},
        {"skeleton-directory", 'S'},

        {"baseclass-header", 'b'},
        {"class-header", 'c'},
        {"implementation-header", 'i'},
        {"parsefun-source", 'p'},

        {"class-name", Arg::Required},

        Arg::LongOption("construction"),
                // implies verbose, but also shows FIRST and FOLLOW sets as
                // well as the full set of states, including the non-kernel
                // items

        Arg::LongOption("debug"),
        Arg::LongOption("error-verbose"),

        {"filenames", 'f'},

        Arg::LongOption("force-implementation-header"),
        Arg::LongOption("force-class-header"),
        Arg::LongOption("insert-stype"),

        {"help", 'h'},

        Arg::LongOption("include-only"),

        {"max-inclusion-depth", Arg::Required},
        {"namespace", 'n'},

        Arg::LongOption("no-baseclass-header"),
        Arg::LongOption("no-parse-member"),

        {"lines", 'l'},

        Arg::LongOption("no-lines"),

        {"print", Arg::Required},
        {"required-tokens", Arg::Required},

        {"scanner", 's'},
        {"scanner-function-name", 't'},
        {"flexc++", 'F'},

        Arg::LongOption("scanner-debug"),

        {"scanner-token-function", Arg::Required},

        Arg::LongOption("show-filenames"),
                // writes the names of the files to the standard output

        Arg::LongOption("thread-safe"),
                // no static data are modified, making bisonc++ thread-safe

        {"usage", 'h'},
        {"version", 'v'},
        {"verbose", 'V'},
                // shows rules, tkoens, final states and kernel items, 
                // and describes conflicts when found
    };
    auto longEnd = longOptions + 
                               sizeof(longOptions) / sizeof(Arg::LongOption);  
}

int main(int argc, char **argv)
try
{
    Arg &arg = Arg::initialize("AB:b:C:c:f:H:hI:i:ln:p:P:s:S:t:Vv", 
                    longOptions, longEnd, argc, argv);

    arg.versionHelp(usage, version, 1);

    Rules rules;

    Parser parser(rules);   // Prepare parsing. If `include-only' was
                            // specified, processing stops here.


    parser.parse();        // parses the input, fills the data in the Rules
                            // read the grammar file, build required data
                            // structures. 

    parser.cleanup();       // do cleanup actions following parse() 
                            // (terminate if parsing produced errors)

    rules.updatePrecedences();  // update production rule precedences


    rules.showRules();
    rules.showTerminals();

    rules.determineFirst();
    rules.showFirst();

    rules.determineFollow();
    rules.showFollow();

                            // define the startproduction
    Production::setStart(rules.startProduction());

    State::define();        // define all states

    rules.assignNonTerminalNumbers();

    rules.showUnusedTerminals();
    rules.showUnusedNonTerminals();
    rules.showUnusedRules();

    State::allStates();

    Grammar grammar;
    grammar.deriveSentence();

    if (Msg::errors())
        return 1;

    if (arg.option('A'))    // Analyze only
        return 0;

    Generator generator(rules, parser);

    generator.baseclassHeader();
    generator.classHeader();
    generator.implementationHeader();

    generator.parseFunction();
}
catch(Errno const &err)
{
    cerr << err.why() << '\n';
    return err.which();
}
catch(int x)
{
    return x;
}
