#include "state.ih"

void State::writeGoToTransition
                (GoToTable::value_type const &goTo, ostream &out)
{
    out << 
        "    {"
                "{" << 
                    goTo.first->nr() << 
                "}, "
                "{" <<
                    goTo.second << 
                "}"
            "}, // " << 
                    goTo.first->name() << "\n";
}

