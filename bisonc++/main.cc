/*
                              bisonc++.cc
*/

#include "main.ih"

using namespace std;
using namespace FBB;

namespace 
{
    Arg::LongOption longOptions[] = 
    {
        {"analyze-only", 'A'},
                                                            
        {"baseclass-header", 'b'},                          // also directive
        {"baseclass-preinclude", 'H'},                      // also directive
        {"baseclass-skeleton", 'B'},
                                                            
        {"class-header", 'c'},                              // also directive
        {"class-name", Arg::Required},                      // also directive
        {"class-skeleton", 'C'},
        Arg::LongOption{"construction"},
            // implies verbose, but also shows              
            // FIRST and FOLLOW sets as well as             
            // the full set of states, including             
            // the non-kernel items                         

//        {"constructor-checks", Arg::Required},              // also directive
                                                            
        Arg::LongOption{"debug"},                           // also directive
        {"default-actions", 'd'},                           // also directive

        Arg::LongOption{"error-verbose"},                   // also directive
                                                            
        {"filenames", 'f'},                                 // also directive
        Arg::LongOption{"flex"},                            // also directive
                                                            
        {"help", 'h'},
                                                            
        {"implementation-header", 'i'},                     // also directive
        {"implementation-skeleton", 'I'},
        Arg::LongOption{"insert-stype"},
                                                            
        {"max-inclusion-depth", Arg::Required},
                                                            
        {"namespace", 'n'},                                 // also directive
        Arg::LongOption{"no-baseclass-header"},
        {"no-decoration", 'D'},
        Arg::LongOption{"no-lines"},                        // also directive
        Arg::LongOption{"no-parse-member"},
                                                            
        {"own-debug", Arg::None},
        {"own-tokens", 'T'},

        {"parsefun-skeleton", 'P'},
        {"parsefun-source", 'p'},                           // also directive
        {"polymorphic-code-skeleton", 'L'},
        {"polymorphic-skeleton", 'M'},
        {"print-tokens", 't'},                              // also directive
                                                            
        {"required-tokens", Arg::Required},                 // also directive
                                                            
        {"scanner", 's'},                                   // also directive
        {"scanner-class-name", Arg::Required},              // also directive
        Arg::LongOption{"scanner-debug"},
        {"scanner-matched-text-function", Arg::Required},   // also directive
        {"scanner-token-function", Arg::Required},          // also directive
        Arg::LongOption{"show-filenames"},
        {"skeleton-directory", 'S'},

        {"tag-mismatches", Arg::Required},                  // also directive
        {"target-directory", Arg::Required},                // also directive
        Arg::LongOption{"thread-safe"},

        {"usage", 'h'},                                     

        {"verbose", 'V'},
            // shows rules, tokens, final states and kernel
            // items, and describes conflicts when found
        {"version", 'v'},

    };
    auto longEnd = longOptions + 
                               sizeof(longOptions) / sizeof(Arg::LongOption);  
}

int main(int argc, char **argv)
try
{
    Arg &arg = Arg::initialize("AB:b:C:c:d:Df:H:hI:i:L:M:n:p:P:s:S:tTVv", 
                    longOptions, longEnd, argc, argv);

    arg.versionHelp(usage, version, 1);

    Rules rules;

    Parser parser(rules);

//    parser.setDebug(Parser::ON__);
//    parser.setDebug(Parser::ACTIONCASES__);

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

                            // define the startproduction
    Production::setStart(rules.startProduction());

    State::define(rules);        // define all states

    rules.assignNonTerminalNumbers();

    rules.showUnusedTerminals();
    rules.showUnusedNonTerminals();
    rules.showUnusedRules();

    State::allStates();

    Grammar grammar;
    grammar.deriveSentence();

    if (emsg.count())
        return 1;

    if (arg.option('A'))    // Analyze only
        return 0;

    Generator generator(rules, parser.polymorphic());

    if (generator.conflicts())
        return 1;

    generator.baseClassHeader();
    generator.classHeader();
    generator.implementationHeader();
    generator.parseFunction();
}
catch(exception  const &err)
{
    cerr << err.what() << '\n';
    return 1;
}
catch(int x)
{
    return Arg::instance().option("hv") ? 0 : x;
}
