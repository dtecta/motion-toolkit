/*  MoTo - Motion Toolkit
    Copyright (c) 2006-2019 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
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

    template <typename Scalar> Vector3<Scalar> moment(const Vector3<Dual<Scalar> >& v, const Vector3<Scalar>& p);

#ifdef USE_OSTREAM
    template <typename CharT, typename Traits, typename Scalar> 
    std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const Vector3<Dual<Scalar> >& a);
#endif


       
    template <typename Scalar> 
    Vector3<Dual<Scalar> > makeDual(const Vector3<Scalar>& u, const Vector3<Scalar>& v)
    {
        return Vector3<Dual<Scalar> >(makeDual(u.x, v.x), makeDual(u.y, v.y), makeDual(u.z, v.z));    
    }

    template <typename Scalar>
    FORCEINLINE
    Vector3<Scalar> real(const Vector3<Dual<Scalar> >& v)
    {   
        return Vector3<Scalar>(real(v.x), real(v.y), real(v.z));
    }  
    
    template <typename Scalar>
    FORCEINLINE
    Vector3<Scalar> dual(const Vector3<Dual<Scalar> >& v)
    {   
        return Vector3<Scalar>(dual(v.x), dual(v.y), dual(v.z));
    }  
    
    template <typename Scalar>
    FORCEINLINE
    Vector3<Dual<Scalar> > conj(const Vector3<Dual<Scalar> >& v)
    {   
        return Vector3<Dual<Scalar> >(conj(v.x), conj(v.y), conj(v.z));
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

    template <typename Scalar> 
    Vector3<Scalar> moment(const Vector3<Dual<Scalar> >& v, const Vector3<Scalar>& p)
    {
        return dual(v) + cross(real(v), p); 
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

