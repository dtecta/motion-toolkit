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

#ifndef MT_DUALVECTOR3_HPP
#define MT_DUALVECTOR3_HPP

#include <moto/Dual.hpp>
#include <moto/Vector3.hpp>
#include <moto/Vector4.hpp>

namespace mt
{
    template <typename Scalar> Vector3<Dual<Scalar> > makeDual(const Vector3<Scalar>& u, const Vector3<Scalar>& v);

    template <typename Scalar> Vector3<Scalar> real(const Vector3<Dual<Scalar> >& v); 
    template <typename Scalar> Vector3<Scalar> dual(const Vector3<Dual<Scalar> >& v); 
    template <typename Scalar> Vector3<Dual<Scalar> > conj(const Vector3<Dual<Scalar> >& v);
 
    
    // The line through p and q represented as Pluecker coordinates
    template <typename Scalar> Vector3<Dual<Scalar> > makeLine(const Vector3<Scalar>& p, const Vector3<Scalar>& q);

    // Again, the line through p and q but now p and q are in homogenous coordinates. 
    template <typename Scalar> Vector3<Dual<Scalar> > makeLine(const Vector4<Scalar>& p, const Vector4<Scalar>& q);

    // The line of intersection of two planes p and q represented by homogeneous coordinates:
    // ax + by + cz + dw = 0 for a plane [a, b, c, d] and a (homogenous) point on the plane [x, y, z, w]
    template <typename Scalar> Vector3<Dual<Scalar> > makeIntersect(const Vector4<Scalar>& p, const Vector4<Scalar>& q);

    template <typename Scalar> Vector3<Scalar> closest(const Vector3<Dual<Scalar> >& v);
    template <typename Scalar> Scalar pitch(const Vector3<Dual<Scalar> >& v);

#ifdef USE_OSTREAM
    template <typename CharT, typename Traits, typename Scalar> 
    std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const Vector3<Dual<Scalar> >& a);
#endif


       
    template <typename Scalar> 
    Vector3<Dual<Scalar> > makeDual(const Vector3<Scalar>& u, const Vector3<Scalar>& v)
    {
        return Vector3<Dual<Scalar> >(makeDual(u[0], v[0]), makeDual(u[1], v[1]), makeDual(u[2], v[2]));    
    }

    template <typename Scalar>
    FORCEINLINE
    Vector3<Scalar> real(const Vector3<Dual<Scalar> >& v)
    {   
        return Vector3<Scalar>(real(v[0]), real(v[1]), real(v[2]));
    }  
    
    template <typename Scalar>
    FORCEINLINE
    Vector3<Scalar> dual(const Vector3<Dual<Scalar> >& v)
    {   
        return Vector3<Scalar>(dual(v[0]), dual(v[1]), dual(v[2]));
    }  
    
    template <typename Scalar>
    FORCEINLINE
    Vector3<Dual<Scalar> > conj(const Vector3<Dual<Scalar> >& v)
    {   
        return Vector3<Dual<Scalar> >(conj(v[0]), conj(v[1]), conj(v[2]));
    } 

    template <typename Scalar> 
    Vector3<Dual<Scalar> > makeLine(const Vector3<Scalar>& p, const Vector3<Scalar>& q)
    {
        return makeDual(q - p, cross(p, q));
    }

    template <typename Scalar> 
    Vector3<Dual<Scalar> > makeLine(const Vector4<Scalar>& p, const Vector4<Scalar>& q)
    {
        return makeDual(xyz(q) * p.w - xyz(p) * q.w, cross(xyz(p), xyz(q)));
    }

    template <typename Scalar> 
    Vector3<Dual<Scalar> > makeIntersect(const Vector4<Scalar>& p, const Vector4<Scalar>& q)
    {
        return makeDual(cross(xyz(p), xyz(q)), xyz(q) * p.w - xyz(p) * q.w);
    }
    
    

    template <typename Scalar> 
    Vector3<Scalar> closest(const Vector3<Dual<Scalar> >& v)
    {
        return cross(real(v), dual(v)) / lengthSquared(real(v));
    }

    template <typename Scalar> 
    Scalar pitch(const Vector3<Dual<Scalar> >& v)
    {
        return dot(real(v), dual(v)) / lengthSquared(real(v));
    }

#ifdef USE_OSTREAM

    template <typename CharT, typename Traits, typename Scalar> 
    FORCEINLINE 
    std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const Vector3<Dual<Scalar> >& a)
    {
        return os << '[' << real(a) << "] + \xee [" << dual(a) << ']';
    }

#endif

  
}

#endif

