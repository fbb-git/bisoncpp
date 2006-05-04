#include "generator.ih"

void Generator::stateArray(ostream &out) const
{
    unsigned const n = 10;

    out << "\n"
            "// State array:\n" 
            "SR *s_state[] =\n"
            "{\n";

    for (unsigned idx = 0; idx < State::nStates(); ++idx)
        out << "  s_" << idx << "," << ((idx + 1) % n == 0 ? "\n" : "");

    
    out << (State::nStates() % n ? "\n" : "") <<
            "};\n"
            "\n";
}





