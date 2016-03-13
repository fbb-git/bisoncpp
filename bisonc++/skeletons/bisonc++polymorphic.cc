namespace Meta__
{
    void SType::swap(SType &other)
    {
        char buffer[sizeof(SType)];
        memcpy(buffer, this,   sizeof(SType));
        memcpy(this,   &other, sizeof(SType));
        memcpy(&other, buffer, sizeof(SType));
    }
    
    SType &SType::operator=(SType const &other)
    {
        SType tmp(other);
        return *this = std::move(tmp);
        return *this;
    }
    
    template <Tag__ tag, typename ...Args>
    void SType::emplace(Args &&...args)
    {
        Semantic<tag> *semPtr = new Semantic<tag>(std::forward<Args>(args) ...);
        delete d_base;
        d_base = semPtr;
    }
    
    template <Tag__ tag>
    typename TypeOf<tag>::type &SType::get()
    {
                    // if we're not yet holding a (tag) value, initialize to 
                    // a Semantic<tag> holding a default value
        if (d_base->tag() != tag)
        {
$insert warnTagMismatch
            emplace<tag>();
        }
        return data<tag>();
    }


}   // namespace Meta__




