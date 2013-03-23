/*
 * MoTo - Motion Toolkit 
 * Copyright (c) 2006-2010 Gino van den Bergen, DTECTA 
 * http://www.dtecta.com
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Gino van den Bergen makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 */

#ifndef MT_METRIC_HPP
#define MT_METRIC_HPP

#include <moto/Scalar.hpp>

namespace mt
{
    template <typename Vector> typename Vector::ScalarType lengthSquared(const Vector& v);
    template <typename Vector> typename Vector::ScalarType length(const Vector& v);
    template <typename Vector> typename Vector::ScalarType distanceSquared(const Vector& p1, const Vector& p2);
    template <typename Vector> typename Vector::ScalarType distance(const Vector& p1, const Vector& p2);
    template <typename Vector> Vector normalize(const Vector& v);
    template <typename Vector, typename Scalar> Vector nlerp(const Vector& v1, const Vector& v2, Scalar t);
    template <typename Vector> Vector bound(const Vector& v, typename Vector::ScalarType b);

    template <typename Vector> typename Vector::ScalarType lengthSquared3(const Vector& v);
    template <typename Vector> typename Vector::ScalarType length3(const Vector& v);
    template <typename Vector> typename Vector::ScalarType distanceSquared3(const Vector& p1, const Vector& p2);
    template <typename Vector> typename Vector::ScalarType distance3(const Vector& p1, const Vector& p2);
    template <typename Vector> Vector normalize3(const Vector& v);
    template <typename Vector, typename Scalar> Vector nlerp3(const Vector& v1, const Vector& v2, Scalar t);
    template <typename Vector> Vector bound3(const Vector& v, typename Vector::ScalarType b);

    template <typename Vector>
    FORCEINLINE 
    typename Vector::ScalarType lengthSquared(const Vector& v)
    {
        return dot(v, v);
    }

    template <typename Vector>
    FORCEINLINE 
    typename Vector::ScalarType length(const Vector& v)
    {
        return sqrt(lengthSquared(v));
    }

    template <typename Vector>
    FORCEINLINE 
    typename Vector::ScalarType distanceSquared(const Vector& p1, const Vector& p2)
    {
        return lengthSquared(p1 - p2);
    }

    template <typename Vector>
    FORCEINLINE 
    typename Vector::ScalarType distance(const Vector& p1, const Vector& p2)
    {
        return length(p1 - p2);
    } 
    
    template <typename Vector>
    FORCEINLINE
    Vector normalize(const Vector& v)
    { 
        typename Vector::ScalarType s = lengthSquared(v);  
        return ispositive(s) ? v * rsqrt(s) : v;
    }

    template <typename Vector, typename Scalar>
    FORCEINLINE 
    Vector nlerp(const Vector& v1, const Vector& v2, Scalar t)
    {
        return normalize(lerp(v1, v2, t));
    }

    template <typename Vector>
    FORCEINLINE
    Vector bound(const Vector& v, typename Vector::ScalarType b)
    { 
        ASSERT(!isnegative(b));
        typename Vector::ScalarType d = lengthSquared(v);
        return islessnn(square(b), d) ? v * (b * rsqrt(d)) : v;     
    }

    
    
    template <typename Vector>
    FORCEINLINE 
    typename Vector::ScalarType lengthSquared3(const Vector& v)
    {
        return dot3(v, v);
    }

    template <typename Vector>
    FORCEINLINE 
    typename Vector::ScalarType length3(const Vector& v)
    {
        return sqrt(lengthSquared3(v));
    }

    template <typename Vector>
    FORCEINLINE 
    typename Vector::ScalarType distanceSquared3(const Vector& p1, const Vector& p2)
    {
        return lengthSquared3(p1 - p2);
    }

    template <typename Vector>
    FORCEINLINE 
    typename Vector::ScalarType distance3(const Vector& p1, const Vector& p2)
    {
        return length3(p1 - p2);
    } 
    
    template <typename Vector>
    FORCEINLINE
    Vector normalize3(const Vector& v)
    {   
        typename Vector::ScalarType s = lengthSquared3(v);  
        return ispositive(s) ? v * rsqrt(s) : v;
    }

    template <typename Vector, typename Scalar>
    FORCEINLINE 
    Vector nlerp3(const Vector& v1, const Vector& v2, Scalar t)
    {
        return normalize3(lerp(v1, v2, t));
    } 

    template <typename Vector>
    FORCEINLINE
    Vector bound3(const Vector& v, typename Vector::ScalarType b)
    { 
        ASSERT(!isnegative(b));
        typedef typename Vector::ScalarType Scalar;
        Scalar d = lengthSquared3(v);
        return square(b) < d ? v * (b * rsqrt(d)) : v;     
    }

}

#endif

