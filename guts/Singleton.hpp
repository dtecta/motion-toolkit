#ifndef GUTS_SINGLETON_HPP
#define GUTS_SINGLETON_HPP

#include <consolid/consolid.h>

namespace guts
{
    template <typename Derived>
    class Singleton
    {
    public:
        static Derived& instance() 
        {
            if (sInstance == 0)
            {
                Derived* instance = new Derived; 
                if (INTERLOCKED_COMPARE_EXCHANGE_POINTER(&sInstance, instance, 0) != 0)
                {
                    delete instance;
                }
            }
            return *sInstance;
        }

    private:
        static Derived* volatile sInstance;
    };

    template <typename Derived>
    Derived* volatile Singleton<Derived>::sInstance = 0;
}

#endif
