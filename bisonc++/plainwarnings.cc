#include <bobcat/mstream>

namespace Global
{
    void plainWarnings()
    {
        FBB::wmsg.setTag("Warning");
        FBB::wmsg.noLineNr();
    }
}
