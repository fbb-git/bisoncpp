#include "options.ih"

void Options::delimit(string *target, char const *declTxt)
{
    if (target->size())
        emsg << "%" << declTxt << "multiply specified" << endl;
    else
    {
        *target = String::unescape(*d_matched);
        if (target->find("<\"") != 0)       // not a quoted string
            target->insert(0, 1, '"') += '"';
    }
}
