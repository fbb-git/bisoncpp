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
        {"analyze-only", 'A'},              // option only

        {"baseclass-header", 'b'},
        {"baseclass-preinclude", 'H'},

        {"baseclass-skeleton", 'B'},        // option only

        {"class-header", 'c'},
        {"class-name", Arg::Required},

        {"class-skeleton", 'C'},            // option only

        Arg::LongOption("construction"),    // option only
                // implies verbose, but also shows FIRST and FOLLOW sets as
                // well as the full set of states, including the non-kernel
                // items

        Arg::LongOption("debug"),
        Arg::LongOption("error-verbose"),
        {"filenames", 'f'},
        Arg::LongOption("flex"),
                                            // options only
        Arg::LongOption("force-class-header"),
        Arg::LongOption("force-implementation-header"),

        {"help", 'h'},                      // option only

        {"implementation-header", 'i'},

        {"implementation-skeleton", 'I'},   // option only
        Arg::LongOption("insert-stype"),    // option only

        {"max-inclusion-depth", Arg::Required}, // option only

        {"namespace", 'n'},

                                            // option only
        Arg::LongOption("no-baseclass-header"),

        Arg::LongOption("no-lines"),

        Arg::LongOption("no-parse-member"), // options only
        {"own-debug", Arg::None},
        {"own-tokens", 'T'},
        {"parsefun-skeleton", 'P'},         

        {"parsefun-source", 'p'},
        {"print-tokens", 't'},

        {"required-tokens", Arg::Required},

        {"scanner", 's'},
        Arg::LongOption("scanner-debug"),
        {"scanner-matched-text-function", Arg::Required},
        {"scanner-token-function", Arg::Required},

        Arg::LongOption("show-filenames"),  // option only
        {"skeleton-directory", 'S'},        // option only

        {"target-directory", Arg::Required},

        Arg::LongOption("thread-safe"),     // options only
        {"usage", 'h'},                     
        {"verbose", 'V'},
                // shows rules, tkoens, final states and kernel items, 
                // and describes conflicts when found
        {"version", 'v'},
    };
    auto longEnd = longOptions + 
                               sizeof(longOptions) / sizeof(Arg::LongOption);  
}

int main(int argc, char **argv)
try
{
    Arg &arg = Arg::initialize("AB:b:C:c:f:H:hI:i:n:p:P:s:S:tTVv", 
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

    Generator generator(rules, parser.polymorphic());

    generator.baseClassHeader();
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
