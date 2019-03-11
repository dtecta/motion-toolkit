/*  MoTo - Motion Toolkit
    Copyright (c) 2006-2019 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#ifndef MT_DUALVECTOR4_HPP
#define MT_DUALVECTOR4_HPP

#include <moto/Dual.hpp>
#include <moto/Vector4.hpp>

namespace mt
{
    template <typename Scalar> Vector4<Dual<Scalar> > makeDual(const Vector4<Scalar>& u, const Vector4<Scalar>& v);
    template <typename Scalar> Vector4<Scalar> real(const Vector4<Dual<Scalar> >& q); 
    template <typename Scalar> Vector4<Scalar> dual(const Vector4<Dual<Scalar> >& q); 


    // A dual quaternion has two conjugate operations!!
    //     1) Vector part (i, j, k) for both real and dual is negated. This is performed by "conjugate(q)".
    //     2) Dual part is negated. This is performed by "conj(q)".
    // Order is not important: conjugate(conj(q)) == conj(conjugate(q))    
  
    template <typename Scalar> Vector4<Dual<Scalar> > conj(const Vector4<Dual<Scalar> >& q);

    template <typename Scalar> Vector3<Scalar> rigidTransform(const Vector4<Dual<Scalar> >& q, const Vector3<Scalar>& p);


    // A dual quaternion representing a rigid transformation with rotation q and translation t
    template <typename Scalar> Vector4<Dual<Scalar> > rigid(const Vector4<Scalar>& q, const Vector3<Scalar>& t);


    // The reverse operations. "rotation(q)" returns the rotation as a real quaternion, 
    template <typename Scalar> Vector4<Scalar> rotation(const Vector4<Dual<Scalar> >& q);

    // and "translation(q)" returns the translation part.
    template <typename Scalar> Vector3<Scalar> translation(const Vector4<Dual<Scalar> >& q); 

    template <typename Scalar> Vector3<Dual<Scalar> > logUnit(const Vector4<Dual<Scalar> >& q);
    template <typename Scalar> Vector4<Dual<Scalar> > exp(const Vector3<Dual<Scalar> >& v);
    
#ifdef USE_OSTREAM
    template <typename CharT, typename Traits, typename Scalar> 
    std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const Vector4<Dual<Scalar> >& a);
#endif


  
    template <typename Scalar> 
    Vector4<Dual<Scalar> > makeDual(const Vector4<Scalar>& u, const Vector4<Scalar>& v)
    {
        return Vector4<Dual<Scalar> >(Dual<Scalar>(u.x, v.x), Dual<Scalar>(u.y, v.y), Dual<Scalar>(u.z, v.z), Dual<Scalar>(u.w, v.w));    
    }

    template <typename Scalar>
    FORCEINLINE
    Vector4<Scalar> real(const Vector4<Dual<Scalar> >& q)
    {   
        return Vector4<Scalar>(real(q.x), real(q.y), real(q.z), real(q.w));
    }  
    
    template <typename Scalar>
    FORCEINLINE
    Vector4<Scalar> dual(const Vector4<Dual<Scalar> >& q)
    {   
        return Vector4<Scalar>(dual(q.x), dual(q.y), dual(q.z), dual(q.w));
    } 
    
    template <typename Scalar> 
    FORCEINLINE    
    Vector4<Dual<Scalar> > conj(const Vector4<Dual<Scalar> >& q)
    {
        return Vector4<Dual<Scalar> >(conj(q.x), conj(q.y), conj(q.z), conj(q.w));
    }  
    

    template <typename Scalar> 
    FORCEINLINE    
    Vector3<Scalar> rigidTransform(const Vector4<Dual<Scalar> >& q, const Vector3<Scalar>& p)
    {
        // Which is faster?
        return rotation(q)(p) + translation(q); 
        // return xyz(dual(mul(mul(q, makeDual(Vector4<Scalar>(Identity()), Vector4<Scalar>(p))), conj(conjugate(q)))));
    } 



    template <typename Scalar> 
    FORCEINLINE    
    Vector4<Dual<Scalar> > rigid(const Vector4<Scalar>& q, const Vector3<Scalar>& t)
    {
        return makeDual(q, mul(t, q) * Scalar(0.5));
    } 


    template <typename Scalar>
    FORCEINLINE 
    Vector4<Scalar> rotation(const Vector4<Dual<Scalar> >& q)
    {
        return real(q);
    }
     

    template <typename Scalar>
    FORCEINLINE 
    Vector3<Scalar> translation(const Vector4<Dual<Scalar> >& q)
    {
        return xyz(mul(dual(q), conjugate(real(q)))) * Scalar(2);
    }

    // This one is safe for dual quaternions with an identity real part
    template <typename Scalar>
    FORCEINLINE 
    Vector3<Dual<Scalar> > logUnit(const Vector4<Dual<Scalar> >& q)
    { 
        return makeDual(logUnit(real(q)), xyz(mul(dual(q), conjugate(real(q)))));
    }
 
    template <typename Scalar>
    FORCEINLINE 
    Vector4<Dual<Scalar> > exp(const Vector3<Dual<Scalar> >& v)
    { 
        Vector4<Scalar> q = exp(real(v));
        return makeDual(q, mul(dual(v), q));
    }

#ifdef USE_OSTREAM

    template <typename CharT, typename Traits, typename Scalar> 
    FORCEINLINE 
    std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const Vector4<Dual<Scalar> >& a)
    {
        return os << '[' << real(a) << "] + \xee [" << dual(a) << ']';
    }

#endif
    
}

#endif

