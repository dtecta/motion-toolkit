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

#ifndef MT_DUALVECTOR2_HPP
#define MT_DUALVECTOR2_HPP

#include <moto/Dual.hpp>
#include <moto/Vector2.hpp>

namespace mt
{ 
    template <typename Scalar> Vector2<Dual<Scalar> > makeDual(const Vector2<Scalar>& u, const Vector2<Scalar>& v);

    template <typename Scalar> Vector2<Scalar> real(const Vector2<Dual<Scalar> >& v); 
    template <typename Scalar> Vector2<Scalar> dual(const Vector2<Dual<Scalar> >& v); 
    template <typename Scalar> Vector2<Dual<Scalar> > conj(const Vector2<Dual<Scalar> >& v);
 
#ifdef USE_OSTREAM
    template <typename CharT, typename Traits, typename Scalar> 
    std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const Vector2<Dual<Scalar> >& a);
#endif


    
    template <typename Scalar> 
    Vector2<Dual<Scalar> > makeDual(const Vector2<Scalar>& u, const Vector2<Scalar>& v)
    {
        return Vector2<Dual<Scalar> >(makeDual(u.x, v.x), makeDual(u.y, v.y));    
    }

    template <typename Scalar>
    FORCEINLINE
    Vector2<Scalar> real(const Vector2<Dual<Scalar> >& v)
    {   
        return Vector2<Scalar>(real(v.x), real(v.y));
    }  
    
    template <typename Scalar>
    FORCEINLINE
    Vector2<Scalar> dual(const Vector2<Dual<Scalar> >& v)
    {   
        return Vector2<Scalar>(dual(v.x), dual(v.y));
    }  
    
    template <typename Scalar>
    FORCEINLINE
    Vector2<Dual<Scalar> > conj(const Vector2<Dual<Scalar> >& v)
    {   
        return Vector2<Dual<Scalar> >(conj(v.x), conj(v.y));
    } 

#ifdef USE_OSTREAM

    template <typename CharT, typename Traits, typename Scalar> 
    FORCEINLINE 
    std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const Vector2<Dual<Scalar> >& a)
    {
        return os << '[' << real(a) << "] + \xee [" << dual(a) << ']';
    }

#endif

  
}

#endif

