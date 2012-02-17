#include "sembase.ih"

SemBase *SemBase::v_clone() const
{
    notImplemented();
    return 0;           // not reached
}
string const &SemBase::v_str() const
{
    notImplemented();

    return *reinterpret_cast<string const *>(0);           // not reached
}

bool SemBase::v_logic() const
{
    notImplemented();
    return false;       // not reached
}

size_t SemBase::v_size() const
{
    notImplemented();
    return 0;           // not reached
}

Block const &SemBase::v_block() const
{
    notImplemented();
    return *reinterpret_cast<Block const *>(0);           // not reached
}

