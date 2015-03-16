/*  MoTo - Motion Toolkit
    Copyright (c) 2006 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#ifndef MT_SCALARTRAITS_HPP
#define MT_SCALARTRAITS_HPP

#include <consolid/consolid.h>
#include <limits>

namespace mt
{
    // Constants and static functions that do not take arguments must be placed in a traits class.

    template <typename Scalar>
    struct ScalarTraits {};

    template <>
    struct ScalarTraits<float>
    {
        static float pi()
        {
            return 3.14159265358979323846f;
        }

        static float infinity()
        {
            return std::numeric_limits<float>::infinity();
        }

        static float epsilon()
        {
            return std::numeric_limits<float>::epsilon();
        }

        static float max()
        {
            return std::numeric_limits<float>::max();
        }
    };

    template <>
    struct ScalarTraits<double>
    {
        static double pi()
        {
            return 3.14159265358979323846;
        }

        static double infinity()
        {
            return std::numeric_limits<double>::infinity();
        }

        static double epsilon()
        {
            return std::numeric_limits<double>::epsilon();
        }  

        static double max()
        {
            return std::numeric_limits<double>::max();
        }
    };  
    
    template <>
    struct ScalarTraits<long double>
    {
        static long double pi()
        {
            return 3.1415926535897932384626433832795029L;
        }

        static long double infinity()
        {
            return std::numeric_limits<long double>::infinity();
        }

        static long double epsilon()
        {
            return std::numeric_limits<long double>::epsilon();
        }  

        static long double max()
        {
            return std::numeric_limits<long double>::max();
        }
    };  
}

#endif
