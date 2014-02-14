#include "writer.ih"

void Writer::statesArray() const
{
    size_t const nPerLine = 10;

    *d_out << "\n"
            "// State array:\n" 
            "SR__ " << s_threadConst << "*s_state[] =\n"
            "{\n";

    for (size_t idx = 0; idx != State::nStates(); ++idx)
        *d_out << "  s_" << idx << "," << 
                        ((idx + 1) % nPerLine == 0 ? "\n" : "");

    
    *d_out << (State::nStates() % nPerLine ? "\n" : "") <<
            "};\n"
            "\n";
}





