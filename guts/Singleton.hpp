/*  Guts - Generic Utilities 
    Copyright (c) 2006 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

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
            if (sInstance == NULLPTR)
            {
                Derived* instance = new Derived; 
                if (INTERLOCKED_COMPARE_EXCHANGE_POINTER(&sInstance, instance, NULLPTR) != NULLPTR)
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
    Derived* volatile Singleton<Derived>::sInstance = NULLPTR;
}

#endif
