#include "rules.ih"

void Rules::updatePrecedence(Production *production, 
                             Terminal::Vector const &tv)
{   
    if (production->precedence())       // a precedence has already been set
    {
//        if 
//        (
//            not (*production)[0].isTerminal() 
//            ||
//            production->size() < 2
//            ||
//            not (*production)[1].isNonTerminal() 
//        )
//        {
//            emsg.setTag(production->fileName() + ": error");
//            emsg.setLineNr(production->lineNr());
//            emsg << "Rule " << production << 
//                    " %prec " << production->precedence() << 
//                    ": 1st element must be a terminal token, 2nd "
//                    "element a non-terminal token" << endl;
//        }

        return;
    }

    auto symbolIter = 
        find_if(production->begin(), production->end(), isTerminal);

    if (symbolIter != production->end())
        production->setPrecedence(Terminal::downcast(*symbolIter));
}

