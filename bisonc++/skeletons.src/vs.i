inline \@Base::STYPE__ &\@Base::vs__(size_t idx) 
{
    return std::get<3>(*(d_vsp - idx));
}

