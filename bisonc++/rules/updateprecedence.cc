#include "rules.ih"

void Rules::updatePrecedence(Production *production)
{   
    if (production->precedence())       // a precedence has already been set
        return;

    auto symbolIter = 
        find_if(production->begin(), production->end(), isTerminal);

    if (symbolIter != production->end())
        production->setPrecedence(Terminal::downcast(*symbolIter));
}

//  elaborate compound stmnt after if (production->precedence):
//    {
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
//        return;
//    }








