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
        Arg::LongOption("analyze-only", 'A'),

        Arg::LongOption("baseclass-preinclude", 'H'),
        Arg::LongOption("baseclass-skeleton", 'B'),
        Arg::LongOption("class-skeleton", 'C'),
        Arg::LongOption("implementation-skeleton", 'I'),
        Arg::LongOption("parsefun-skeleton", 'P'),
        Arg::LongOption("skeleton-directory", 'S'),

        Arg::LongOption("baseclass-header", 'b'),
        Arg::LongOption("class-header", 'c'),
        Arg::LongOption("implementation-header", 'i'),
        Arg::LongOption("parsefun-source", 'p'),

        Arg::LongOption("class-name", Arg::Required),

        Arg::LongOption("construction"),
                // implies verbose, but also shows FIRST and FOLLOW sets as
                // well as the full set of states, including the non-kernel
                // items

        Arg::LongOption("debug"),

        Arg::LongOption("error-verbose"),

        Arg::LongOption("filenames", 'f'),

        Arg::LongOption("force-implementation-header"),
        Arg::LongOption("force-class-header"),

        Arg::LongOption("insert-stype"),

        Arg::LongOption("help", 'h'),
        Arg::LongOption("include-only"),
        Arg::LongOption("max-inclusion-depth", Arg::Required),

        Arg::LongOption("namespace", 'n'),

        Arg::LongOption("no-baseclass-header"),
        Arg::LongOption("no-parse-member"),

        Arg::LongOption("lines", 'l'),
        Arg::LongOption("no-lines"),

        Arg::LongOption("required-tokens", Arg::Required),

        Arg::LongOption("scanner", 's'),
        Arg::LongOption("scanner-debug"),

        Arg::LongOption("show-filenames"),
                // writes the names of the files to the standard output

        Arg::LongOption("thread-safe"),
                // no static data are modified, making bisonc++ thread-safe

        Arg::LongOption("usage", 'h'),
        Arg::LongOption("version", 'v'),
        Arg::LongOption("verbose", 'V'),
                // shows rules, tkoens, final states and kernel items, 
                // and describes conflicts when found
    };

    Arg::LongOption const *const longEnd = longOptions + 
                                sizeof(longOptions) / sizeof(Arg::LongOption); 
}

int main(int argc, char **argv)
try
{
    Arg &arg = Arg::initialize("AB:b:C:c:f:H:hI:i:ln:p:P:s:S:Vv", 
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

    return 0;
}
catch(Errno const &err)
{
    cerr << err.what() << endl;
    return err.which();
}
catch(int x)
{
    return x;
}
