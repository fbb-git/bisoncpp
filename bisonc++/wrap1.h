#ifndef _INCLUDED_WRAP1_H_
#define _INCLUDED_WRAP1_H_

namespace FBB
{
    template <typename Type, typename Context, typename ReturnType = void>
    class Wrap1
    {
        ReturnType (*d_fun)(Type, Context &);
        Context &d_context;

        public:
            Wrap1(ReturnType (*fun)(Type, Context &), Context &context)
            :
                d_fun(fun),
                d_context(context)
            {}
            ReturnType operator()(Type param) const
            {
                return (*d_fun)(param, d_context);
            }
    };
} // namespace FBB ends
#endif
