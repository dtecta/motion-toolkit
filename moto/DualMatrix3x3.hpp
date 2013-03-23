/*
 * MoTo - Motion Toolkit 
 * Copyright (c) 2006-2008 Gino van den Bergen, DTECTA 
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

#ifndef MT_DUALMATRIX3X3_HPP
#define MT_DUALMATRIX3X3_HPP

#include <moto/Dual.hpp>
#include <moto/Matrix3x3.hpp>

namespace mt
{
    template <typename Scalar> Matrix3x3<Dual<Scalar> > makeDual(const Matrix3x3<Scalar>& u, const Matrix3x3<Scalar>& v);
    template <typename Scalar> Matrix3x3<Scalar> real(const Matrix3x3<Dual<Scalar> >& m); 
    template <typename Scalar> Matrix3x3<Scalar> dual(const Matrix3x3<Dual<Scalar> >& m); 
    template <typename Scalar> Matrix3x3<Dual<Scalar> > lineTransform(const Matrix3x3<Scalar>& basis, const Vector3<Scalar>& origin);
    
  
    template <typename Scalar> 
    Matrix3x3<Dual<Scalar> > makeDual(const Matrix3x3<Scalar>& u, const Matrix3x3<Scalar>& v)
    {
        return Matrix3x3<Dual<Scalar> >(Dual<Scalar>(u[0][0], v[0][0]), Dual<Scalar>(u[0][1], v[0][1]), Dual<Scalar>(u[0][2], v[0][2]),
                                        Dual<Scalar>(u[1][0], v[1][0]), Dual<Scalar>(u[1][1], v[1][1]), Dual<Scalar>(u[1][2], v[1][2]),
                                        Dual<Scalar>(u[2][0], v[2][0]), Dual<Scalar>(u[2][1], v[2][1]), Dual<Scalar>(u[2][2], v[2][2]));    
    }

    template <typename Scalar>
    FORCEINLINE
    Matrix3x3<Scalar> real(const Matrix3x3<Dual<Scalar> >& m)
    {   
        return Matrix3x3<Scalar>(real(m[0][0]), real(m[0][1]), real(m[0][2]),
                                 real(m[1][0]), real(m[1][1]), real(m[1][2]),
                                 real(m[2][0]), real(m[2][1]), real(m[2][2]));
    }  

    template <typename Scalar>
    FORCEINLINE
    Matrix3x3<Scalar> dual(const Matrix3x3<Dual<Scalar> >& m)
    {   
        return Matrix3x3<Scalar>(dual(m[0][0]), dual(m[0][1]), dual(m[0][2]),
                                 dual(m[1][0]), dual(m[1][1]), dual(m[1][2]),
                                 dual(m[2][0]), dual(m[2][1]), dual(m[2][2]));
    }  

    template <typename Scalar>
    FORCEINLINE
    Matrix3x3<Dual<Scalar> > lineTransform(const Matrix3x3<Scalar>& basis, const Vector3<Scalar>& origin)
    {   
        return makeDual(basis, mul(cross(origin), basis));
    }  
}

#endif

