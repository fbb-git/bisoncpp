#include "options.ih"

Options &Options::instance()
{
    if (s_options == 0)
        s_options = new Options();

    return *s_options;
}
