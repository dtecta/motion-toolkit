/*  MoTo - Motion Toolkit
    Copyright (c) 2006 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
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

