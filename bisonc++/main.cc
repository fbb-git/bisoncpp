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
        Arg::LongOption{"analyze-only", 'A'},
                                                            
        Arg::LongOption{"baseclass-header", 'b'},           // also directive
        Arg::LongOption{"baseclass-preinclude", 'H'},       // also directive
        {"baseclass-skeleton", 'B'},
                                                            
        Arg::LongOption{"class-header", 'c'},               // also directive
        Arg::LongOption{"class-name", Arg::Required},       // also directive
        Arg::LongOption{"class-skeleton", 'C'},
        Arg::LongOption{"construction"},
            // implies verbose, but also shows              
            // FIRST and FOLLOW sets as well as             
            // the full set of states, including             
            // the non-kernel items                         

        Arg::LongOption{"debug"},                           // also directive
        Arg::LongOption{"default-actions", 'd'},            // also directive

        Arg::LongOption{"error-verbose"},                   // also directive
                                                            
        Arg::LongOption{"filenames", 'f'},                  // also directive
        Arg::LongOption{"flex"},                            // also directive
                                                            
        Arg::LongOption{"help", 'h'},
                                                            
        Arg::LongOption{"implementation-header", 'i'},      // also directive
        Arg::LongOption{"implementation-skeleton", 'I'},
        Arg::LongOption{"insert-stype"},
                                                            
        Arg::LongOption{"max-inclusion-depth", Arg::Required},
                                                            
        Arg::LongOption{"namespace", 'n'},                  // also directive
        Arg::LongOption{"no-baseclass-header"},
        Arg::LongOption{"no-decoration", 'D'},
        Arg::LongOption{"no-lines"},                        // also directive
        Arg::LongOption{"no-parse-member"},
                                                            
        Arg::LongOption{"own-debug"},
        Arg::LongOption{"own-tokens", 'T'},

        Arg::LongOption{"parsefun-skeleton", 'P'},
        Arg::LongOption{"parsefun-source", 'p'},            // also directive
        Arg::LongOption{"polymorphic-code-skeleton", 'L'},
        Arg::LongOption{"polymorphic-skeleton", 'M'},
        Arg::LongOption{"print-tokens", 't'},               // also directive

        Arg::LongOption{"prompt"},                          // also directive

        Arg::LongOption{"required-tokens", Arg::Required},  // also directive

        Arg::LongOption{"scanner", 's'},                    // also directive
                                                            // also directive
        Arg::LongOption{"scanner-class-name", Arg::Required},   
        Arg::LongOption{"scanner-debug"},
                                                            // also directive
        Arg::LongOption{"scanner-matched-text-function", Arg::Required},    
                                                            // also directive
        Arg::LongOption{"scanner-token-function", Arg::Required},
        Arg::LongOption{"show-filenames"},
        Arg::LongOption{"skeleton-directory", 'S'},
        Arg::LongOption{"stack-expansion", Arg::Required},

        Arg::LongOption{"tag-mismatches", Arg::Required},   // also directive
        Arg::LongOption{"target-directory", Arg::Required}, // also directive
        Arg::LongOption{"thread-safe"},                     // also directive

        Arg::LongOption{"usage", 'h'},                                     

        Arg::LongOption{"verbose", 'V'},
            // shows rules, tokens, final states and kernel
            // items, and describes conflicts when found
        Arg::LongOption{"version", 'v'},

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

//    parser.setDebug(Parser::ACTIONCASES |);

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
